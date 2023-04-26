#include "User.h"
#include "Chat.h"
#include "Database.h"
#include <iostream>
#include <mysql.h>



int main()
{
	setlocale(0, "");
	Chat chat;
	chat.startWork();
	while (chat.getChatWork()) {
		chat.showStartMenu();
		while (chat.getCurrentUser()!=nullptr) {
			chat.showUserMenu();
		}
	}
	return 0;
}