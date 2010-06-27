#pragma once
#include <string>
#include <boost/cstdint.hpp>

struct AccountInfo
{
	boost::uint32_t AccountId;
	std::string AccountName;
	boost::uint8_t AccountAccess;
	boost::uint8_t AccountPremium;

	bool isValid;

	// This is very dangerous. We shouldn't be doing this, but its necessary
	// for it to be allocated with GoGoClient.
	AccountInfo()
		: AccountId(0xFFFFFFFF), isValid(false)
	{
	}

	AccountInfo(
		boost::uint32_t accountID,
		const std::string& accountName,
		boost::uint8_t accountAccess,
		boost::uint8_t accountPremium)
		: AccountId(accountID),
		  AccountName(accountName),
		  AccountAccess(accountAccess),
		  AccountPremium(accountPremium),
		  isValid(true)
	{
	}

};
