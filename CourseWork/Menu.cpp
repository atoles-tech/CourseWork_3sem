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
		cout << "3.Управление своими данными, как механика" << endl;
		cout << "0.Выйти из аккаунта" << endl;
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
		cout << "1.Добавить запись" << endl;
		cout << "2.Изменить запись" << endl;
		cout << "3.Удалить запись" << endl;
		cout << "4.Просмотр записей" << endl;
		cout << "5.Изменить доступ" << endl;
		cout << "0.Обратно в меню" << endl;
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

void Menu::registr() {
	system("cls");

	vector<User> users = User::readUsers();

	string login = ConsoleHelper::readString("Введите имя: ");

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

	User user(login, hash, false, salt, false);

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