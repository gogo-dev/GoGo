#pragma once
#include <exception>

class InvalidAccountInfo : public std::exception
{
public:
	virtual const char* what() throw()
	{
		return "Invalid account info!";
	}
};

class InvalidCharacterInfo : public std::exception
{
	virtual const char* what() throw()
	{
		return "Invalid character info!";
	}
};

class InvalidCID : public std::exception
{
	virtual const char* what() throw()
	{
		return "Invalid CID!";
	}
};