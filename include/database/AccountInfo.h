#pragma once
#include <string>
#include <boost/cstdint.hpp>

struct AccountInfo
{
	boost::uint32_t AccountId;
	std::string AccountName;
	boost::uint8_t AccountAccess;
	boost::uint8_t AccountPremium;

	AccountInfo ()
	{
		AccountId = -1;
		AccountName = "";
		AccountAccess = 0;
		AccountPremium = 0;
	}

};
