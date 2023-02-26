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
		std::cout << "������� 1 - ��������, 2 - ��������� ���������, 3 - ������ �������������, 4 - ����� �� ��������, 0 - ����� �� ���������" 
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
			std::cout << "������, ������� ���������� ������ �� ����" << std::endl;
			break;
		}
	}
}

void Chat::saveUsers() // ���������� ������������� � ����
{
	std::ofstream outfile("savedUsers.txt");
	if (outfile) {
		for (User user:_users) {
			outfile << user;
		}
	}
	else {
		std::cout << "���������� ������� ����!" << '\n';
	}
	outfile.close();
}

void Chat::saveMessages() // ���������� ��������� � ����
{
	std::ofstream outfile("savedMessages.txt");
	if (outfile) {
		for (Message message:_messages) {
			outfile << message;
		}
	}
	else {
		std::cout << "���������� ������� ����!" << '\n';
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
		std::cout << "���������� ������� ����!" << '\n';
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
		std::cout << "���������� ������� ����!" << '\n';
	}
	inputfile.close();
}
