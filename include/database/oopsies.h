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

	BannedUser(const std::string& account)
	{
		error = std::string("Account is banned: ") + account + "!";
	}

	virtual const char* what() const throw()
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
	virtual const char* what() const throw()
	{
		return "Invalid character info!";
	}
};

class InvalidCID : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Invalid CID!";
	}
};

class NameInUse : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Character name is in use!";
	}
};

class InvalidCharacterName : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Invalid character name!";
	}
};

/**
	This is thrown whenever there's an error in the database. An error message
	will be printed, so there's no need to do that yourself. The best thing to
	do when this is thrown is to just work around the error as best as you can.
*/
class InternalDatabaseError : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Internal Database Error!";
	}
};
