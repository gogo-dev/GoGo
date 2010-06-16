#pragma once
#include <istream>
#include <stdexcept>
#include <string>
#include <cstddef>

#include <boost/call_traits.hpp>
#include <boost/tr1/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

struct SyntaxError : public std::runtime_error
{
	size_t lineNumber;

	SyntaxError(const char* message, size_t lineNumber);
};

class Configuration
{
private:
	typedef boost::unordered_map<std::string, std::string> ValueMap;
	ValueMap values;

public:
	/**
		Loads the configuration from the passed stream. This can be a file, or
		any other stream imaginable!

		@throws SyntaxError Thrown when the configuration file has invalid
		                    syntax.
	*/
	Configuration(std::istream& stream);

	/**
		Returns the value of type T that is matched with the given key inside
		the configuration. If the value is not present, defaultValue is
		returned.

		@param  key             The key used to look up the correct value.
		@param  defaultValue    The value returned if the key is not found.

		@return                 The value for the requested key.
	*/
	template <typename T>
	T get_value(
		const std::string& key,
		typename boost::call_traits<T>::param_type defaultValue) const
	{
		ValueMap::const_iterator loc = values.find(key);

		if(loc == values.end())
			return defaultValue;

		try {
			return boost::lexical_cast<T>(loc->second);
		} catch(boost::bad_lexical_cast&) {
			return defaultValue;
		}
	}

	/**
		Returns the value of type T that is matched with the given key inside
		the configuration. If the value is not present, std::runtime_error is
		thrown.

		@throws std::runtime_error Thrown when the key could not be found.

		@param  key                The key used to look up the correct value.

		@return                    The value for the requested key.
	*/
	template <typename T>
	T get_value(const std::string& key) const
	{
		using namespace std;
		using namespace boost;

		ValueMap::const_iterator loc = values.find(key);

		if(loc == values.end())
			throw runtime_error((format("[%1% => ???] Could not find %1% in the configuration file.") % key.c_str()).str().c_str());

		try {
			return lexical_cast<T>(loc->second);
		} catch(bad_lexical_cast&) {
			throw runtime_error((format("[%1% => %2%] Result could not be coerced to the proper type.") % key.c_str() % loc->second).str().c_str());
		}
	}

	~Configuration();
};
