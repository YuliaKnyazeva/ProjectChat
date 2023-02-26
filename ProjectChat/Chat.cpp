#include "Chat.h"
#include "LoginError.h"
#include <iostream>

void Chat:: startWork()
{
	_chatWork=true;
}

const bool Chat::getChatWork()
{
	return _chatWork;
}

const std::shared_ptr<User> Chat::getCurrentUser()
{
	return _currentUser;
}

void Chat::signUp() // Регистрация пользователя
{
	std::string name, login, password;
	std::cout << "Enter your Name" << std::endl;
	std::cin >> name;
	std::cout << "Enter login" << std::endl;
	std::cin >> login;
	try
	{
		checkLogin(login);
		std::cout << "Enter password" << std::endl;
		std::cin >> password;
		_users.emplace_back(name, login, password);
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

void Chat::showUsers() // Показать зарегистрированных пользователей
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
			break;
		default:
			std::cout << "Error, enter the correct number of menu" << std::endl;
			break;
		}
	}
}

void Chat::saveUsers() // Сохранение пользователей в файл
{
	std::ofstream outfile("savedUsers.txt");
	if (outfile) {
		for (User user:_users) {
			outfile << user;
		}
	}
	else {
		std::cout << "Could not open the file!" << '\n';
	}
	outfile.close();
}

void Chat::saveMessages() // Сохранение сообщений в файл
{
	std::ofstream outfile("savedMessages.txt");
	if (outfile) {
		for (Message message:_messages) {
			outfile << message;
		}
	}
	else {
		std::cout << "Could not open the file!" << '\n';
	}
	outfile.close();
}

void Chat::loadUsers()
{
	std::ifstream inputfile("savedUsers.txt");
	if (inputfile) {
		User temp;
		while (!inputfile.eof()) {
			inputfile >> temp;
		_users.push_back(temp);
		}
	}
	else {
		std::cout << "Could not open the file!" << '\n';
	}
	inputfile.close();
}

void Chat::loadMessages()
{
	std::ifstream inputfile("savedMessages.txt");
	if (inputfile) {
		Message temp;
		while (!inputfile.eof()) {
			inputfile >> temp;
			_messages.push_back(temp);
		}
	}
	else {
		std::cout << "Could not open the file!" << '\n';
	}
	inputfile.close();
}
