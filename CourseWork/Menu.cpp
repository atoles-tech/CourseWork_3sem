#include "Menu.h"

using namespace std;

//---------------------------------------------------------------------------//

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
			Menu::registr();
			break;
		case 3:
			return;
		}
	}
}
//---------------------------------------------------------------------------//

void Menu::mechanicMenu(string name) {
	if (!ServiceStation::getInstance().hasMechanic(name)) {
		cout << "������� ���� ������ ����� ����������!" << endl;
		ServiceStation::getInstance().addMechanic(inputMechanic(name));
	}
	system("cls");
	cout << "���� ��������!" << endl;
	system("pause");
}

//---------------------------------------------------------------------------//

void Menu::userMenu(string name) {
	if (!ServiceStation::getInstance().hasClient(name)) {
		cout << "������� ���� ������ ����� ����������!" << endl;
		ServiceStation::getInstance().addClient(inputClient(name));
	}
	system("cls");
	cout << "���� ������������!" << endl;
	system("pause");
}

//---------------------------------------------------------------------------//

void Menu::adminMenu(string name) {
	while (true) {
		system("cls");
		cout << "���� ������!" << endl;
		cout << "1.���������� �������� ��������" << endl;
		cout << "2.���������� ������� ���" << endl;
		cout << "3.���������� ������ �������, ��� ��������" << endl;
		cout << "0.����� �� ��������" << endl;
		int input = ConsoleHelper::getOneInt("0123");
		switch (input) {
		case 1:
			Menu::adminMenuEditAccount(name);
			break;
		case 2:
			//Menu::adminMenuEditData(name);
			break;
		case 3:
			//Menu::adminMenuEditSelf(name);
			break;
		case 0:
			return;
			break;
		}
		system("pause");
	}
}

void Menu::adminMenuEditAccount(string name) {
	while (true) {
		cout << "1.�������� ������" << endl;
		cout << "2.�������� ������" << endl;
		cout << "3.������� ������" << endl;
		cout << "4.�������� �������" << endl;
		cout << "5.�������� ������" << endl;
		cout << "0.������� � ����" << endl;
		int input = ConsoleHelper::getOneInt("012345");
		switch (input) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 0:
			break;
		}
	}
}

//----------------------------------------------------------------------------------------//

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

	if (!user.getAccess()) {
		cout << "� ������� ��������!" << endl;
		cout << "�������� ������������� ���������������!" << endl;
		system("pause");
		return;
	}

	switch (user.getRole()) {
	case 0:
		userMenu(login);
		break;
	case 1:
		mechanicMenu(login);
		break;
	case 2:
		adminMenu(login);
		break;
	}
}

void Menu::registr() {
	system("cls");

	vector<User> users = User::readUsers();

	string login = ConsoleHelper::readString("������� ���: ");

	if (!ConsoleHelper::checkString(login)) {
		cout << "������������ ������ ������!" << endl;
		system("pause");
		return;
	}

	for (User user : users) {
		if (user.getLogin() == login) {
			cout << "������������ � ������ ������ ����������!" << endl;
			system("pause");
			return;
		}
	}

	string password = ConsoleHelper::getPassword("������� ������: ");
	
	string salt = Hash::generateSalt();

	long long int hash = Hash::getHash(password, salt);

	User user(login, hash, false, salt, false);

	User::writeUser(user);
}

//---------------------------------------------------------------------------//

shared_ptr<Client> Menu::inputClient(string name) {
	string login = name;

	cout << "������� ���: ";
	string n;
	while (true) {
		getline(cin, n);
		if (ConsoleHelper::checkName(n)) {
			break;
		}
		else {
			cout << "� ����� �� ������ ���� �������� �������� �� ����, ��������� ����!" << endl;
		}
	}

	cout << "������� �������: ";
	string surname;
	while (true) {
		getline(cin, surname);
		if (ConsoleHelper::checkName(surname)) {
			break;
		}
		else {
			cout << "� ������� �� ������ ���� �������� �������� �� ����, ��������� ����!" << endl;
		}
	}

	cout << "������� email: ";
	string email;
	getline(cin, email);

	shared_ptr<Client> c = make_shared<Client>(login, n, surname, email);

	Client::writeOneFile(c);

	return c;
}

shared_ptr<Mechanic> Menu::inputMechanic(string name) {
	string login = name;

	cout << "������� ���: ";
	string n;
	while (true) {
		getline(cin, n);
		if (ConsoleHelper::checkName(n)) {
			break;
		}
		else {
			cout << "� ����� �� ������ ���� �������� �������� �� ����, ��������� ����!" << endl;
		}
	}

	cout << "������� �������: ";
	string surname;
	while (true) {
		getline(cin, surname);
		if (ConsoleHelper::checkName(surname)) {
			break;
		}
		else {
			cout << "� ������� �� ������ ���� �������� �������� �� ����, ��������� ����!" << endl;
		}
	}

	cout << "������� email: ";
	string email;
	getline(cin, email);

	shared_ptr<Mechanic> m = make_shared<Mechanic>(login, n, surname, email);
	
	Mechanic::writeOneFile(m);

	return m;
}