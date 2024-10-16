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
			Menu::registr(0);
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
		cout << "0.����� �� ��������" << endl;
		int input = ConsoleHelper::getOneInt("012");
		switch (input) {
		case 1:
			Menu::adminMenuEditAccount(name);
			break;
		case 2:
			//Menu::adminMenuEditData(name);
			break;
		case 0:
			return;
			break;
		}
		system("pause");
	}
}

void Menu::adminMenuEditAccount(string name) {
	vector<User> users;
	int index;

	while (true) {
		system("cls");
		cout << "1.�������� �������" << endl;
		cout << "2.�������� �������" << endl;
		cout << "3.������� �������" << endl;
		cout << "4.�������� �������" << endl;
		cout << "5.�������� ������" << endl;
		cout << "0.������� � ����" << endl;
		int input = ConsoleHelper::getOneInt("012345");
		switch (input) {
		case 1:
			cout << "������� ���� ��� ��������(0 - ������, 1 - �������, 2 - �������������): ";
			registr(ConsoleHelper::getOneInt("012"));
			cout << "������� ���������������" << endl;
			User::writeAllUsers(users);
			break;
		case 2:
			users = User::showUsers();
			cout << "������� ����� ��������: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			users[index] = changeUser(users, users[index]);
			cout << "��������� �������" << endl;
			User::writeAllUsers(users);
			break;
		case 3:
			users = User::showUsers();
			cout << "������� ����� ��������: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (users[index].getLogin() == name) {
				cout << "�� �� ������ ������� ����" << endl;
				break;
			}
			for (shared_ptr<Client> c :ServiceStation::getInstance().getClients()) {
				if (c->getLogin() == users[index].getLogin()) {
					c->setLogin(c->getLogin() + "(del)");
					break;
				}
			}
			for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
				if (r->getClient() == users[index].getLogin()) {
					r->setClient(r->getClient() + "(del)");
				}
			}
			users.erase(users.begin() + index);
			User::writeAllUsers(users);
			break;
		case 4:
			User::showUsers();
			break;
		case 5:
			users = User::showUsers();
			cout << "������� ����� ��������: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (users[index].getLogin() == name) {
				cout << "�� �� ������ �������� ���� ������" << endl;
				break;
			}
			if (!users[index].getAccess()) {
				users[index].setAccess(true);
			}
			else {
				users[index].setAccess(false);
			}
			cout << "������ �������" << endl;
			User::writeAllUsers(users);
			break;
		case 0:
			return;
		}
		system("pause");
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

	string password = ConsoleHelper::getPassword("������� ������: ");
	cout << endl;
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

void Menu::registr(int role) {
	system("cls");

	vector<User> users = User::readUsers();

	string login = ConsoleHelper::readString("������� �����: ");

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

	User user(login, hash, role, salt, false);

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

User Menu::changeUser(vector<User> users, User user) {
	while (true) {
		system("cls");
		cout << "���� ���������:" << endl;
		cout << "�����: " << user.getLogin() << endl;
		cout << "����: " << (user.getRole() == 0 ? "������" : (user.getRole() == 1 ? "�������" : "�����")) << endl;
		cout << "������: " << (user.getAccess() == true ? "������ ��������" : "������ ��������") << endl;

		cout << "1.�������� �����" << endl;
		cout << "2.�������� ������" << endl;
		cout << "0.����� � ��������� ���������" << endl;

		int input = ConsoleHelper::getOneInt("012");

		if (input == 0) {
			break;
		}
		else if (input == 1) {
			string login = ConsoleHelper::readString("������� �����: ");
			if (User::getUser(users, login).getLogin() != "-") {
				cout << "������������ � ����� ������� ����������!" << endl;
			}
			else {
				for (shared_ptr<Mechanic> m : ServiceStation::getInstance().getMechanics()) {
					if (m->getLogin() == user.getLogin()) {
						m->setLogin(login);
						break;
					}
				}
				user.setLogin(login);
			}
		}
		else {
			string password = ConsoleHelper::getPassword("������� ������: ");
			string salt = Hash::generateSalt();

			user.setSalt(salt);
			user.setHash(Hash::getHash(password, salt));
		}
	}

	return user;
}