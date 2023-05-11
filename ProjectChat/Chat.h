#pragma once
#include <winsock2.h>
#define PORT 7777
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable:4996)
#include "User.h"
#include "Message.h"
#include <vector>
#include <string>
#include <memory>



class Chat
{
	bool _chatWork = false;
	std:: vector<User> _users;
	std:: vector<Message> _messages;
	std:: shared_ptr < User > _currentUser = nullptr;
	void signUp();
	void signIn();
	bool checkUser(const std::string& login, const std::string& password);
	void sendMessage(const std::string& login);
	void ShowMessages(const std::string& login);
	void ShowUsers();
	WSADATA _wsaData;
	SOCKADDR_IN _addr;
	SOCKET _Connection;
	void Disconnect();
	void Connect();
public:
	void startWork();
	const bool getChatWork() const;
	const std::shared_ptr<User> getCurrentUser() const;
	void showStartMenu();
	void showUserMenu();
};

