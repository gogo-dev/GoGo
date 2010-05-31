#pragma once
#include <boost/cstdint.hpp>

struct AccountInfo
{
	boost::uint32_t AccountId;
	std::string AccountName;
	boost::uint8_t AccountAccess;
	boost::uint8_t AccountPremium;
};
