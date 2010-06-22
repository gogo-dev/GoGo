#pragma once
#include <exception>
#include <string>

class InvalidAccountInfo : public std::exception
{
public:
	virtual const char* what() throw()
	{
		return "Invalid account info!";
	}
};

class BannedUser : public std::exception
{
public:
	std::string error;

	BannedUser(std::string account)
	{
		error = std::string("Account is banned: ") + account + "!";
	}

	virtual const char* what() throw()
	{
		return error.c_str();
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
