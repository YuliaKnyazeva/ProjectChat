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
	std::cout << "Введите Ваше имя" << std::endl;
	std::cin >> name;
	std::cout << "Введите логин" << std::endl;
	std::cin >> login;
	try
	{
		checkLogin(login);
		std::cout << "Введите пароль" << std::endl;
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
	std::cout << "Введите логин пльзователя или all для отправки всем участникам" << std::endl;
	std::cin >> to;
	std::cout << "Введите текст сообщения" << std::endl;
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
			std::cout << "Пользователь " << message.getFrom() << " написал:" << std::endl
				<< message.getText() << std::endl;
		}
		else 
		{
			std::cout << "Для вас нет личных сообщений" << std::endl;
		}
	}
}

void Chat::showUsers() // Показать зарегистрированных пользователей
{
	std::cout << "Пользователи в системе:" << std::endl;
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
			std::cout <<"Вы вошли под именем: " << user.getName() << std::endl;
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
	std::cout << "Введите логин" << std::endl;
	std::cin >> login;
	std::cout << "Введите пароль" << std::endl;
	std::cin >> password;
	if (!checkUser(login, password))
	{
		std::cout << "Пароль или логин неверный" << std::endl;
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
		std::cout << "Введите 1 - для регистрации, 2 - для входа, 0 - для выхода из программы" << std::endl;
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
			//exit(0);
		default:
			std::cout << "Ошибка, введите корректный символ из меню" << std::endl;
			break;
		}
	} while (!_currentUser && _chatWork);
}

void Chat::showUserMenu() //Меню залогиненного пользователя
{
	char menu = '0';
	while (_currentUser) {
		showUsers();
		showMessage(_currentUser->getLogin());
		std::cout << "Введите 1 - для отправки сообщение, 2 - для выхода из аккаунта, 0 - для выхода из программы" << std::endl;
		std::cin >> menu;
		switch (menu) {
		case '1':
			addMessage(_currentUser->getLogin());
			break;
		case '2':
			_currentUser = nullptr;
			break;
		case '0':
			_chatWork = false;
			break;
			//exit(0);
		default:
			std::cout << "Ошибка, введите корректный символ из меню" << std::endl;
			break;
		}
	}
}
