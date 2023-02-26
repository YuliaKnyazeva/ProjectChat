#include "User.h"
#include "Chat.h"
#include <iostream>



int main()
{
	setlocale(0, "");
	Chat chat;
	chat.startWork();
	chat.loadUsers();
	chat.loadMessages();
	while (chat.getChatWork()) {
		chat.showStartMenu();
		while (chat.getCurrentUser()!=nullptr) {
			chat.showUserMenu();
		}
	}
	chat.saveUsers();
	chat.saveMessages();
	return 0;
}