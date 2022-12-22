#include "Chat.h"
#include "LoginError.h"
#include <iostream>

void Chat::newUser() // Регистрация пользователя
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
		User user(name, login, password);
		users.push_back(user);
	}
	catch (LoginError& e)
	{
		std:: cout << e.what() << std::endl;
	}

}

void Chat::checkLogin(const std::string& login) // Проверка при регистрации
{
	for (auto i = 0; i < users.size(); i++)
	{
		if (login == users[i].getLogin())
		{
			throw LoginError();
		}
	}
}

void Chat::addMessage(const std::string& login) // Отправка сообщения
{
	std::string from, to, text;
	from = login;
	std::cout << "Отправить сообщение? Введите логин пльзователя или all для отправки всем участникам" << std::endl;
	std::cin >> to;
	std::cout << "Введите текст сообщения" << std::endl;
	std::cin.ignore();
	getline(std::cin,text);
	Message message(from, to, text);
	messages.push_back(message);
}

void Chat::showMessage(const std::string login) // Показать входящие сообщения
{
	for (auto& message : messages)
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
	for (auto i = 0; i < users.size(); i++)
	{
		std::cout << users[i].getName() << '\n';
	}
}

bool Chat::checkUser(const std::string& login, const std::string& password) // Проверка авторизации
{
	for (auto i = 0; i < users.size(); i++)
	{
		if (login == users[i].getLogin() && password == users[i].getPassword())
		{
			std::cout <<"Вы вошли под именем: " << users[i].getName() << std::endl;
			return true;
		}
	}
	return false;
}
void Chat::login() // Вход пользователя
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
		showMessage(login);
		addMessage(login);
	}
}

