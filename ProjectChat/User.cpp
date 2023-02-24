#include "User.h"
#include <iostream>

User::User(std::string& name, const std::string& login, const std::string& password) :_name(name), _login(login), _password(password) {}

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

std::ifstream& operator >>(std::ifstream& is, User& obj)
{
	is >> obj._name;
	is >> obj._login;
	is >> obj._password;
	return is;
}

std::ostream& operator <<(std::ostream& os, const User& obj)
{
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._password;
	os << '\n';
	return os;
}