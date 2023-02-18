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

void Chat::signUp() // ����������� ������������
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
		_users.emplace_back(name, login, password);
	}
	catch (LoginError& e)
	{
		std:: cout << e.what() << std::endl;
	}
}

void Chat::checkLogin(const std::string& login) // �������� ��� �����������
{
	for (size_t i = 0; i < _users.size(); i++)
	{
		if (login == _users[i].getLogin())
		{
			throw LoginError();
		}
	}
}

void Chat::addMessage(const std::string& login) // �������� ���������
{
	std::string from, to, text;
	from = login;
	std::cout << "������� ����� ����������� ��� all ��� �������� ���� ����������" << std::endl;
	std::cin >> to;
	std::cout << "������� ����� ���������" << std::endl;
	std::cin.ignore();
	getline(std::cin, text);
	_messages.emplace_back(from, to, text);
}

void Chat::showMessage(const std::string& login) // �������� �������� ���������
{
	for (auto& message : _messages)
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
	for (size_t i = 0; i < _users.size(); i++)
	{
		std::cout << _users[i].getName() << '\n';
	}
}

bool Chat::checkUser(const std::string& login, const std::string& password) // �������� �����������
{
	for (auto& user: _users)
	{
		if (login == user.getLogin() && password == user.getPassword())
		{
			std::cout <<"�� ����� ��� ������: " << user.getName() << std::endl;
			_currentUser = std::make_shared<User>(user);
			return true;
		}
	}
	return false;
}
void Chat::signIn() // ���� ������������
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
		showUserMenu();
	}
}

void Chat::showStartMenu() //��������� ����
{
	char menu = '0';
	do {
		std::cout << "������� 1 - ��� �����������, 2 - ��� �����, 0 - ��� ������ �� ���������" << std::endl;
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
			std::cout << "������, ������� ���������� ������ �� ����" << std::endl;
			break;
		}
	} while (!_currentUser && _chatWork);
}

void Chat::showUserMenu() //���� ������������� ������������
{
	char menu = '0';
	while (_currentUser) {
		showUsers();
		showMessage(_currentUser->getLogin());
		std::cout << "������� 1 - ��� �������� ���������, 2 - ��� ������ �� ��������, 0 - ��� ������ �� ���������" << std::endl;
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
			std::cout << "������, ������� ���������� ������ �� ����" << std::endl;
			break;
		}
	}
}
