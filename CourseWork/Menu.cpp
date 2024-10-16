#include "Menu.h"

using namespace std;

//---------------------------------------------------------------------------//

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
		cout << "Введите свои данные чтобы продолжить!" << endl;
		ServiceStation::getInstance().addMechanic(inputMechanic(name));
	}
	system("cls");
	cout << "Меню механика!" << endl;
	system("pause");
}

//---------------------------------------------------------------------------//

void Menu::userMenu(string name) {
	if (!ServiceStation::getInstance().hasClient(name)) {
		cout << "Введите свои данные чтобы продолжить!" << endl;
		ServiceStation::getInstance().addClient(inputClient(name));
	}
	system("cls");
	cout << "Меню пользователя!" << endl;
	system("pause");
}

//---------------------------------------------------------------------------//

void Menu::adminMenu(string name) {
	while (true) {
		system("cls");
		cout << "Меню админа!" << endl;
		cout << "1.Управление учетными записями" << endl;
		cout << "2.Управление данными СТО" << endl;
		cout << "0.Выйти из аккаунта" << endl;
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
		cout << "1.Добавить аккаунт" << endl;
		cout << "2.Изменить аккаунт" << endl;
		cout << "3.Удалить аккаунт" << endl;
		cout << "4.Просмотр аккаунт" << endl;
		cout << "5.Изменить доступ" << endl;
		cout << "0.Обратно в меню" << endl;
		int input = ConsoleHelper::getOneInt("012345");
		switch (input) {
		case 1:
			cout << "Введите роль для аккаунта(0 - клиент, 1 - механик, 2 - администратор): ";
			registr(ConsoleHelper::getOneInt("012"));
			cout << "Аккаунт зарегистрирован" << endl;
			User::writeAllUsers(users);
			break;
		case 2:
			users = User::showUsers();
			cout << "Введите номер аккаунта: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			users[index] = changeUser(users, users[index]);
			cout << "Изменения приняты" << endl;
			User::writeAllUsers(users);
			break;
		case 3:
			users = User::showUsers();
			cout << "Введите номер аккаунта: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (users[index].getLogin() == name) {
				cout << "Вы не можете удалить себя" << endl;
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
			cout << "Введите номер аккаунта: ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (users[index].getLogin() == name) {
				cout << "Вы не можете изменять свой доступ" << endl;
				break;
			}
			if (!users[index].getAccess()) {
				users[index].setAccess(true);
			}
			else {
				users[index].setAccess(false);
			}
			cout << "Доступ изменен" << endl;
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
	string login = ConsoleHelper::readString("Введите имя: ");

	User user = User::getUser(users,login);
	
	if (user.getLogin() == "-") {
		cout << "Пользователя с данным именем не существует!" << endl;
		system("pause");
		return;
	}

	string password = ConsoleHelper::getPassword("Введите пароль: ");
	cout << endl;
	long long int hash = Hash::getHash(password, user.getSalt());

	if(hash != user.getHash()){
		cout << "Неверный пароль!" << endl;
		system("pause");
		return;
	}

	if (!user.getAccess()) {
		cout << "В доступе отказано!" << endl;
		cout << "Ожидайте разблокоривки администратором!" << endl;
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

	string login = ConsoleHelper::readString("Введите логин: ");

	if (!ConsoleHelper::checkString(login)) {
		cout << "Неккоректный формат логина!" << endl;
		system("pause");
		return;
	}

	for (User user : users) {
		if (user.getLogin() == login) {
			cout << "Пользователь с данным именем существует!" << endl;
			system("pause");
			return;
		}
	}

	string password = ConsoleHelper::getPassword("Введите пароль: ");
	
	string salt = Hash::generateSalt();

	long long int hash = Hash::getHash(password, salt);

	User user(login, hash, role, salt, false);

	User::writeUser(user);
}

//---------------------------------------------------------------------------//

shared_ptr<Client> Menu::inputClient(string name) {
	string login = name;

	cout << "Введите имя: ";
	string n;
	while (true) {
		getline(cin, n);
		if (ConsoleHelper::checkName(n)) {
			break;
		}
		else {
			cout << "В имени не должно быть символов отличных от букв, повторите ввод!" << endl;
		}
	}

	cout << "Введите фамилию: ";
	string surname;
	while (true) {
		getline(cin, surname);
		if (ConsoleHelper::checkName(surname)) {
			break;
		}
		else {
			cout << "В фамилии не должно быть символов отличных от букв, повторите ввод!" << endl;
		}
	}

	cout << "Введите email: ";
	string email;
	getline(cin, email);

	shared_ptr<Client> c = make_shared<Client>(login, n, surname, email);

	Client::writeOneFile(c);

	return c;
}

shared_ptr<Mechanic> Menu::inputMechanic(string name) {
	string login = name;

	cout << "Введите имя: ";
	string n;
	while (true) {
		getline(cin, n);
		if (ConsoleHelper::checkName(n)) {
			break;
		}
		else {
			cout << "В имени не должно быть символов отличных от букв, повторите ввод!" << endl;
		}
	}

	cout << "Введите фамилию: ";
	string surname;
	while (true) {
		getline(cin, surname);
		if (ConsoleHelper::checkName(surname)) {
			break;
		}
		else {
			cout << "В фамилии не должно быть символов отличных от букв, повторите ввод!" << endl;
		}
	}

	cout << "Введите email: ";
	string email;
	getline(cin, email);

	shared_ptr<Mechanic> m = make_shared<Mechanic>(login, n, surname, email);
	
	Mechanic::writeOneFile(m);

	return m;
}

User Menu::changeUser(vector<User> users, User user) {
	while (true) {
		system("cls");
		cout << "Меню изменений:" << endl;
		cout << "Логин: " << user.getLogin() << endl;
		cout << "Роль: " << (user.getRole() == 0 ? "Клиент" : (user.getRole() == 1 ? "Механик" : "Админ")) << endl;
		cout << "Доступ: " << (user.getAccess() == true ? "Доступ разрешен" : "Доступ запрещен") << endl;

		cout << "1.Изменить логин" << endl;
		cout << "2.Изменить пароль" << endl;
		cout << "0.Выйти и сохранить изменения" << endl;

		int input = ConsoleHelper::getOneInt("012");

		if (input == 0) {
			break;
		}
		else if (input == 1) {
			string login = ConsoleHelper::readString("Введите логин: ");
			if (User::getUser(users, login).getLogin() != "-") {
				cout << "Пользователь с таким логином существует!" << endl;
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
			string password = ConsoleHelper::getPassword("Введите пароль: ");
			string salt = Hash::generateSalt();

			user.setSalt(salt);
			user.setHash(Hash::getHash(password, salt));
		}
	}

	return user;
}