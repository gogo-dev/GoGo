#include <database/MySQLGunzDB.h>

#include <cstddef>
#include <cassert>

#include <boost/bind/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace mysqlpp;

static void make_get_inventory_query(Query& q, uint32_t cid)
{
	q << "SELECT * FROM character_inventory where charid=" << cid;
}

static vector<Item> handle_get_inventory(const StoreQueryResult& result)
{
	typedef mysqlpp::StoreQueryResult::const_iterator ResultIt;

	vector<Item> items(16);

	for(ResultIt i = result.begin(), end = result.end(); i != end; ++i)
	{
		const Row& row = *i;
		Item item;

		item.ItemCID = row["id"];
		item.ItemID = row["itemid"];

		if(row["rental"])
		{
			// TODO(Jacob): Handle item.RentHour
		}

		items.push_back(item);
	}

	return items;
}

vector<Item> MySQLGunzDB::GetInventory(uint32_t cid)
{
	return run_query<vector<Item> >(
		bind(make_get_inventory_query, _1, cid),
		handle_get_inventory
	);
}
