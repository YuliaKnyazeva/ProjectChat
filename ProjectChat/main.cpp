#include "User.h"
#include "Chat.h"
#include <iostream>



int main()
{
	setlocale(0, "");
	Chat chat;
	char menu = '0';
	do {
		std::cout << "Введите 1 - для регистрации, 2 - для входа, 0 - для выхода из программы" << std::endl;
		std::cin >> menu;
		switch (menu)
		{
		case '1':
			chat.signUp();
			break;
		case '2':
			chat.showUsers();
			chat.signIn();
			break;
		case '0':
			exit(0);
		default:
			std::cout << "Ошибка, введите корректный символ из меню" << std::endl;
			break;
		}
	} while (menu != 0);
	return 0;
}