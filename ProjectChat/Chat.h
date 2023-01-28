#pragma once
#include "User.h"
#include "Message.h"
#include <vector>
#include <string>


class Chat
{
	std:: vector<User> users;
	std:: vector<Message> messages;
public:
	void signUp();
	void signIn();
	bool checkUser(const std::string& login, const std::string& password);
	void addMessage(const std::string& login);
	void showMessage(const std::string& login);
	void showUsers();
	void checkLogin(const std::string& Login);
};

