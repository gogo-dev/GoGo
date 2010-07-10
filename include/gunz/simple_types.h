// This file contains general-purpose structures and enumerations that are global throughout
// all of GoGo. Do your best to keep things out of this file. It kinda ruins encapsulation.
#pragma once
#include <boost/cstdint.hpp>

namespace gunz {

enum UserGrade
{
    UG_GUEST,
    UG_USER,
    UG_EVENT,
    UG_CRIMINAL = 100,
    UG_WARNING1 = 101,
    UG_WARNING2 = 102,
    UG_WARNING3 = 103,
    UG_CHATBAN = 104,
    UG_PENALITY = 105,
    UG_EVENTMASTER = 252,
    UG_BANNED = 253,
    UG_DEVELOPER = 254,
    UG_ADMINISTRATOR = 255
};

enum PremiumGrade
{
	PG_FREE,
	PG_PREMIUM
};

enum ClanGrade
{
    CG_NONE,
    CG_MASTER,
    CG_ADMIN,
    CG_USER = 9
};

enum SlotType
{
	ST_HEAD,
	ST_CHEST,
	ST_HANDS,
	ST_LEGS,
	ST_FEET,
	ST_LFINGER,
	ST_RFINGER,
	ST_MELEE,
	ST_PRIMARY,
	ST_SECONADY,
	ST_CUSTOM1,
	ST_CUSTOM2
};

enum ItemType
{
	IT_MELEE,
	IT_RANGE,
	IT_EQUIPMENT,
	IT_CUSTOM,
	IT_NONE
};

enum MatchPlace
{
	MP_CHARACTER,
	MP_LOBBY,
	MP_STAGE,
	MP_GAME,
	MP_END
};

enum ObjectStageState
{
	OSS_NOTREADY,
	OSS_READY,
	OSS_SHOP,
	OSS_EQUIPMENT,
	OSS_END
};

enum StageState
{
	SS_STANDBY,
	SS_COUNTDOWN,
	SS_BATTLE,
	SS_END
};

enum RoundState
{
	RS_PREPARE,
	RS_COUNTDOWN,
	RS_PLAY,
	RS_FINISH,
	RS_EXIT,
	RS_FREE,
	RS_FAILED
};

enum GameType
{
	GT_DEATHMATCH,
	GT_TEAMDEATHMATCH,
	GT_GLADIATOR,
	GT_ASSASSINATION,
	GT_TRAINING,
	GT_SURVIVAL,
	GT_QUEST,
	GT_BERSERKER,
	GT_TEAMDEATHMATCHEXTREME,
	GT_DUEL
};

enum TeamColor
{
	TC_ALL,
	TC_SPECTATOR,
	TC_RED,
	TC_BLUE,
	TC_END
};

enum MessageType
{
	MT_ANNOUNCE,
	MT_WHISPER,
	MT_CHANNEL,
	MT_STAGE
};

typedef boost::uint64_t MUID;

}
