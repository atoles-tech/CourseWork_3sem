#include "Menu.h"

using namespace std;

void Menu::initMenu() {
	system("cls");
	cout << "===������� ����===" << endl;
	cout << "1.�����������" << endl;
	cout << "2.�����������" << endl;
	cout << "3.�����" << endl;
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
	string login = ConsoleHelper::readString("������� ���: ");
}