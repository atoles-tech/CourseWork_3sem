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
			Menu::adminMenuEditData(name);
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
/*
2 Управление данными
		2.1 Добавить запись
			2.1.1 Добавить автомобиль клиенту
			2.1.2 Добавить заказ
			2.1.3 Добавить услугу
			2.1.4 <- Назад
		2.2 Изменение записей
			2.2.1 Изменить автомобиль
			2.2.2 Изменить заказ
			2.2.3 Изменить услугу
			2.2.4 <- Назад
		2.3 Удаление записей
			2.3.1 Удалить автомобиль
			2.3.2 Удалить заказ
			2.3.3 Удалить услугу
			2.3.4 <- Назад
		2.4 Просмотр записей
			2.4.1 Просмотреть автомобиль
			2.4.2 Просмотреть заказ
			2.4.3 Просмотреть услугу
			2.4.4 Просмотреть клиентов
			2.4.5 Просмотреть механиков
			2.4.6 Просмотреть чек определенного заказа
			2.4.7 <- Назад
		2.5 <- Обратно в меню *
*/
void Menu::adminMenuEditData(string name) {
	while (true) {
		system("cls");
		cout << "===Изменение===" << endl;
		cout << "1.Добавление записей" << endl;
		cout << "2.Изменение записей" << endl;
		cout << "3.Удаление записей" << endl;
		cout << "4.Просмотр записей" << endl;
		cout << "0.Обратно в меню" << endl;
		int input = ConsoleHelper::getOneInt("01234");
		switch (input) {
		case 1:
			adminMenuEditDataAdd(name);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			adminMenuEditDataShow(name);
			break;
		case 0:
			return;
		}
	}
}

void Menu::adminMenuEditDataAdd(string name) {
	shared_ptr<Vehicle> v;
	shared_ptr<Request> r;
	shared_ptr<Service> s;
	system("cls");
	cout << "===Добавление===" << endl;
	cout << "1.Добавить новый автомобиль клиенту" << endl;
	cout << "2.Добавить заказ" << endl;
	cout << "3.Добавить услугу" << endl;
	cout << "0.Назад" << endl;
	int input = ConsoleHelper::getOneInt("0123");
	switch (input) {
	case 1:
		if (ServiceStation::getInstance().getClients().size() == 0) {
			cout << "Невозможно добавить автомобиль клиенту по причине: Отсутствие клиентов" << endl;
			break;
		}
		v = inputVehicle();
		if (v->getNumber() != "()") {
			ServiceStation::getInstance().addVehicle(v);
			ServiceStation::getInstance().showClient();
			cout << "Введите номер клиента: ";
			ServiceStation::getInstance().getClients()[ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size()) - 1]->addVehicle(v);
			cout << "Автомобиль успешно добавлен" << endl;
		}
		break;
	case 2:
		if (ServiceStation::getInstance().getClients().size() == 0) {
			cout << "Невозможно добавить заказ по причине: Отсутствие клиентов" << endl;
			break;
		}
		else if (ServiceStation::getInstance().getServices().size() == 0) {
			cout << "Невозможно добавить заказ по причине: Отсутствие услуг" << endl;
			break;
		}
		else if (ServiceStation::getInstance().getVehicles().size() == 0) {
			cout << "Невозможно добавить заказ по причине: Отсутствие автомобилей у клинта" << endl;
			break;
		}
		r = inputRequest();
		if (r->getStatus() != -1) {
			ServiceStation::getInstance().addRequest(r);
		}
		for (shared_ptr<Client> cl : ServiceStation::getInstance().getClients()) {
			for (shared_ptr<Request> rq : cl->getRequests()) {
				if (rq->getId() == r->getId()) {
					cout << cl->getLogin() << " " << cl->getEmail() << endl;
				}
			}
		}
		break;
	case 3:
		s = inputService();
		if (s->getServiceId() != -1) {
			ServiceStation::getInstance().addService(s);
		}
		break;
	case 0:
		return;
	}
	ServiceStation::getInstance().saveAllData();
	system("pause");
}

