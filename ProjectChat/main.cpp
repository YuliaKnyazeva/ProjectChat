#include "User.h"
#include "Chat.h"
#include <iostream>



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