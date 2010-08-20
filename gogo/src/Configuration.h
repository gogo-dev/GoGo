#pragma once
#include <istream>
#include <stdexcept>
#include <string>
#include <cstddef>

#include <boost/call_traits.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>

#include <cstdio>

struct SyntaxError : public std::runtime_error
{
	size_t lineNumber;

	SyntaxError(const char* message, size_t lineNumber);
};

class Configuration
{
private:
	// Why is this a hashmap? The hashing means the lookup string is only
	// iterated through once instead of log(n) times.
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
	Configuration(const Configuration& rhs);

#ifdef BOOST_HAS_RVALUE_REFS
	Configuration(std::istream&& stream);
	Configuration(const Configuration&& rhs);
#endif

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
		} catch(const boost::bad_lexical_cast&) {
			return defaultValue;
		}
	}

	/**
		Returns the value of type T that is matched with the given key inside
		the configuration. If the value is not present, std::runtime_error is
		thrown.

		@throws std::runtime_error      If the key could not be found in the
		                                configuration file.

		@throws boost::bad_lexical_cast If the value could be found, but
		                                casting it to the correct type failed.

		@param  key                     The key used to look up the correct value.

		@return                         The value for the requested key.
	*/
	template <typename T>
	T get_value(const std::string& key) const
	{
		ValueMap::const_iterator loc = values.find(key);

		if(loc == values.end())
			throw std::runtime_error("Key could not be found in the configuration file.");

		return boost::lexical_cast<T>(loc->second);
	}

	~Configuration();
};
