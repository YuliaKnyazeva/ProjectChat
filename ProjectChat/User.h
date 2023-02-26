#pragma once
#include <string>
#include <fstream>

class User
{
private:
	std::string _name;
	std::string _login;
	std::string _password;
public:
	User() = default;
	~User() = default;
	User(const std::string& name, const std::string& Login, const std::string& Password);
	const std::string &getName() const;
	const std::string &getLogin() const;
	const std::string &getPassword() const;
	friend std::ifstream& operator >>(std::ifstream& is, User& obj);
	friend std::ostream& operator <<(std::ostream& os, const User& obj);
};

