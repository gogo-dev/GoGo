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

	~BannedUser() throw()
	{
	}
};

class InvalidCharacterInfo : public std::exception
{
public:
	virtual const char* what() throw()
	{
		return "Invalid character info!";
	}
};

class InvalidCID : public std::exception
{
public:
	virtual const char* what() throw()
	{
		return "Invalid CID!";
	}
};

class NameInUse : public std::exception
{
public: 
	virtual const char* what() throw()
	{
		return "Character name is in use!";
	}
};
