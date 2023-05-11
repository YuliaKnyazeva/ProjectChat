#include "Chat.h"
#include <iostream>


void Chat::Connect()
{
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &_wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(1);
	}

	int sizeofaddr = sizeof(_addr);
	_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_addr.sin_port = htons(PORT);
	_addr.sin_family = AF_INET;

	SOCKET CurrentConnection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(CurrentConnection, (SOCKADDR*)&_addr, sizeof(_addr)) != 0) {
		std::cout << "Connect failed" << std::endl;
		WSACleanup();
		exit(1);
	}
	_Connection=CurrentConnection;
	std::cout << "Connected" << std::endl;
}

void Chat::Disconnect()
{
	send(_Connection, "0", sizeof("0"), 0);
	closesocket(_Connection);
	WSACleanup();
}
void Chat:: startWork()
{
	Connect();
	_chatWork=true;
}

const bool Chat::getChatWork() const
{
	return _chatWork;
}

const std::shared_ptr<User> Chat::getCurrentUser() const
{
	return _currentUser;
}

void Chat::signUp() // Регистрация пользователя
{
	char buf[1024];
	send(_Connection, "1", sizeof("1"), 0);
	std::string name, login, password;
	std::cout << "Enter login" << std::endl;
	std::cin >> login;
	send(_Connection, login.c_str(), sizeof(login), 0);
	recv(_Connection, buf, sizeof(buf), 0);
	int temp = std::atoi(buf);
	if (temp==1) {
		std::cout << "Enter password" << std::endl;
		std::cin >> password;
		send(_Connection, password.c_str(), sizeof(password), 0);
		std::cout << "Enter your Name" << std::endl;
		std::cin >> name;
		send(_Connection, name.c_str(), sizeof(name), 0);
		_users.emplace_back(name, login, password);
	}
	else std::cout << "Login used" << std::endl;
}

void Chat::ShowMessages(const std::string& login)
{
	char buf[1024];
	send(_Connection, "21", sizeof("21"), 0);
	send(_Connection, login.c_str(), sizeof(login), 0);
	recv(_Connection, buf, sizeof(buf), 0);
	std::cout << buf << std::endl;
}

void Chat::sendMessage(const std::string& login) // Отправка сообщения
{
	send(_Connection, "22", sizeof("22"), 0);
	std::string from, to, text;
	send(_Connection, login.c_str(), sizeof(login), 0);
	from = login;
	std::cout << "Enter user name or 'all' for send all users" << std::endl;
	std::cin >> to;
	send(_Connection, to.c_str(), sizeof(to), 0);
	std::cout << "Enter message" << std::endl;
	std::cin.ignore();
	getline(std::cin, text);
	send(_Connection, text.c_str(), sizeof(text), 0);
}

void Chat::ShowUsers()
{
	char buf[1024];
	send(_Connection, "23", sizeof("23"), 0);
	recv(_Connection, buf, sizeof(buf), 0);
	std::cout << "Users in chat:" << std::endl << buf << std::endl;
}

bool Chat::checkUser(const std::string& login, const std::string& password) // Проверка авторизации
{
	for (auto& user: _users)
	{
		if (login == user.getLogin() && password == user.getPassword())
		{
			_currentUser = std::make_shared<User>(user);
			return true;
		}
	}
	return false;
}
void Chat::signIn() // Вход пользователя
{
	char buf[1024];
	send(_Connection, "2", sizeof("2"), 0);
	std::string login, password, name;
	std::cout << "Enter your login" << std::endl;
	std::cin >> login;
	send(_Connection, login.c_str(), sizeof(login), 0);
	std::cout << "Enter password" << std::endl;
	std::cin >> password;
	send(_Connection, password.c_str(), sizeof(password), 0);
	recv(_Connection, buf, sizeof(buf), 0);
	int temp = std::atoi(buf);
	if (temp==1) {
		recv(_Connection, buf, sizeof(buf), 0);
		name = buf;
		std::cout<< "Welcome, " << name <<"!"<<std::endl;
		_users.emplace_back(name, login, password);
		checkUser(login, password);
		showUserMenu();
	}
	else {
		std::cout << "Login or password error" << std::endl;
	}
}

void Chat::showStartMenu() //Стартовое меню // Перестало закрываться на 0, если не с первого раза (Разобраться)
{
	char menu = '0';
	do {
		std::cout << "Enter 1 - registration, 2 - sign in, 0 - exit" << std::endl;
		std::cin >> menu;
		switch (menu)
		{
		case '1':
			signUp();
			break;
		case '2':
			signIn();
			break;
		case '0':
			Disconnect();
			_chatWork = false;
			break;
		default:
			std::cout << "Error, enter the correct number of menu" << std::endl;
			break;
		}
	} while (!_currentUser && _chatWork);
}

void Chat::showUserMenu() //Меню залогиненного пользователя // 4 выходит из программы, а 0 - нет (Разобраться)
{
	char menu = '0';
	while (_currentUser) {
		std::cout << "Enter 1 - incoming message, 2 - Send message, 3 - Users, 4 - Log out, 0 - Exit programm" << std::endl;
		std::cin >> menu;
		switch (menu) {
		case '1':
			ShowMessages(_currentUser->getLogin());
			break;
		case '2':
			sendMessage(_currentUser->getLogin());
			break;
		case '3':
			ShowUsers();
			break;
		case '4':
			_currentUser = nullptr;
			break;
		case '0':
			Disconnect();
			_chatWork = false;
			exit(1);
			break;
		default:
			std::cout << "Error, enter the correct number of menu" << std::endl;
			break;
		}
	}
}
