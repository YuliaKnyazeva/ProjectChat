#include "Chat.h"
#include "LoginError.h"
#include <iostream>

void Chat:: startWork()
{
	_chatWork=true;
	db.Connect();
	//db.CreateTables();
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
	std::string name, login, password;
	std::cout << "Enter login" << std::endl;
	std::cin >> login;
	try
	{
		checkLogin(login);
		std::cout << "Enter password" << std::endl;
		std::cin >> password;
		std::cout << "Enter your Name" << std::endl;
		std::cin >> name;
		db.addUser(login, password, name);
	}
	catch (LoginError& e)
	{
		std:: cout << e.what() << std::endl;
	}
}

void Chat::checkLogin(const std::string& login) // Проверка при регистрации
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (login == _users[i].getLogin())
		{
			throw LoginError();
		}
	}
}

void Chat::addMessage(const std::string& login) // Отправка сообщения
{
	std::string from, to, text;
	from = login;
	std::cout << "Enter user name or 'all' for send all users" << std::endl;
	std::cin >> to;
	std::cout << "Enter message" << std::endl;
	std::cin.ignore();
	getline(std::cin, text);
	_messages.emplace_back(from, to, text);
}

void Chat::showMessage(const std::string& login) // Показать входящие сообщения
{
	for (auto& message : _messages)
	{
		if (login == message.getTo() || message.getTo() == "all")
		{
			std::cout << "User " << message.getFrom() << " written:" << std::endl
				<< message.getText() << std::endl;
		} 
	}
}

void Chat::showUsers() const // Показать зарегистрированных пользователей
{
	std::cout << "Users in system:" << std::endl;
	for (size_t i = 0; i < _users.size(); i++)
	{
		std::cout << _users[i].getName() << '\n';
	}
}

bool Chat::checkUser(const std::string& login, const std::string& password) // Проверка авторизации
{
	for (auto& user: _users)
	{
		if (login == user.getLogin() && password == user.getPassword())
		{
			std::cout <<"Welcome: " << user.getName() << std::endl;
			_currentUser = std::make_shared<User>(user);
			return true;
		}
	}
	return false;
}
void Chat::signIn() // Вход пользователя
{
	bool check = false;
	std::string login, password;
	std::cout << "Enter your login" << std::endl;
	std::cin >> login;
	std::cout << "Enter password" << std::endl;
	std::cin >> password;
	if (!checkUser(login, password))
	{
		std::cout << "Login or passwor error" << std::endl;
	}
	else
	{
		showUserMenu();
	}
}

void Chat::showStartMenu() //Стартовое меню
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
			_chatWork = false;
			db.Disconnect();
			break;
		default:
			std::cout << "Error, enter the correct number of menu" << std::endl;
			break;
		}
	} while (!_currentUser && _chatWork);
}

void Chat::showUserMenu() //Меню залогиненного пользователя
{
	char menu = '0';
	while (_currentUser) {
		std::cout << "Enter 1 - incoming message, 2 - Send message, 3 - Users, 4 - Log out, 0 - Exit programm" 
			<< std::endl;
		std::cin >> menu;
		switch (menu) {
		case '1':
			showMessage(_currentUser->getLogin());
			break;
		case '2':
			addMessage(_currentUser->getLogin());
			break;
		case '3':
			showUsers();
			break;
		case '4':
			_currentUser = nullptr;
			break;
		case '0':
			_currentUser = nullptr;
			_chatWork = false;
			db.Disconnect();
			break;
		default:
			std::cout << "Error, enter the correct number of menu" << std::endl;
			break;
		}
	}
}
