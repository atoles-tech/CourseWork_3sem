#include <iostream>
#include <windows.h>
#include "Menu.h"
#include "HashFunc.h"
#include "User.h"
#include "ConsoleHelper.h" //DANGER//

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	srand(time(NULL));
#if 0
	vector<User> users;
	users.push_back(User("user", Hash::getHash("user", "ABCDEFGP"), false, "ABCDEFGP"));
	users.push_back(User("admin", Hash::getHash("admin", "ABCDEFGK"), true, "ABCDEFGK"));
	User::writeAllUsers(users);
	users = User::readUsers();
	cout << users[0].getLogin();
#endif
	Menu::initMenu();

	return 0;
}