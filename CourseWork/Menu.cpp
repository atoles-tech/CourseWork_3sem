#include "Menu.h"

using namespace std;

void Menu::initMenu() {
	while (true) {
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
}

void Menu::userMenu(string name) {
	system("cls");
	cout << "���� ������������!" << endl;
	system("pause");
}

void Menu::adminMenu(string name) {
	system("cls");
	cout << "���� ������!" << endl;
	system("pause");
}

void Menu::authorize() {
	system("cls");
	vector<User> users = User::readUsers();
	string login = ConsoleHelper::readString("������� ���: ");
	
	User user = User::getUser(users,login);
	
	if (user.getLogin() == "-") {
		cout << "������������ � ������ ������ �� ����������!" << endl;
		system("pause");
		return;
	}

	string password = ConsoleHelper::readString("������� ������: ");
	long long int hash = Hash::getHash(password, user.getSalt());

	if(hash != user.getHash()){
		cout << "�������� ������!" << endl;
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