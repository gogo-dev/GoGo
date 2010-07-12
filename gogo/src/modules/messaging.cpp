#include "../GoGoClient.h"

#include <cockpit/Transmitter.h>

static void on_announce(cockpit::Transmitter* transmitter, const char* sender, const char* message)
{
}

static void on_channel_chat(cockpit::Transmitter* transmitter, const char* sender, const char* message)
{
}

static void on_stage_chat(cockpit::Transmitter* transmitter, const char* sender, const char* message)
{
}

static void on_whisper(cockpit::Transmitter* transmitter, const char* sender, const char* message)
{
}

void GoGoClient::OnMessage(MessageType type, const char* sender, const char* message)
{
	switch(type)
	{
	case MT_ANNOUNCE:
		on_announce(transmitter, sender, message);
	case MT_CHANNEL:
		on_channel_chat(transmitter, sender, message);
	case MT_STAGE:
		on_stage_chat(transmitter, sender, message);
	case MT_WHISPER:
		on_whisper(transmitter, sender, message);
	default:
		assert(0 && "Trying to send a message to something not in the enum. Is your compiler broken for not warning you about this?");
	}
}
