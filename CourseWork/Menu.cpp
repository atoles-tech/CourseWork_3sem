#include "Menu.h"

using namespace std;

void Menu::initMenu() {
	while (true) {
		system("cls");
		cout << "===Главное меню===" << endl;
		cout << "1.Авторизация" << endl;
		cout << "2.Регистрация" << endl;
		cout << "3.Выход" << endl;
		cout << "------------------" << endl;
		int input = ConsoleHelper::getOneInt("123");
		switch (input) {
		case 1:
			Menu::authorize();
			break;
		case 2:
			//Menu::registr();
			break;
		case 3:
			return;
		}
	}
}

void Menu::userMenu(string name) {
	system("cls");
	cout << "Меню пользователя!" << endl;
	system("pause");
}

void Menu::adminMenu(string name) {
	system("cls");
	cout << "Меню админа!" << endl;
	system("pause");
}

void Menu::authorize() {
	system("cls");
	vector<User> users = User::readUsers();
	string login = ConsoleHelper::readString("Введите имя: ");
	
	User user = User::getUser(users,login);
	
	if (user.getLogin() == "-") {
		cout << "Пользователя с данным именем не существует!" << endl;
		system("pause");
		return;
	}

	string password = ConsoleHelper::readString("Введите пароль: ");
	long long int hash = Hash::getHash(password, user.getSalt());

	if(hash != user.getHash()){
		cout << "Неверный пароль!" << endl;
		system("pause");
		return;
	}

	if (user.getRole()) {
		Menu::adminMenu(user.getLogin());
	}
	else {
		Menu::userMenu(user.getLogin());
	}
}