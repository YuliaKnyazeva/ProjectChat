#include "User.h"
#include "Chat.h"
#include <iostream>



int main()
{
	Chat Chat1;
	setlocale(0, "");
	char menu='0';
	std::cout << "����� ���������� � ���!" << std::endl;
	do
	{
		std::cout <<"������� 1 - ��� �����������, 2 - ��� �����, 0 - ��� ������ �� ���������" << std::endl;
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