//! This is our misc/general structures.
#include <string>
#include <list>

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

enum ChannelType
{
	CT_GENERAL,
	CT_PRIVATE,
	CT_USER,
	CT_CLAN,
	CT_NONE = 255
};

enum ChannelRule
{
	CR_NOVICE,
	CR_NEWBIE,
	CR_ROOKIE,
	CR_MASTERY,
	CR_ELITE
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

enum ObjectCacheState
{
	OCS_KEEP,
	OCS_NEW,
	OCS_EXPIRE
};

enum PacketErrorCode
{
    PEC_NONE,
    PEC_WRONG_PASSWORD = 10000,
    PEC_ACCOUNT_INUSE = 10001,
    PEC_INVALIDV_ERSION = 10002,
    PEC_SERVER_FULL = 10003,
    PEC_USER_BANNED = 10004,
    PEC_AUTH_FAILED = 10005,
    PEC_NAME_IN_USE = 10100,
    PEC_INVALID_NAME = 10101,
    PEC_NAME_SHORT = 10102,
    PEC_NAME_LONG = 10103,
    PEC_NONAME = 10104,
    PEC_NO_CHARACTER = 10110,
    PEC_NO_DELETE = 10111,
	PEC_INSUFFICIENT_BOUNTY = 20001,
    PEC_INVALID_ITEM = 20007,
    PEC_INVENTORY_FULL = 20008,
    PEC_FALSE_ITEM = 20009,
    PEC_LEVEL_LOW = 20011,
    PEC_STAGE_FULL = 30001,
    PEC_STAGE_INVALID_PASS = 30002,
    PEC_STAGE_INVALID_LEVEL = 30003,
    PEC_INVALID_STAGE = 30006,
    PEC_STAGE_CREATE_FAILED = 30008,
    PEC_CHANNEL_JOIN_FAILED = 30020,
    PEC_CHANNEL_FULL = 300021,
    PEC_CHANNEL_INVALID_LEVEL = 300022
};


struct MUID
{
	boost::uint32_t uidLow;
	boost::uint32_t uidHigh;
};

struct AccountInfo
{
	boost::uint32_t AccountId;
	char AccountName[32];
	boost::uint8_t AccountAccess;
	boost::uint8_t AccountPremium;
};

struct Item
{
    boost::uint32_t ItemCID;
    boost::uint32_t ItemID;
    boost::uint32_t RentHour;
    boost::uint32_t Price;
    boost::uint8_t  Sex;
    boost::uint8_t  Level;
    boost::uint32_t Weight;
    boost::uint32_t MaxWT;

	Item() { RentHour = 0x20050800; }
};

struct CharacterInfo
{
	boost::uint32_t CharacterId;
	char CharacterName[32];
	char ClanName[16];
	ClanGrade CharacterGrade;
	boost::uint16_t ClanPoints;
	boost::uint8_t CharacterMarker;
	boost::uint16_t CharacterLevel;
	boost::uint8_t CharacterSex;
	boost::uint8_t CharacterHair;
	boost::uint8_t CharacterFace;
	boost::uint32_t CharacterXP;
	boost::uint32_t CharacterBP;
	float BonusRate; //Always 0, never used.
	boost::uint16_t Prize;
	boost::uint16_t HP;
	boost::uint16_t AP;
	boost::uint16_t MaxWeight;
	boost::uint16_t SafeFalls;
	boost::uint16_t FR;
	boost::uint16_t CR;
	boost::uint16_t ER;
	boost::uint16_t WR;
	Item Equipment[12];
	UserGrade CharacterAccess;
	boost::uint32_t ClandId;
	std::list<Item> Inventory;
};

struct MMatchWorldItem   
{
    boost::uint16_t nUID;
    boost::uint16_t nItemID;
    boost::uint16_t nStaticSpawnIndex;
    float x;
    float y;
    float z;
    boost::uint32_t nLifeTime;
    boost::uint32_t nQuestItemID;
};