void Menu::adminMenuEditDataShow(string name) {
	system("cls");
	cout << "===Просмотр===" << endl;
	cout << "1.Показать клиентов" << endl;
	cout << "2.Показать механиков" << endl;
	cout << "3.Показать автомобили" << endl;
	cout << "4.Показать услуги" << endl;
	cout << "5.Показать заказы" << endl;
	cout << "6.Показать подробную информацию о клиенте" << endl;
	cout << "7.Показать подробную информацию о заказе" << endl;
	cout << "8.Показать подробную информацию о механике" << endl;
	cout << "0.Назад" << endl;
	int input = ConsoleHelper::getOneInt("012345678");

	switch (input) {
	case 1:
		ServiceStation::getInstance().showClient();
		system("pause");
		break;
	case 2:
		ServiceStation::getInstance().showMechanic();
		system("pause");
		break;
	case 3:
		ServiceStation::getInstance().showVehicle();
		system("pause");
		break;
	case 4:
		ServiceStation::getInstance().showService();
		system("pause");
		break;
	case 5:
		ServiceStation::getInstance().showRequest();
		system("pause");
		break;
	case 6: {
		ServiceStation::getInstance().showClient();
		cout << "Введите номер клиента: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size());
		shared_ptr<Client> c = ServiceStation::getInstance().getClients()[n - 1];
		cout << "Логин: " << c->getLogin() << endl;
		cout << "Имя: " << c->getName() << endl;
		cout << "Фамилия: " << c->getSurname() << endl;
		cout << "Email: " << c->getEmail() << endl << endl;

		if (c->getVehicles().size() == 0) {
			cout << "Автомобилей нет!" << endl;
		}
		else {
			cout << "Автомобили:" << endl;
			Vehicle::showVehicle(c->getVehicles());
		}
		cout << endl;
		if (c->getRequests().size() == 0) {
			cout << "Заказов нет!" << endl;
		}
		else {
			cout << "Заказы:" << endl;
			Request::showRequest(c->getRequests());
		}
		system("pause");
		break;
	}
	case 7: {
		ServiceStation::getInstance().showRequest();
		cout << "Введите номер заказа: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size());
		shared_ptr<Request> req = ServiceStation::getInstance().getRequests()[n-1];
		cout << "ID: " << req->getId() << endl;
		cout << "Клиент: " << req->getClient() << endl;
		cout << "Механик: " << req->getMechanic() << endl << endl;
		cout << "Автомобиль:" << endl;
		cout << "Номер: " << req->getVehicle()->getNumber() << endl;
		cout << "Марка: " << req->getVehicle()->getBrand() << endl;
		cout << "Модель: " << req->getVehicle()->getModel() << endl;
		cout << "VIN: " << req->getVehicle()->getVIN() << endl;
		system("pause");
		break;
	}
	case 8: {
		ServiceStation::getInstance().showMechanic();
		cout << "Введите номер заказа: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getMechanics().size());
		shared_ptr<Mechanic> m = ServiceStation::getInstance().getMechanics()[n - 1];
		cout << "Логин: " << m->getLogin() << endl;
		cout << "Имя: " << m->getName() << endl;
		cout << "Фамилия: " << m->getSurname() << endl;
		cout << "Email: " << m->getEmail() << endl;
		cout << "Статус: " << (m->getStatus() == true ? "Занят" : "Свободен") << endl << endl;

		cout << "Заказы: " << endl;
		Request::showRequest(m->getRequests());
		system("pause");
	}
		break;
	case 0:
		return;
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

shared_ptr<Vehicle> Menu::inputVehicle() {
	shared_ptr<Vehicle> v = make_shared<Vehicle>();
	string car_number = ConsoleHelper::readString("Введите номер автомобиля: ");
	if (!ConsoleHelper::checkString(car_number)) {
		cout << "Введены недопустимые символы" << endl;
		return v;
	}
	for (shared_ptr<Vehicle> veh : ServiceStation::getInstance().getVehicles()) {
		if (veh->getNumber() == car_number) {
			cout << "Автомобиль с данным номером уже существует" << endl;
			system("pause");
			return v;
		}
	}
	string brand = ConsoleHelper::readString("Введите марку автомобиля: ");
	string model = ConsoleHelper::readString("Введите модель автомобиля: ");
	string vin = ConsoleHelper::readString("Введите VIN автомобиля: ");

	v = make_shared<Vehicle>(car_number,model,brand,vin);

	Vehicle::writeOneFile(v);

	return v;
}

shared_ptr<Request> Menu::inputRequest() {
	shared_ptr<Request> r = make_shared<Request>();
	int id = ConsoleHelper::readInt("Введите id заказа: ");
	for (shared_ptr<Request> req : ServiceStation::getInstance().getRequests()) {
		if (req->getId() == id) {
			cout << "Заказ с данным id уже существует" << endl;
			system("pause");
			return r;
		}
	}

	ServiceStation::getInstance().showClient();
	
	cout << "Введите номер клиента: ";
	int input = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size());

	ServiceStation::getInstance().showVehicle();
	cout << "Введите порядковый номер автомобиля: ";
	int input_v = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getVehicles().size());

	vector<shared_ptr<Service>> ser;

	ServiceStation::getInstance().showService();
	cout << "Вводите номера услуг, когда посчитаете нужным закончить введите 0(нельзя отсавить список услуг пустым)" << endl;

	while (true) {
		int inp = ConsoleHelper::readInt("Введите номер сервиса: ");
		if (inp > ServiceStation::getInstance().getServices().size()) {
			cout << "Такого номера нет! Будьте внимательней" << endl;
		}
		else if (inp == 0) {
			if (ser.size() == 0) {
				cout << "Нельзя выйти, так как услуг нет";
			}
			else {
				break;
			}
		}
		else {
			ser.push_back(ServiceStation::getInstance().getServices()[inp - 1]);
		}
	}

	r = make_shared<Request>(id, ServiceStation::getInstance().getClients()[input - 1]->getLogin(), ServiceStation::getInstance().getVehicles()[input_v - 1], ser, 0);

	ServiceStation::getInstance().getClients()[input - 1]->addRequest(r);
	
	Request::writeOneFile(r);

	return r;
}

shared_ptr<Service> Menu::inputService() {
	shared_ptr<Service> s = make_shared<Service>();

	int id = ConsoleHelper::readInt("Введите id услуги: ");
	for (shared_ptr<Service> ser : ServiceStation::getInstance().getServices()) {
		if (ser->getServiceId() == id) {
			cout << "Услуга с данным id уже существует" << endl;
			return s;
		}
	}

	string name = ConsoleHelper::readString("Введите название услуги: ");

	double price = ConsoleHelper::readDouble("Введите цену: ");

	int time = ConsoleHelper::readInt("Введите время в часах на выполнение данной услуги: ");

	s = make_shared<Service>(id, name, price, time);

	return s;
}

//---------------------------------------------------------------------------//

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