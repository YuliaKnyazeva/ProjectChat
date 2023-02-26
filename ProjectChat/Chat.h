#pragma once
#include "User.h"
#include "Message.h"
#include <vector>
#include <string>
#include <memory>
#include <fstream>


class Chat
{
	bool _chatWork = false;
	std:: vector<User> _users;
	std:: vector<Message> _messages;
	std:: shared_ptr < User > _currentUser = nullptr;
	void signUp();
	void signIn();
	bool checkUser(const std::string& login, const std::string& password);
	void addMessage(const std::string& login);
	void showMessage(const std::string& login);
	void showUsers();
	void checkLogin(const std::string& Login);
public:
	void startWork();
	const bool getChatWork();
	const std::shared_ptr<User> getCurrentUser();
	void showStartMenu();
	void showUserMenu();
	void saveUsers();
	void saveMessages();
	void loadUsers();
	void loadMessages();

};

