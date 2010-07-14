#pragma once
#include <string>
#include <boost/cstdint.hpp>

struct AccountInfo
{
	boost::uint32_t aid;
	std::string name;
	boost::uint8_t access;
	boost::uint8_t pgradeid;

	bool isValid;

	// This is very dangerous. We shouldn't be doing this, but its necessary
	// for it to be allocated with GoGoClient.
	AccountInfo()
		: aid(0xFFFFFFFF), isValid(false)
	{
	}

	AccountInfo(
		boost::uint32_t _aid,
		const std::string& _name,
		boost::uint8_t _access,
		boost::uint8_t _pgradeid)
		: aid(_aid),
		  name(_name),
		  access(_access),
		  pgradeid(_pgradeid),
		  isValid(true)
	{
	}
};
