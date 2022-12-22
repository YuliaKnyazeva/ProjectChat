#include "Chat.h"
#include "LoginError.h"
#include <iostream>

void Chat::newUser() // ����������� ������������
{
	std::string name, login, password;
	std::cout << "������� ���� ���" << std::endl;
	std::cin >> name;
	std::cout << "������� �����" << std::endl;
	std::cin >> login;
	try
	{
		checkLogin(login);
		std::cout << "������� ������" << std::endl;
		std::cin >> password;
		User user(name, login, password);
		users.push_back(user);
	}
	catch (LoginError& e)
	{
		std:: cout << e.what() << std::endl;
	}

}

void Chat::checkLogin(const std::string& login) // �������� ��� �����������
{
	for (auto i = 0; i < users.size(); i++)
	{
		if (login == users[i].getLogin())
		{
			throw LoginError();
		}
	}
}

void Chat::addMessage(const std::string& login) // �������� ���������
{
	std::string from, to, text;
	from = login;
	std::cout << "��������� ���������? ������� ����� ����������� ��� all ��� �������� ���� ����������" << std::endl;
	std::cin >> to;
	std::cout << "������� ����� ���������" << std::endl;
	std::cin.ignore();
	getline(std::cin,text);
	Message message(from, to, text);
	messages.push_back(message);
}

void Chat::showMessage(const std::string login) // �������� �������� ���������
{
	for (auto& message : messages)
	{
		if (login == message.getTo() || message.getTo() == "all")
		{
			std::cout << "������������ " << message.getFrom() << " �������:" << std::endl
				<< message.getText() << std::endl;
		}
		else 
		{
			std::cout << "��� ��� ��� ������ ���������" << std::endl;
		}
	}
}

void Chat::showUsers() // �������� ������������������ �������������
{
	std::cout << "������������ � �������:" << std::endl;
	for (auto i = 0; i < users.size(); i++)
	{
		std::cout << users[i].getName() << '\n';
	}
}

bool Chat::checkUser(const std::string& login, const std::string& password) // �������� �����������
{
	for (auto i = 0; i < users.size(); i++)
	{
		if (login == users[i].getLogin() && password == users[i].getPassword())
		{
			std::cout <<"�� ����� ��� ������: " << users[i].getName() << std::endl;
			return true;
		}
	}
	return false;
}
void Chat::login() // ���� ������������
{
	bool check = false;
	std::string login, password;
	std::cout << "������� �����" << std::endl;
	std::cin >> login;
	std::cout << "������� ������" << std::endl;
	std::cin >> password;
	if (!checkUser(login, password))
	{
		std::cout << "������ ��� ����� ��������" << std::endl;
	}
	else
	{
		showMessage(login);
		addMessage(login);
	}
}

