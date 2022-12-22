#include "User.h"
#include "Chat.h"
#include <iostream>



int main()
{
	Chat Chat1;
	setlocale(0, "");
	char menu='0';
	std::cout << "Добро пожаловать в чат!" << std::endl;
	do
	{
		std::cout <<"Введите 1 - для регистрации, 2 - для входа, 0 - для выхода из программы" << std::endl;
		std::cin >> menu;
		switch(menu)
		{
			case '1':
				Chat1.newUser();
				break;
			case '2':
				Chat1.showUsers();
				Chat1.login();
				break;
			case '0':
				break;
		}
	} 
	while (menu != '0');
	return 0;
}