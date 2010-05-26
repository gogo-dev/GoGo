#include "Structures.h"

packet::blob CharacterInfo::blobify()
{
	packet::blob charBlob(1, 146);

	charBlob.addParam(packet::string(CharacterName, 32));
	charBlob.addParam(packet::string(ClanName, 16));
	charBlob.addParam(packet::int32(CharacterGrade));
	charBlob.addParam(packet::int32(ClanPoints));
	charBlob.addParam(packet::uint8(CharacterMarker));
	charBlob.addParam(packet::uint16(CharacterLevel));
	charBlob.addParam(packet::uint8(CharacterSex));
	charBlob.addParam(packet::uint8(CharacterHair));
	charBlob.addParam(packet::uint8(CharacterFace));
	charBlob.addParam(packet::int32(CharacterXP));
	charBlob.addParam(packet::int32(CharacterBP));
	charBlob.addParam(packet::floating_point(0.0f));	//Yawn. Bonus Rate.
	charBlob.addParam(packet::int32(0));	//Prize/HP
	charBlob.addParam(packet::int32(0));	//AP/Weight
	charBlob.addParam(packet::int32(0));	//SasfeFall/FR
	charBlob.addParam(packet::int32(0));	// CR/ER
	charBlob.addParam(packet::uint16(0));	// WR

	for (int i = 0; i < 12; ++i)
		charBlob.addParam(packet::int32 (Equipment[i].ItemID));

	charBlob.addParam(packet::int32(CharacterAccess));
	charBlob.addParam(packet::int32(ClanId));
	return charBlob;
}