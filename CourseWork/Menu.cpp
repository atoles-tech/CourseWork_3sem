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
/*
2 ���������� �������
		2.1 �������� ������
			2.1.1 �������� ���������� �������
			2.1.2 �������� �����
			2.1.3 �������� ������
			2.1.4 <- �����
		2.2 ��������� �������
			2.2.1 �������� ����������
			2.2.2 �������� �����
			2.2.3 �������� ������
			2.2.4 <- �����
		2.3 �������� �������
			2.3.1 ������� ����������
			2.3.2 ������� �����
			2.3.3 ������� ������
			2.3.4 <- �����
		2.4 �������� �������
			2.4.1 ����������� ����������
			2.4.2 ����������� �����
			2.4.3 ����������� ������
			2.4.4 ����������� ��������
			2.4.5 ����������� ���������
			2.4.6 ����������� ��� ������������� ������
			2.4.7 <- �����
		2.5 <- ������� � ���� *
*/
void Menu::adminMenuEditData(string name) {
	while (true) {
		system("cls");
		cout << "===���������===" << endl;
		cout << "1.���������� �������" << endl;
		cout << "2.��������� �������" << endl;
		cout << "3.�������� �������" << endl;
		cout << "4.�������� �������" << endl;
		cout << "0.������� � ����" << endl;
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
	cout << "===����������===" << endl;
	cout << "1.�������� ����� ���������� �������" << endl;
	cout << "2.�������� �����" << endl;
	cout << "3.�������� ������" << endl;
	cout << "0.�����" << endl;
	int input = ConsoleHelper::getOneInt("0123");
	switch (input) {
	case 1:
		if (ServiceStation::getInstance().getClients().size() == 0) {
			cout << "���������� �������� ���������� ������� �� �������: ���������� ��������" << endl;
			break;
		}
		v = inputVehicle();
		if (v->getNumber() != "()") {
			ServiceStation::getInstance().addVehicle(v);
			ServiceStation::getInstance().showClient();
			cout << "������� ����� �������: ";
			ServiceStation::getInstance().getClients()[ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size()) - 1]->addVehicle(v);
			cout << "���������� ������� ��������" << endl;
		}
		break;
	case 2:
		if (ServiceStation::getInstance().getClients().size() == 0) {
			cout << "���������� �������� ����� �� �������: ���������� ��������" << endl;
			break;
		}
		else if (ServiceStation::getInstance().getServices().size() == 0) {
			cout << "���������� �������� ����� �� �������: ���������� �����" << endl;
			break;
		}
		else if (ServiceStation::getInstance().getVehicles().size() == 0) {
			cout << "���������� �������� ����� �� �������: ���������� ����������� � ������" << endl;
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
	cout << "===��������===" << endl;
	cout << "1.�������� ��������" << endl;
	cout << "2.�������� ���������" << endl;
	cout << "3.�������� ����������" << endl;
	cout << "4.�������� ������" << endl;
	cout << "5.�������� ������" << endl;
	cout << "6.�������� ��������� ���������� � �������" << endl;
	cout << "7.�������� ��������� ���������� � ������" << endl;
	cout << "8.�������� ��������� ���������� � ��������" << endl;
	cout << "0.�����" << endl;
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
		cout << "������� ����� �������: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size());
		shared_ptr<Client> c = ServiceStation::getInstance().getClients()[n - 1];
		cout << "�����: " << c->getLogin() << endl;
		cout << "���: " << c->getName() << endl;
		cout << "�������: " << c->getSurname() << endl;
		cout << "Email: " << c->getEmail() << endl << endl;

		if (c->getVehicles().size() == 0) {
			cout << "����������� ���!" << endl;
		}
		else {
			cout << "����������:" << endl;
			Vehicle::showVehicle(c->getVehicles());
		}
		cout << endl;
		if (c->getRequests().size() == 0) {
			cout << "������� ���!" << endl;
		}
		else {
			cout << "������:" << endl;
			Request::showRequest(c->getRequests());
		}
		system("pause");
		break;
	}
	case 7: {
		ServiceStation::getInstance().showRequest();
		cout << "������� ����� ������: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size());
		shared_ptr<Request> req = ServiceStation::getInstance().getRequests()[n-1];
		cout << "ID: " << req->getId() << endl;
		cout << "������: " << req->getClient() << endl;
		cout << "�������: " << req->getMechanic() << endl << endl;
		cout << "����������:" << endl;
		cout << "�����: " << req->getVehicle()->getNumber() << endl;
		cout << "�����: " << req->getVehicle()->getBrand() << endl;
		cout << "������: " << req->getVehicle()->getModel() << endl;
		cout << "VIN: " << req->getVehicle()->getVIN() << endl;
		system("pause");
		break;
	}
	case 8: {
		ServiceStation::getInstance().showMechanic();
		cout << "������� ����� ������: ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getMechanics().size());
		shared_ptr<Mechanic> m = ServiceStation::getInstance().getMechanics()[n - 1];
		cout << "�����: " << m->getLogin() << endl;
		cout << "���: " << m->getName() << endl;
		cout << "�������: " << m->getSurname() << endl;
		cout << "Email: " << m->getEmail() << endl;
		cout << "������: " << (m->getStatus() == true ? "�����" : "��������") << endl << endl;

		cout << "������: " << endl;
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

shared_ptr<Vehicle> Menu::inputVehicle() {
	shared_ptr<Vehicle> v = make_shared<Vehicle>();
	string car_number = ConsoleHelper::readString("������� ����� ����������: ");
	if (!ConsoleHelper::checkString(car_number)) {
		cout << "������� ������������ �������" << endl;
		return v;
	}
	for (shared_ptr<Vehicle> veh : ServiceStation::getInstance().getVehicles()) {
		if (veh->getNumber() == car_number) {
			cout << "���������� � ������ ������� ��� ����������" << endl;
			system("pause");
			return v;
		}
	}
	string brand = ConsoleHelper::readString("������� ����� ����������: ");
	string model = ConsoleHelper::readString("������� ������ ����������: ");
	string vin = ConsoleHelper::readString("������� VIN ����������: ");

	v = make_shared<Vehicle>(car_number,model,brand,vin);

	Vehicle::writeOneFile(v);

	return v;
}

shared_ptr<Request> Menu::inputRequest() {
	shared_ptr<Request> r = make_shared<Request>();
	int id = ConsoleHelper::readInt("������� id ������: ");
	for (shared_ptr<Request> req : ServiceStation::getInstance().getRequests()) {
		if (req->getId() == id) {
			cout << "����� � ������ id ��� ����������" << endl;
			system("pause");
			return r;
		}
	}

	ServiceStation::getInstance().showClient();
	
	cout << "������� ����� �������: ";
	int input = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size());

	ServiceStation::getInstance().showVehicle();
	cout << "������� ���������� ����� ����������: ";
	int input_v = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getVehicles().size());

	vector<shared_ptr<Service>> ser;

	ServiceStation::getInstance().showService();
	cout << "������� ������ �����, ����� ���������� ������ ��������� ������� 0(������ �������� ������ ����� ������)" << endl;

	while (true) {
		int inp = ConsoleHelper::readInt("������� ����� �������: ");
		if (inp > ServiceStation::getInstance().getServices().size()) {
			cout << "������ ������ ���! ������ ������������" << endl;
		}
		else if (inp == 0) {
			if (ser.size() == 0) {
				cout << "������ �����, ��� ��� ����� ���";
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

	int id = ConsoleHelper::readInt("������� id ������: ");
	for (shared_ptr<Service> ser : ServiceStation::getInstance().getServices()) {
		if (ser->getServiceId() == id) {
			cout << "������ � ������ id ��� ����������" << endl;
			return s;
		}
	}

	string name = ConsoleHelper::readString("������� �������� ������: ");

	double price = ConsoleHelper::readDouble("������� ����: ");

	int time = ConsoleHelper::readInt("������� ����� � ����� �� ���������� ������ ������: ");

	s = make_shared<Service>(id, name, price, time);

	return s;
}

//---------------------------------------------------------------------------//

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