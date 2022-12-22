#include "User.h"
#include <iostream>

User::User(std::string name, const std::string& login, const std::string& password) :_name(name), _login(login), _password(password) {}

const std::string &User::getName()
{
	return _name;
}

const std::string &User::getLogin()
{
	return _login;
}

const std::string &User::getPassword()
{
	return _password;
}
