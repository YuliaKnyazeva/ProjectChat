#include "User.h"
#include "main.cpp"
#include <iostream>
#include <vector>

void newUser()
{
	std::string name, login, password;
	std::cout << "������� ���� ���" << std::endl;
	std::cin >> name;
	std::cout << "������� �����" << std::endl;
	std::cin >> login;
	std::cout << "������� ������" << std::endl;
	std::cin >> password;
	User user(name, login, password);
	users.push_back(user);
}