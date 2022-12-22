#include "User.h"
#include "main.cpp"
#include <iostream>
#include <vector>

void newUser()
{
	std::string name, login, password;
	std::cout << "¬ведите ¬аше им€" << std::endl;
	std::cin >> name;
	std::cout << "¬ведите логин" << std::endl;
	std::cin >> login;
	std::cout << "¬ведите пароль" << std::endl;
	std::cin >> password;
	User user(name, login, password);
	users.push_back(user);
}