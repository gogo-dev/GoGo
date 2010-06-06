#include <cockpit/MatchServer.h>
#include "ClientConnection.h"

#include <cockpit/ClientHandler.h>

#include <cockpit/packet/Registry.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost;
using namespace boost::asio;

namespace cockpit {

void MatchServer::accept_new_client()
{
	shared_ptr<ClientConnection> client(new ClientConnection(io, factory));

	acceptor->async_accept(
		client->s.get_raw(),
		bind(&MatchServer::handle_new_client, this, client, placeholders::error)
	);
}

void MatchServer::handle_new_client(shared_ptr<ClientConnection> client, system::error_code error)
{
	if(error)
		return;

	accept_new_client();

	packet::Registry registry;

	client->s.set_registry(&registry);
	client->handler->initialize(&client->s, &registry);

	client->s.begin();
}

}