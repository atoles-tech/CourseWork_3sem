#include "Menu.h"

using namespace std;

void Menu::initMenu() {
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

void Menu::userMenu() {

}

void Menu::adminMenu() {
	
}

void Menu::authorize() {
	system("cls");
	string login = ConsoleHelper::readString("Введите имя: ");
}