#pragma once
#include <boost/cstdint.hpp>
#include <boost/test/minimal.hpp>
#include <string>

#define countof(arr) (sizeof(arr)/sizeof((arr)[0]))

struct HexChars
{
	char first;
	char second;
};

inline HexChars hexify(boost::uint8_t byte)
{
	static const char* hex = "0123456789ABCDEF";

	HexChars retVal;

	retVal.first  = hex[(byte >> 4) & 0x0F];
	retVal.second = hex[(byte >> 0) & 0x0F];

	return retVal;
}

inline std::string stringify(boost::uint8_t* data, size_t len)
{
	std::string retVal;

	retVal += '[';

	for(size_t i = 0; i < len; ++i)
	{
		HexChars chars = hexify(data[i]);

		retVal += chars.first;
		retVal += chars.second;

		retVal += " ";
	}

	retVal[retVal.length() - 1] = ']';

	return retVal;
}

#define check_array_equal(a, b, len) \
	do_check_array_equal(a, b, len, \
		__FILE__, __LINE__, BOOST_CURRENT_FUNCTION)

inline void do_check_array_equal(
	boost::uint8_t* a, boost::uint8_t* b, size_t len,
	const char* file, int line, const char* function)
{
	for(size_t i = 0; i < len; ++i)
	{
		if(a[i] != b[i])
		{
			boost::minimal_test::report_error(
				(stringify(a, len) + " != " + stringify(b, len)).c_str(),
				file,
				line,
				function,
				true
			);

			return;
		}
	}
}
