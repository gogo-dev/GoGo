#include <cockpit/packet/Lookup.h>
#include <cockpit/packet/protocol/all>

using namespace boost;

namespace cockpit {
namespace packet {

PacketInfo::PacketInfo(const char* _name, const char* _doc, uint16_t _commandID)
	: name(_name), doc(_doc), commandId(_commandID)
{
}

PacketInfo::~PacketInfo()
{
}

BadCommandId::BadCommandId(uint16_t _commandId)
	: std::runtime_error("Bad command ID!"), commandId(_commandId)
{
}

BadCommandId::~BadCommandId()
{
}

PacketInfo lookup(uint16_t commandID)
{
	switch(commandID)
	{
		case protocol::Net_Ping::packetID: return PacketInfo("Net_Ping", "Ping", commandID);
		case protocol::Net_Pong::packetID: return PacketInfo("Net_Pong", "Pong", commandID);
		case protocol::Match_Announce::packetID: return PacketInfo("Match_Announce", "Announce Server Message", commandID);
		case protocol::Clock_Synchronize::packetID: return PacketInfo("Clock_Synchronize", "Synchronize Clock", commandID);
		case protocol::Match_Login::packetID: return PacketInfo("Match_Login", "Login Match Server", commandID);
		case protocol::Match_ResponseLogin::packetID: return PacketInfo("Match_ResponseLogin", "Response Login", commandID);
		case protocol::Match_Response_Result::packetID: return PacketInfo("Match_Response_Result", "Response Result", commandID);
		case protocol::Match_LoginNetmarble::packetID: return PacketInfo("Match_LoginNetmarble", "Login from Netmarble", commandID);
		case protocol::MC_MATCH_DISCONNMSG::packetID: return PacketInfo("MC_MATCH_DISCONNMSG", "disconnect reason", commandID);
		case protocol::MC_MATCH_LOGIN_NHNUSA::packetID: return PacketInfo("MC_MATCH_LOGIN_NHNUSA", "Login from nhn usa.", commandID);
		case protocol::MC_MATCH_LOGIN_GAMEON_JP::packetID: return PacketInfo("MC_MATCH_LOGIN_GAMEON_JP", "Login from GameOn Japan", commandID);
		case protocol::Match_ObjectCache::packetID: return PacketInfo("Match_ObjectCache", "Match Object Cache", commandID);
		case protocol::Match_BridgePeer::packetID: return PacketInfo("Match_BridgePeer", "Match BridgePeer", commandID);
		case protocol::Match_BridgePeerACK::packetID: return PacketInfo("Match_BridgePeerACK", "ACK for BridgePeer", commandID);
		case protocol::MatchServer_RequestRecommandedChannel::packetID: return PacketInfo("MatchServer_RequestRecommandedChannel", "Request recommanded channel", commandID);
		case protocol::MatchServer_ResponseRecommandedChannel::packetID: return PacketInfo("MatchServer_ResponseRecommandedChannel", "Response recommanded channel", commandID);
		case protocol::Channel_Join::packetID: return PacketInfo("Channel_Join", "Join a Channel", commandID);
		case protocol::Channel_ResponseJoin::packetID: return PacketInfo("Channel_ResponseJoin", "Response Join a Channel", commandID);
		case protocol::Channel_RequestJoinFromName::packetID: return PacketInfo("Channel_RequestJoinFromName", "Join a Channel From Name", commandID);
		case protocol::Channel_Leave::packetID: return PacketInfo("Channel_Leave", "Leave Channel", commandID);
		case protocol::Channel_ListStart::packetID: return PacketInfo("Channel_ListStart", "Channel List transmit start", commandID);
		case protocol::Channel_ListStop::packetID: return PacketInfo("Channel_ListStop", "Channel List transmit stop", commandID);
		case protocol::Channel_List::packetID: return PacketInfo("Channel_List", "Channel List", commandID);
		case protocol::Channel_Request_Chat::packetID: return PacketInfo("Channel_Request_Chat", "Request Chat to Channel", commandID);
		case protocol::Channel_Chat::packetID: return PacketInfo("Channel_Chat", "Chat to Channel", commandID);
		case protocol::Channel_Request_Rule::packetID: return PacketInfo("Channel_Request_Rule", "Request the Channel Rule", commandID);
		case protocol::Channel_Response_Rule::packetID: return PacketInfo("Channel_Response_Rule", "Response the Channel Rule", commandID);
		case protocol::Channel_RequestAllPlayerList::packetID: return PacketInfo("Channel_RequestAllPlayerList", "Request Channel All Player List", commandID);
		case protocol::Channel_ResponseAllPlayerList::packetID: return PacketInfo("Channel_ResponseAllPlayerList", "Response Channel All Player List", commandID);
		case protocol::Stage_Create::packetID: return PacketInfo("Stage_Create", "Create a Stage", commandID);
		case protocol::Stage_RequestJoin::packetID: return PacketInfo("Stage_RequestJoin", "Request Join a Stage", commandID);
		case protocol::Stage_RequestPrivateJoin::packetID: return PacketInfo("Stage_RequestPrivateJoin", "Request Join a Private Stage", commandID);
		case protocol::Stage_Join::packetID: return PacketInfo("Stage_Join", "Join a Stage", commandID);
		case protocol::Stage_Leave::packetID: return PacketInfo("Stage_Leave", "Leave Stage", commandID);
		case protocol::Stage_Request_PlayerList::packetID: return PacketInfo("Stage_Request_PlayerList", "Requst PlayerList from the Stage", commandID);
		case protocol::Stage_Follow::packetID: return PacketInfo("Stage_Follow", "Follow User to Stage", commandID);
		case protocol::Stage_Response_Follow::packetID: return PacketInfo("Stage_Response_Follow", "Response Follow User to Stage", commandID);
		case protocol::Stage_ResponseJoin::packetID: return PacketInfo("Stage_ResponseJoin", "Response Join a Stage", commandID);
		case protocol::Stage_RequirePassword::packetID: return PacketInfo("Stage_RequirePassword", "Require password", commandID);
		case protocol::RequestGameInfo::packetID: return PacketInfo("RequestGameInfo", "Request Game Info", commandID);
		case protocol::ResponseGameInfo::packetID: return PacketInfo("ResponseGameInfo", "Response Game Info", commandID);
		case protocol::Stage_ResponseCreate::packetID: return PacketInfo("Stage_ResponseCreate", "Response Create a Stage", commandID);
		case protocol::Stage_Request_EnterBattle::packetID: return PacketInfo("Stage_Request_EnterBattle", "Request Enter Stage Battle", commandID);
		case protocol::Stage_EnterBattle::packetID: return PacketInfo("Stage_EnterBattle", "Enter Stage Battle", commandID);
		case protocol::Stage_LeaveBattle::packetID: return PacketInfo("Stage_LeaveBattle", "Leave Stage Battle", commandID);
		case protocol::Stage_Start::packetID: return PacketInfo("Stage_Start", "Start Stage", commandID);
		case protocol::Stage_Map::packetID: return PacketInfo("Stage_Map", "Change Map", commandID);
		case protocol::Stage_Chat::packetID: return PacketInfo("Stage_Chat", "Chat to Stage", commandID);
		case protocol::Stage_RequestQuickJoin::packetID: return PacketInfo("Stage_RequestQuickJoin", "Stage Request QuickJoin", commandID);
		case protocol::Stage_ResponseQuickJoin::packetID: return PacketInfo("Stage_ResponseQuickJoin", "Stage Response QuickJoin", commandID);
		case protocol::Stage_StageGo::packetID: return PacketInfo("Stage_StageGo", "Stage Go", commandID);
		case protocol::Stage_State::packetID: return PacketInfo("Stage_State", "Change State In Stage", commandID);
		case protocol::Stage_Team::packetID: return PacketInfo("Stage_Team", "Change Team", commandID);
		case protocol::Stage_Master::packetID: return PacketInfo("Stage_Master", "Set Master", commandID);
		case protocol::Stage_ListStart::packetID: return PacketInfo("Stage_ListStart", "Stage List transmit start", commandID);
		case protocol::Stage_ListStop::packetID: return PacketInfo("Stage_ListStop", "Stage List transmit stop", commandID);
		case protocol::Stage_List::packetID: return PacketInfo("Stage_List", "Stage List", commandID);
		case protocol::Stage_RequestStageList::packetID: return PacketInfo("Stage_RequestStageList", "Request Stage List", commandID);
		case protocol::Channel_RequestPlayerList::packetID: return PacketInfo("Channel_RequestPlayerList", "Request Channel Player List", commandID);
		case protocol::Channel_ResponsePlayerList::packetID: return PacketInfo("Channel_ResponsePlayerList", "Response Channel Player List", commandID);
		case protocol::Stage_RequestStageSetting::packetID: return PacketInfo("Stage_RequestStageSetting", "Request stage setting", commandID);
		case protocol::Stage_ResponseStageSetting::packetID: return PacketInfo("Stage_ResponseStageSetting", "Response stage setting", commandID);
		case protocol::Stage_StageSetting::packetID: return PacketInfo("Stage_StageSetting", "Setting up Stage", commandID);
		case protocol::Stage_Launch::packetID: return PacketInfo("Stage_Launch", "Launch Stage", commandID);
		case protocol::Stage_Finish::packetID: return PacketInfo("Stage_Finish", "Finish Stage", commandID);
		case protocol::Stage_RequestPeerList::packetID: return PacketInfo("Stage_RequestPeerList", "Request peer list", commandID);
		case protocol::Stage_ResponsePeerList::packetID: return PacketInfo("Stage_ResponsePeerList", "Response peer list", commandID);
		case protocol::Loading_Complete::packetID: return PacketInfo("Loading_Complete", "Loading Complete", commandID);
		case protocol::Match_RequestPeerRelay::packetID: return PacketInfo("Match_RequestPeerRelay", "Request Peer Relay", commandID);
		case protocol::Match_ResponsePeerRelay::packetID: return PacketInfo("Match_ResponsePeerRelay", "Response Peer Relay", commandID);
		case protocol::Stage_RoundState::packetID: return PacketInfo("Stage_RoundState", "Sync State of a StageRound", commandID);
		case protocol::Game_Kill::packetID: return PacketInfo("Game_Kill", "Object Die", commandID);
		case protocol::Game_Requst_Spawn::packetID: return PacketInfo("Game_Requst_Spawn", "Request Spawn", commandID);
		case protocol::Game_LevelUp::packetID: return PacketInfo("Game_LevelUp", "Game.LevelUp", commandID);
		case protocol::Game_LevelDown::packetID: return PacketInfo("Game_LevelDown", "Game.LevelDown", commandID);
		case protocol::Game_Dead::packetID: return PacketInfo("Game_Dead", "Game.Dead", commandID);
		case protocol::Game_TeamBonus::packetID: return PacketInfo("Game_TeamBonus", "Game.TeamBonus", commandID);
		case protocol::Game_RequestTimeSync::packetID: return PacketInfo("Game_RequestTimeSync", "Request TimeSync for Game", commandID);
		case protocol::Game_ResponseTimeSync::packetID: return PacketInfo("Game_ResponseTimeSync", "Response TimeSync for Game", commandID);
		case protocol::Game_ReportTimeSync::packetID: return PacketInfo("Game_ReportTimeSync", "Report TimeSync for Verify SpeedHack", commandID);
		case protocol::Stage_RequestForcedEntry::packetID: return PacketInfo("Stage_RequestForcedEntry", "Request Forced Entry", commandID);
		case protocol::Stage_ResponseForcedEntry::packetID: return PacketInfo("Stage_ResponseForcedEntry", "Response Forced Entry", commandID);
		case protocol::Stage_RoundFinishInfo::packetID: return PacketInfo("Stage_RoundFinishInfo", "Update Round Finished Info", commandID);
		case protocol::Match_Notify::packetID: return PacketInfo("Match_Notify", "Notify Message", commandID);
		case protocol::Match_Whisper::packetID: return PacketInfo("Match_Whisper", "Whisper Message to a User", commandID);
		case protocol::Match_Where::packetID: return PacketInfo("Match_Where", "Ask Player Location", commandID);
		case protocol::Match_UserOption::packetID: return PacketInfo("Match_UserOption", "Set User Option", commandID);
		case protocol::ChatRoom_Create::packetID: return PacketInfo("ChatRoom_Create", "Create a ChatRoom", commandID);
		case protocol::ChatRoom_Join::packetID: return PacketInfo("ChatRoom_Join", "Join a ChatRoom", commandID);
		case protocol::ChatRoom_Leave::packetID: return PacketInfo("ChatRoom_Leave", "Leave a Chat Room", commandID);
		case protocol::ChatRoom_SelectWrite::packetID: return PacketInfo("ChatRoom_SelectWrite", "Select ChatRoom to Write", commandID);
		case protocol::ChatRoom_Invite::packetID: return PacketInfo("ChatRoom_Invite", "Invite a user to ChatRoom", commandID);
		case protocol::ChatRoom_Chat::packetID: return PacketInfo("ChatRoom_Chat", "ChatRoom Chat", commandID);
		case protocol::Match_RequestAccountCharList::packetID: return PacketInfo("Match_RequestAccountCharList", "Request Account Character List", commandID);
		case protocol::Match_ResponseAccountCharList::packetID: return PacketInfo("Match_ResponseAccountCharList", "Response Account Character List", commandID);
		case protocol::Match_RequestAccountCharInfo::packetID: return PacketInfo("Match_RequestAccountCharInfo", "Request Account Character Info", commandID);
		case protocol::Match_ResponseAccountCharInfo::packetID: return PacketInfo("Match_ResponseAccountCharInfo", "Response Account Character Info", commandID);
		case protocol::Match_RequestSelectChar::packetID: return PacketInfo("Match_RequestSelectChar", "Request Select Character", commandID);
		case protocol::Match_ResponseSelectChar::packetID: return PacketInfo("Match_ResponseSelectChar", "Response Select Character", commandID);
		case protocol::Match_RequestCharInfo::packetID: return PacketInfo("Match_RequestCharInfo", "Request Character Info", commandID);
		case protocol::Match_ResponseCharInfo::packetID: return PacketInfo("Match_ResponseCharInfo", "Response Character Info", commandID);
		case protocol::Match_RequestDeleteChar::packetID: return PacketInfo("Match_RequestDeleteChar", "Request Delete Character", commandID);
		case protocol::Match_ResponseDeleteChar::packetID: return PacketInfo("Match_ResponseDeleteChar", "Response Delete Character", commandID);
		case protocol::Match_RequestCreateChar::packetID: return PacketInfo("Match_RequestCreateChar", "Request Create Character", commandID);
		case protocol::Match_ResponseCreateChar::packetID: return PacketInfo("Match_ResponseCreateChar", "Response Create Character", commandID);
		case protocol::Match_RequestBuyItem::packetID: return PacketInfo("Match_RequestBuyItem", "Request Buy Item", commandID);
		case protocol::Match_ResponseBuyItem::packetID: return PacketInfo("Match_ResponseBuyItem", "Response Buy Item", commandID);
		case protocol::Match_RequestSellItem::packetID: return PacketInfo("Match_RequestSellItem", "Request Sell Item", commandID);
		case protocol::Match_ResponseSellItem::packetID: return PacketInfo("Match_ResponseSellItem", "Response Sell Item", commandID);
		case protocol::Match_RequestShopItemList::packetID: return PacketInfo("Match_RequestShopItemList", "Request Shop Item List", commandID);
		case protocol::Match_ResponseShopItemList::packetID: return PacketInfo("Match_ResponseShopItemList", "Response Shop Item List", commandID);
		case protocol::Match_RequestCharacterItemList::packetID: return PacketInfo("Match_RequestCharacterItemList", "Request Character Item List", commandID);
		case protocol::Match_RequestCharacterItemListForce::packetID: return PacketInfo("Match_RequestCharacterItemListForce", "Request Character Item List NonPrevent Duplicate Send", commandID);
		case protocol::Match_ResponseCharacterItemList::packetID: return PacketInfo("Match_ResponseCharacterItemList", "Response Character Item List", commandID);
		case protocol::MatchRequestEquipItem::packetID: return PacketInfo("MatchRequestEquipItem", "Request Equip Item", commandID);
		case protocol::MatchResponseEquipItem::packetID: return PacketInfo("MatchResponseEquipItem", "Response Equip Item", commandID);
		case protocol::MatchRequestTakeoffItem::packetID: return PacketInfo("MatchRequestTakeoffItem", "Request Takeoff Item", commandID);
		case protocol::MatchResponseTakeoffItem::packetID: return PacketInfo("MatchResponseTakeoffItem", "Response Takeoff Item", commandID);
		case protocol::Match_RequestAccountItemList::packetID: return PacketInfo("Match_RequestAccountItemList", "Request Account Item List", commandID);
		case protocol::Match_ResponseAccountItemList::packetID: return PacketInfo("Match_ResponseAccountItemList", "Response Account Item List", commandID);
		case protocol::Match_RequestBringAccountItem::packetID: return PacketInfo("Match_RequestBringAccountItem", "Request Bring Account Item", commandID);
		case protocol::Match_ResponseBringAccountItem::packetID: return PacketInfo("Match_ResponseBringAccountItem", "Response Bring Account Item", commandID);
		case protocol::Match_RequestBringBackAccountItem::packetID: return PacketInfo("Match_RequestBringBackAccountItem", "Request BringBack Account Item", commandID);
		case protocol::Match_ResponseBringBackAccountItem::packetID: return PacketInfo("Match_ResponseBringBackAccountItem", "Response BringBack Account Item", commandID);
		case protocol::Match_ExpiredRentItem::packetID: return PacketInfo("Match_ExpiredRentItem", "Match.Expired Rent Item", commandID);
		case protocol::Match_ItemGamble::packetID: return PacketInfo("Match_ItemGamble", "Request Item Gamble", commandID);
		case protocol::Match_GambleResultItem::packetID: return PacketInfo("Match_GambleResultItem", "Response Item Gamble Result Item", commandID);
		case protocol::Match_Request_Suicide::packetID: return PacketInfo("Match_Request_Suicide", "Request Suicide", commandID);
		case protocol::Match_Response_Suicide::packetID: return PacketInfo("Match_Response_Suicide", "Response Suicide", commandID);
		case protocol::Match_Response_SuicideReserve::packetID: return PacketInfo("Match_Response_SuicideReserve", "response suicide reserve", commandID);
		case protocol::Match_Request_Obtain_WorldItem::packetID: return PacketInfo("Match_Request_Obtain_WorldItem", "Request Obtain WorldItem", commandID);
		case protocol::Match_WorldItem_Obtain::packetID: return PacketInfo("Match_WorldItem_Obtain", "Obtain WorldItem", commandID);
		case protocol::Match_WorldItem_Spawn::packetID: return PacketInfo("Match_WorldItem_Spawn", "Spawn WorldItem", commandID);
		case protocol::Match_Request_Spawn_WorldItem::packetID: return PacketInfo("Match_Request_Spawn_WorldItem", "Request Spawn WorldItem", commandID);
		case protocol::Match_Request_Spawn_WorldItem_UID::packetID: return PacketInfo("Match_Request_Spawn_WorldItem_UID", "Request Spawn WorldItem", commandID);
		case protocol::Match_Reset_TeamMembers::packetID: return PacketInfo("Match_Reset_TeamMembers", "Reset Team Members", commandID);
		case protocol::Match_Assign_Commander::packetID: return PacketInfo("Match_Assign_Commander", "Assign Commander", commandID);
		case protocol::Match_Set_Observer::packetID: return PacketInfo("Match_Set_Observer", "Set Observer", commandID);
		case protocol::Match_Ladder_Request_Challenge::packetID: return PacketInfo("Match_Ladder_Request_Challenge", "Request Challenge a Ladder", commandID);
		case protocol::Match_Ladder_Response_Challenge::packetID: return PacketInfo("Match_Ladder_Response_Challenge", "Response Challenge a Ladder", commandID);
		case protocol::Match_Ladder_SearchRival::packetID: return PacketInfo("Match_Ladder_SearchRival", "Search a Ladder Rival", commandID);
		case protocol::Match_Ladder_Request_CancelChallenge::packetID: return PacketInfo("Match_Ladder_Request_CancelChallenge", "Request Cancel Challenge", commandID);
		case protocol::Match_Ladder_CancelChallenge::packetID: return PacketInfo("Match_Ladder_CancelChallenge", "Cancel Ladder Challenge", commandID);
		case protocol::Ladder_Prepare::packetID: return PacketInfo("Ladder_Prepare", "Prepare Ladder Game", commandID);
		case protocol::Ladder_Launch::packetID: return PacketInfo("Ladder_Launch", "Launch Ladder Game", commandID);
		case protocol::Match_RequestProposal::packetID: return PacketInfo("Match_RequestProposal", "Request Proposal", commandID);
		case protocol::Match_ResponseProposal::packetID: return PacketInfo("Match_ResponseProposal", "Response Proposal", commandID);
		case protocol::Match_AskAgreement::packetID: return PacketInfo("Match_AskAgreement", "Ask Agreement", commandID);
		case protocol::Match_ReplyAgreement::packetID: return PacketInfo("Match_ReplyAgreement", "Reply Agreement", commandID);
		case protocol::Match_Friend_Add::packetID: return PacketInfo("Match_Friend_Add", "Add a Friend", commandID);
		case protocol::Match_Friend_Remove::packetID: return PacketInfo("Match_Friend_Remove", "Remove a Friend", commandID);
		case protocol::Match_Friend_List::packetID: return PacketInfo("Match_Friend_List", "List Friend", commandID);
		case protocol::Match_Response_FriendList::packetID: return PacketInfo("Match_Response_FriendList", "Response List Friend", commandID);
		case protocol::Match_Friend_Msg::packetID: return PacketInfo("Match_Friend_Msg", "Message to Friends", commandID);
		case protocol::Match_Clan_RequestCreateClan::packetID: return PacketInfo("Match_Clan_RequestCreateClan", "Request Create Clan", commandID);
		case protocol::Match_Clan_ResponseCreateClan::packetID: return PacketInfo("Match_Clan_ResponseCreateClan", "Response Create Clan", commandID);
		case protocol::Match_Clan_AskSponsorAgreement::packetID: return PacketInfo("Match_Clan_AskSponsorAgreement", "Ask Sponsor's Agreement", commandID);
		case protocol::Match_Clan_AnswerSponsorAgreement::packetID: return PacketInfo("Match_Clan_AnswerSponsorAgreement", "Answer Sponsor's Agreement", commandID);
		case protocol::Match_Clan_RequestAgreedCreateClan::packetID: return PacketInfo("Match_Clan_RequestAgreedCreateClan", "Request Agreed Create Clan", commandID);
		case protocol::Match_Clan_AgreedResponseCreateClan::packetID: return PacketInfo("Match_Clan_AgreedResponseCreateClan", "Response Agreed Create Clan", commandID);
		case protocol::Match_Clan_RequestCloseClan::packetID: return PacketInfo("Match_Clan_RequestCloseClan", "Request Close Clan", commandID);
		case protocol::Match_Clan_ResponseCloseClan::packetID: return PacketInfo("Match_Clan_ResponseCloseClan", "Response Close Clan", commandID);
		case protocol::Match_Clan_RequestJoinClan::packetID: return PacketInfo("Match_Clan_RequestJoinClan", "Request Join Clan", commandID);
		case protocol::Match_Clan_ResponseJoinClan::packetID: return PacketInfo("Match_Clan_ResponseJoinClan", "Response Join Clan", commandID);
		case protocol::Match_Clan_AskJoinAgreement::packetID: return PacketInfo("Match_Clan_AskJoinAgreement", "Ask Join Agreement", commandID);
		case protocol::Match_Clan_AnswerJoinAgreement::packetID: return PacketInfo("Match_Clan_AnswerJoinAgreement", "Answer Join Agreement", commandID);
		case protocol::Match_Clan_RequestAgreedJoinClan::packetID: return PacketInfo("Match_Clan_RequestAgreedJoinClan", "Request Agreed Join Clan", commandID);
		case protocol::Match_Clan_ResponseAgreedJoinClan::packetID: return PacketInfo("Match_Clan_ResponseAgreedJoinClan", "Response Agreed Join Clan", commandID);
		case protocol::Match_Clan_RequestLeaveClan::packetID: return PacketInfo("Match_Clan_RequestLeaveClan", "Request Leave Clan", commandID);
		case protocol::Match_Clan_ResponseLeaveClan::packetID: return PacketInfo("Match_Clan_ResponseLeaveClan", "Response Leave Clan", commandID);
		case protocol::Match_Clan_UpdateCharClanInfo::packetID: return PacketInfo("Match_Clan_UpdateCharClanInfo", "Update Char ClanInfo", commandID);
		case protocol::Match_Clan_Master_RequestChangeGrade::packetID: return PacketInfo("Match_Clan_Master_RequestChangeGrade", "Request Change ClanGrade", commandID);
		case protocol::Match_Clan_Master_ResponseChangeGrade::packetID: return PacketInfo("Match_Clan_Master_ResponseChangeGrade", "Response Change ClanGrade", commandID);
		case protocol::Match_Clan_Admin_RequestExpelMember::packetID: return PacketInfo("Match_Clan_Admin_RequestExpelMember", "Request Expel ClanMember", commandID);
		case protocol::Match_Clan_Admin_ResponseLeaveMember::packetID: return PacketInfo("Match_Clan_Admin_ResponseLeaveMember", "Response Expel ClanMember", commandID);
		case protocol::Match_Clan_Request_Msg::packetID: return PacketInfo("Match_Clan_Request_Msg", "Request Clan Msg", commandID);
		case protocol::Match_Clan_Msg::packetID: return PacketInfo("Match_Clan_Msg", "Clan Msg", commandID);
		case protocol::Match_Clan_Request_ClanMemberList::packetID: return PacketInfo("Match_Clan_Request_ClanMemberList", "Request Clan Member List", commandID);
		case protocol::Match_Clan_Response_ClanMemberList::packetID: return PacketInfo("Match_Clan_Response_ClanMemberList", "Response Clan Member List", commandID);
		case protocol::Match_Clan_Request_Clan_Info::packetID: return PacketInfo("Match_Clan_Request_Clan_Info", "Request Clan Info", commandID);
		case protocol::Match_Clan_Response_Clan_Info::packetID: return PacketInfo("Match_Clan_Response_Clan_Info", "Response Clan Info", commandID);
		case protocol::Match_Clan_Standby_ClanList::packetID: return PacketInfo("Match_Clan_Standby_ClanList", "Standby Clan List", commandID);
		case protocol::Match_Clan_Member_Connected::packetID: return PacketInfo("Match_Clan_Member_Connected", "Member Connected", commandID);
		case protocol::Match_Clan_Request_EmblemURL::packetID: return PacketInfo("Match_Clan_Request_EmblemURL", "Request EmblemURL", commandID);
		case protocol::Match_Clan_Response_EmblemURL::packetID: return PacketInfo("Match_Clan_Response_EmblemURL", "Response EmblemURL", commandID);
		case protocol::Match_Clan_Local_EmblemReady::packetID: return PacketInfo("Match_Clan_Local_EmblemReady", "Notify Emblem Ready", commandID);
		case protocol::MC_MATCH_CLAN_ACCOUNCE_DELETE::packetID: return PacketInfo("MC_MATCH_CLAN_ACCOUNCE_DELETE", "delete clan info announce to clan member", commandID);
		case protocol::Match_Callvote::packetID: return PacketInfo("Match_Callvote", "Callvote", commandID);
		case protocol::Match_NotifyCallvote::packetID: return PacketInfo("Match_NotifyCallvote", "Notify Callvote", commandID);
		case protocol::Match_NotifyVoteResult::packetID: return PacketInfo("Match_NotifyVoteResult", "Notify Vote Result", commandID);
		case protocol::Match_VoteYes::packetID: return PacketInfo("Match_VoteYes", "Vote", commandID);
		case protocol::Match_VoteNo::packetID: return PacketInfo("Match_VoteNo", "Vote", commandID);
		case protocol::Votestop::packetID: return PacketInfo("Votestop", "Vote stop", commandID);
		case protocol::Match_Broadcast_ClanRenewVictories::packetID: return PacketInfo("Match_Broadcast_ClanRenewVictories", "Broadcast Clan Renew Victories", commandID);
		case protocol::Match_Broadcast_ClanInterruptVictories::packetID: return PacketInfo("Match_Broadcast_ClanInterruptVictories", "Broadcast Clan Interrupt Victories", commandID);
		case protocol::Match_Broadcast_DuelRenewVictories::packetID: return PacketInfo("Match_Broadcast_DuelRenewVictories", "Broadcast Duel Renew Victories", commandID);
		case protocol::Match_Broadcast_DuelInterruptVictories::packetID: return PacketInfo("Match_Broadcast_DuelInterruptVictories", "Broadcast Duel Interrupt Victories", commandID);
		case protocol::Match_Assign_Berserker::packetID: return PacketInfo("Match_Assign_Berserker", "Assign Berserker", commandID);
		case protocol::Match_Duel_QueueInfo::packetID: return PacketInfo("Match_Duel_QueueInfo", "Queue Info", commandID);
		case protocol::Match_Quest_Ping::packetID: return PacketInfo("Match_Quest_Ping", "QuestPing", commandID);
		case protocol::Match_Quest_Pong::packetID: return PacketInfo("Match_Quest_Pong", "QuestPong", commandID);
		case protocol::MC_QUEST_NPCLIST::packetID: return PacketInfo("MC_QUEST_NPCLIST", "Send npc info list to client.", commandID);
		case protocol::Event_ChangeMaster::packetID: return PacketInfo("Event_ChangeMaster", "Take out Master from Stage", commandID);
		case protocol::Event_ChangePassword::packetID: return PacketInfo("Event_ChangePassword", "Change Password on Stage", commandID);
		case protocol::Event_RequestJJang::packetID: return PacketInfo("Event_RequestJJang", "Request JJang mark to a Player", commandID);
		case protocol::Event_RemoveJJang::packetID: return PacketInfo("Event_RemoveJJang", "Remove JJang mark from a Player", commandID);
		case protocol::Event_UpdateJJang::packetID: return PacketInfo("Event_UpdateJJang", "Update JJang Player", commandID);
		case protocol::Quest_NPCSpawn::packetID: return PacketInfo("Quest_NPCSpawn", "Npc Spawn", commandID);
		case protocol::Quest_Entrust_NPC_Control::packetID: return PacketInfo("Quest_Entrust_NPC_Control", "Entrust Npc Control", commandID);
		case protocol::Quest_Checksum_NPCInfo::packetID: return PacketInfo("Quest_Checksum_NPCInfo", "Checksum NPC Info", commandID);
		case protocol::Quest_NPCDead::packetID: return PacketInfo("Quest_NPCDead", "Npc Dead", commandID);
		case protocol::Quest_RefreshPlayerStatus::packetID: return PacketInfo("Quest_RefreshPlayerStatus", "Refresh Player Status", commandID);
		case protocol::Quest_NPC_AllClear::packetID: return PacketInfo("Quest_NPC_AllClear", "Clear All NPC", commandID);
		case protocol::Quest_Round_Start::packetID: return PacketInfo("Quest_Round_Start", "Quest Start Round", commandID);
		case protocol::Quest_RequestDead::packetID: return PacketInfo("Quest_RequestDead", "Quest Request Dead", commandID);
		case protocol::Quest_PlayerDead::packetID: return PacketInfo("Quest_PlayerDead", "Quest Player Dead", commandID);
		case protocol::Quest_ObtainQuestItem::packetID: return PacketInfo("Quest_ObtainQuestItem", "Obtain QuestItem", commandID);
		case protocol::Quest_ObtainZItem::packetID: return PacketInfo("Quest_ObtainZItem", "Obtain ZItem", commandID);
		case protocol::Quest_State_Mapset::packetID: return PacketInfo("Quest_State_Mapset", "Change Stage Quest Mapset Setting", commandID);
		case protocol::Quest_Stage_GameInfo::packetID: return PacketInfo("Quest_Stage_GameInfo", "Quest Stage GameInfo", commandID);
		case protocol::Quest_SectorBonus::packetID: return PacketInfo("Quest_SectorBonus", "Quest Sector Bonus", commandID);
		case protocol::Quest_GameInfo::packetID: return PacketInfo("Quest_GameInfo", "Quest Game Info", commandID);
		case protocol::Quest_Combat_State::packetID: return PacketInfo("Quest_Combat_State", "Quest Combat State", commandID);
		case protocol::Quest_Sector_Start::packetID: return PacketInfo("Quest_Sector_Start", "Quest Sector Start", commandID);
		case protocol::Quest_Complete::packetID: return PacketInfo("Quest_Complete", "Complete Quest", commandID);
		case protocol::Quest_Failed::packetID: return PacketInfo("Quest_Failed", "Quest failed", commandID);
		case protocol::Quest_Request_Moveto_Portal::packetID: return PacketInfo("Quest_Request_Moveto_Portal", "Request Moveto Portal", commandID);
		case protocol::Quest_Moveto_Portal::packetID: return PacketInfo("Quest_Moveto_Portal", "Moveto Portal", commandID);
		case protocol::Quest_Readyto_NewSector::packetID: return PacketInfo("Quest_Readyto_NewSector", "Ready To New Sector", commandID);
		case protocol::Quest_Peer_NPC_BasicInfo::packetID: return PacketInfo("Quest_Peer_NPC_BasicInfo", "NPC BasicInfo", commandID);
		case protocol::Quest_Peer_NPC_HPInfo::packetID: return PacketInfo("Quest_Peer_NPC_HPInfo", "NPC HPInfo", commandID);
		case protocol::Quest_Peer_NPC_Attack_Melee::packetID: return PacketInfo("Quest_Peer_NPC_Attack_Melee", "NPC Melee Attack", commandID);
		case protocol::Quest_Peer_NPC_Attack_Range::packetID: return PacketInfo("Quest_Peer_NPC_Attack_Range", "NPC Range Attack", commandID);
		case protocol::Quest_Peer_NPC_Skill_Start::packetID: return PacketInfo("Quest_Peer_NPC_Skill_Start", "NPC Skill Start", commandID);
		case protocol::Quest_Peer_NPC_Skill_Execute::packetID: return PacketInfo("Quest_Peer_NPC_Skill_Execute", "NPC Skill Start", commandID);
		case protocol::Quest_Peer_NPC_Dead::packetID: return PacketInfo("Quest_Peer_NPC_Dead", "NPC Dead", commandID);
		case protocol::Quest_Test_RequestNPCSpawn::packetID: return PacketInfo("Quest_Test_RequestNPCSpawn", "NPC Spawn", commandID);
		case protocol::Quest_Test_ClearNPC::packetID: return PacketInfo("Quest_Test_ClearNPC", "Clear NPC", commandID);
		case protocol::Quest_Test_SectorClear::packetID: return PacketInfo("Quest_Test_SectorClear", "Sector Clear", commandID);
		case protocol::Quest_Test_Finish::packetID: return PacketInfo("Quest_Test_Finish", "Finish Quest", commandID);
		case protocol::Admin_Announce::packetID: return PacketInfo("Admin_Announce", "Announce", commandID);
		case protocol::Admin_RequestBanPlayer::packetID: return PacketInfo("Admin_RequestBanPlayer", "Request Ban Player", commandID);
		case protocol::Admin_ResponseBanPlayer::packetID: return PacketInfo("Admin_ResponseBanPlayer", "Response Ban Player", commandID);
		case protocol::Admin_Hide::packetID: return PacketInfo("Admin_Hide", "Hide Admin Player", commandID);
		case protocol::MC_ADMIN_RESET_ALL_HACKING_BLOCK::packetID: return PacketInfo("MC_ADMIN_RESET_ALL_HACKING_BLOCK", "reset all hacking block", commandID);
		case protocol::MC_ADMIN_RELOAD_GAMBLEITEM::packetID: return PacketInfo("MC_ADMIN_RELOAD_GAMBLEITEM", "reload gamble item info", commandID);
		case protocol::MC_ADMIN_ASSASIN::packetID: return PacketInfo("MC_ADMIN_ASSASIN", "choose admin as commander", commandID);
		case protocol::Agent_Connect::packetID: return PacketInfo("Agent_Connect", "Connect Agent to MatchServer", commandID);
		case protocol::Agent_Disconnect::packetID: return PacketInfo("Agent_Disconnect", "Unregister Agent from MatchServer", commandID);
		case protocol::Match_RegisterAgent::packetID: return PacketInfo("Match_RegisterAgent", "Register Agent to MatchServer", commandID);
		case protocol::Match_UnRegisterAgent::packetID: return PacketInfo("Match_UnRegisterAgent", "Unregister Agent from MatchServer", commandID);
		case protocol::Match_Agent_RequestLiveCheck::packetID: return PacketInfo("Match_Agent_RequestLiveCheck", "Request LiveCheck for Agent", commandID);
		case protocol::Match_Agent_ResponseLiveCheck::packetID: return PacketInfo("Match_Agent_ResponseLiveCheck", "Response LiveCheck for Agent", commandID);
		case protocol::Agent_StageReserve::packetID: return PacketInfo("Agent_StageReserve", "Reserve stage on AgentServer", commandID);
		case protocol::Agent_StageRelease::packetID: return PacketInfo("Agent_StageRelease", "Release stage on AgentServer", commandID);
		case protocol::Agent_StageReady::packetID: return PacketInfo("Agent_StageReady", "Ready to Handle stage", commandID);
		case protocol::Agent_RelayPeer::packetID: return PacketInfo("Agent_RelayPeer", "Let agent to Relay Peer", commandID);
		case protocol::Questitem::packetID: return PacketInfo("Questitem", "Request my quest item list", commandID);
		case protocol::Quest_item_response::packetID: return PacketInfo("Quest_item_response", "Response my quest item list", commandID);
		case protocol::Quest_item_buy::packetID: return PacketInfo("Quest_item_buy", "Request buy quest item", commandID);
		case protocol::Quest_item_responsebuy::packetID: return PacketInfo("Quest_item_responsebuy", "Response buy quest item", commandID);
		case protocol::Quest_item_sell::packetID: return PacketInfo("Quest_item_sell", "Request sell quest item", commandID);
		case protocol::Quest_item_responsesell::packetID: return PacketInfo("Quest_item_responsesell", "Response sell quest item", commandID);
		case protocol::Quest_Reward::packetID: return PacketInfo("Quest_Reward", "Quest reward.", commandID);
		case protocol::Quest_Request_Sacrifice::packetID: return PacketInfo("Quest_Request_Sacrifice", "Request drop sacrifice item", commandID);
		case protocol::Quest_Response_Sacrifice::packetID: return PacketInfo("Quest_Response_Sacrifice", "Response drop sacrifice item", commandID);
		case protocol::Quest_Callback_Sacrifice::packetID: return PacketInfo("Quest_Callback_Sacrifice", "Request callback sacrifice item", commandID);
		case protocol::Quest_Callback_Result::packetID: return PacketInfo("Quest_Callback_Result", "Request callback sacrifice item", commandID);
		case protocol::Quest_Request_SlotInfo::packetID: return PacketInfo("Quest_Request_SlotInfo", "Request slot info", commandID);
		case protocol::Quest_Resonse_SlotInfo::packetID: return PacketInfo("Quest_Resonse_SlotInfo", "Response slot info", commandID);
		case protocol::Quest_RequestLevel::packetID: return PacketInfo("Quest_RequestLevel", "Request stage quest level", commandID);
		case protocol::Quest_ResponseLevel::packetID: return PacketInfo("Quest_ResponseLevel", "Response stage quest level", commandID);
		case protocol::Quest_Survival_Result::packetID: return PacketInfo("Quest_Survival_Result", "Send survival result", commandID);
		case protocol::Quest_Survival_Ranking::packetID: return PacketInfo("Quest_Survival_Ranking", "Send survival top ranking list", commandID);
		case protocol::Quest_Survuval_PrivateRanking::packetID: return PacketInfo("Quest_Survuval_PrivateRanking", "Send survival private ranking", commandID);
		case protocol::Quest_Start_Fail::packetID: return PacketInfo("Quest_Start_Fail", "Failed start quest.", commandID);
		case protocol::monsterinfo::packetID: return PacketInfo("monsterinfo", "monster info", commandID);
		case protocol::Quest_Bible_Request::packetID: return PacketInfo("Quest_Bible_Request", "request monster bible info", commandID);
		case protocol::Quest_Bible_Response::packetID: return PacketInfo("Quest_Bible_Response", "response monster bible info", commandID);
		case protocol::MC_REQUEST_GIVE_ONESELF_UP::packetID: return PacketInfo("MC_REQUEST_GIVE_ONESELF_UP", "give oneself up", commandID);
		case protocol::MC_RESPONSE_GAMBLEITEMLIST::packetID: return PacketInfo("MC_RESPONSE_GAMBLEITEMLIST", "send gamble item info list to client", commandID);
		case protocol::MC_MATCH_ROUTE_UPDATE_STAGE_EQUIP_LOOK::packetID: return PacketInfo("MC_MATCH_ROUTE_UPDATE_STAGE_EQUIP_LOOK", "route updated user equip info", commandID);
		case protocol::MC_REQUEST_RESOURCE_CRC32::packetID: return PacketInfo("MC_REQUEST_RESOURCE_CRC32", "MC_REQUEST_RESOURCE_CRC32", commandID);
		case protocol::MC_RESPONSE_RESOURCE_CRC32::packetID: return PacketInfo("MC_RESPONSE_RESOURCE_CRC32", "MC_RESPONSE_RESOURCE_CRC32", commandID);
		default: throw BadCommandId(commandID);
	}
}

}
}
