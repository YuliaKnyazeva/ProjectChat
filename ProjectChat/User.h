#pragma once
#include <string>

class User
{
private:
	std::string _name;
	std::string _login;
	std::string _password;
public:
	User() = default;
	virtual ~User() = default;
	User(std::string Name, const std::string& Login, const std::string& Password);
	const std::string &getName();
	const std::string &getLogin();
	const std::string &getPassword();
};

