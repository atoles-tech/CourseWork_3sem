#include "Menu.h"

using namespace std;

//---------------------------------------------------------------------------//

void Menu::initMenu() {
	cout.setf(ios::left);
	while (true) {
		system("cls");
		User::checkFile();

		cout << "=========������� ����=========" << endl;
		cout << "1.�����������" << endl;
		cout << "2.�����������" << endl;
		cout << "0.�����" << endl;
		cout << "------------------------------" << endl;
		cout << "��� �����: ";
		int input = ConsoleHelper::getOneInt("120");
		switch (input) {
		case 1:
			Menu::authorize();
			break;
		case 2:
			Menu::registr(0,false);
			break;
		case 0:
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
	shared_ptr<Mechanic> m;
	for (shared_ptr<Mechanic> mech : ServiceStation::getInstance().getMechanics()) {
		if (mech->getLogin() == name) {
			m = mech;
		}
	}
	vector<shared_ptr<Request>> req;
	for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
		if (r->getStatus() == 0) {
			req.push_back(r);
		}
	}
	while (true) {
		system("cls");
		cout << "����� ����������, " << name << "!" << endl;
		cout << "======���� ��������======" << endl;
		cout << "1.�������� ����� �������" << endl;
		cout << "2.�������� ��������� �������" << endl;
		cout << "3.��������� �����" << endl;
		cout << "0.����� �� ��������" << endl;
		cout << "-------------------------" << endl;
		cout << "��� �����: ";
		int input = ConsoleHelper::getOneInt("0123");
		int a;
		switch (input) {
		case 1:
			Request::showRequest(m->getRequests());
			break;
		case 2:
			Request::showRequest(req);
			break;
		case 3:
			if (m->getStatus()) {
				m->setStatus(false);
				for (shared_ptr<Request> r : m->getRequests()) {
					if (r->getStatus() == 1) {
						r->setStatus(2);
						break;
					}
				}
			}
			else {
				cout << "� ��� ��� ��������� ������" << endl;
				system("pause");
			}
			break;
		case 0:
			return;
		}
		system("pause");
	}
}

//---------------------------------------------------------------------------//

void Menu::userMenu(string name) {
	if (!ServiceStation::getInstance().hasClient(name)) {
		cout << "������� ���� ������ ����� ����������!" << endl;
		ServiceStation::getInstance().addClient(inputClient(name));
	}
	shared_ptr<Client> client;
	int a;
	for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
		if (c->getLogin() == name) {
			client = c;
			break;
		}
	}
	shared_ptr<Vehicle> v;
	shared_ptr<Request> r;
	while (true) {
		system("cls");
		cout << "����� ����������, " << name << "!" << endl;
		cout << "======���� ������������======" << endl;
		cout << "1.�������� ����� �������" << endl;
		cout << "2.�������� ����� ����" << endl;
		cout << "3.�������� ����������" << endl;
		cout << "4.������� �����" << endl;
		cout << "5.����������� ���� ���������" << endl;
		cout << "6.��������� �������� ������" << endl;
		cout << "7.������������� ������" << endl;
		cout << "8.�������� �����" << endl;
		cout << "0.����� �� ��������" << endl;
		cout << "----------------------------" << endl;
		cout << "��� �����: ";
		int input = ConsoleHelper::getOneInt("012345678");
		switch (input) {
		case 1:
			Request::showRequest(client->getRequests());
			break;
		case 2:
			Vehicle::showVehicle(client->getVehicles());
			break;
		case 3:
			v = Menu::inputVehicle();
			if (v->getNumber() == "()") {
				break;
			}
			client->addVehicle(v);
			ServiceStation::getInstance().addVehicle(v);
			cout << "���������� ��������" << endl;
			break;
		case 4:
			if (ServiceStation::getInstance().getServices().size() == 0) {
				cout << "���������� �������� ����� �� �������: ���������� �����" << endl;
				break;
			}
			else if (client->getVehicles().size() == 0) {
				cout << "���������� �������� ����� �� �������: ���������� �����������" << endl;
				break;
			}
			r = inputRequestForUser(name);
			if (r->getStatus() != -1) {
				ServiceStation::getInstance().addRequest(r);
				client->addRequest(r);
				cout << "����� ��������" << endl;
			}
			break;
		case 5:
			ServiceStation::getInstance().showMechanic();
			break;
		case 6:
			Request::showRequest(client->getRequests());
			cout << "������� ����� ������: ";
			r = ServiceStation::getInstance().getRequests()[ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size()) - 1];
			cout << "ID: " << r->getId() << endl;
			cout << "������: " << r->getClient() << endl;
			cout << "�������: " << (r->getMechanic() == "N/A" ? "������� �� ��������" : r->getMechanic()) << endl << endl;

			cout << "����������:" << endl;
			cout << "�����: " << r->getVehicle()->getNumber() << endl;
			cout << "�����: " << r->getVehicle()->getBrand() << endl;
			cout << "������: " << r->getVehicle()->getModel() << endl;
			cout << "VIN: " << r->getVehicle()->getVIN() << endl << endl;

			cout << "������:" << endl;
			Service::showService(r->getServices());
			break;
		case 7:
			if (client->getRequests().size() < 2) {
				cout << "������ ��� ���������� ������������" << endl;
			}
			system("cls");
			cout << "===������ ���������� �������===" << endl;
			cout << "1.����������� �� ID(1-9)" << endl;
			cout << "2.����������� �� ID(9-1)" << endl;
			cout << "3.����������� �� �������(A-Z)" << endl;
			cout << "4.����������� �� �������(Z-�)" << endl;
			cout << "5.����������� �� ��������(A-Z)" << endl;
			cout << "6.����������� �� ��������(Z-�)" << endl;
			cout << "-------------------------------" << endl;
			cout << "�������� ����� ����������:";

			switch (ConsoleHelper::getOneInt("123456")) {
			case 1:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getId() < b->getId(); }); break;
			case 2:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getId() > b->getId(); }); break;
			case 3:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getClient() < b->getClient(); }); break;
			case 4:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getClient() > b->getClient(); }); break;
			case 5:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getMechanic() < b->getMechanic(); }); break;
			case 6:sort(client->getRequests().begin(), client->getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getMechanic() > b->getMechanic(); }); break;
			}

			Client::writeFile(ServiceStation::getInstance().getClients());
			cout << "������ ������������� � ���������!" << endl;
			break;
		case 8: {
			vector<shared_ptr<Request>> req;
			for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
				if (c->getLogin() == name) {
					client = c;
					break;
				}
			}
			for (shared_ptr<Request> r : client->getRequests()) {
				if (!r->getBill().getStatus()) {
					req.push_back(r);
				}
			}
			if (req.size() == 0) {
				cout << "� ��� ��� �������� �������" << endl;
				break;
			}
			Request::showRequest(req);
			cout << "��������� ���������� ����� ������, ������� ������� ��������: ";
			a = ConsoleHelper::getIntToSize(req.size());
			req[a - 1]->getBill().approveBill();
			Request::writeFile(ServiceStation::getInstance().getRequests());
			cout << "����� ID: " << req[a - 1]->getId() << " �������" << endl;
			break;
		}
		case 0:
			return;
		}
		Client::writeFile(ServiceStation::getInstance().getClients());
		system("pause");
	}
}

//---------------------------------------------------------------------------//

void Menu::adminMenu(string name) {
	while (true) {
		system("cls");
		cout << "����� ����������, " << name << "!" << endl;
		cout << "==========���� ��������������==========" << endl;
		cout << "1.���������� �������� ��������" << endl;
		cout << "2.���������� ������� ���" << endl;
		cout << "0.����� �� ��������" << endl;
		cout << "---------------------------------------" << endl;
		cout << "��� �����: ";
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
		}
		system("pause");
	}
}

void Menu::adminMenuEditAccount(string name) {
	vector<User> users;
	int index;
	int temp;
	while (true) {
		system("cls");
		cout << "===���������� ����������===" << endl;
		cout << "1.�������� �������" << endl;
		cout << "2.�������� �������" << endl;
		cout << "3.������� �������" << endl;
		cout << "4.�������� �������" << endl;
		cout << "5.�������� ������" << endl;
		cout << "0.������� � ����" << endl;
		cout << "---------------------------" << endl;
		cout << "��� �����: ";
		int input = ConsoleHelper::getOneInt("012345");
		switch (input) {
		case 1:
			cout << "������� ���� ��� ��������(1 - ������, 2 - �������, 3 - �������������, 0 - ������): ";
			temp = ConsoleHelper::getOneInt("0123");
			if (temp == 0) {
				break;
			}
			registr(temp-1,true);
			cout << "������� ���������������" << endl;
			break;
		case 2:
			users = User::showUsers();
			cout << "������� ����� �������� (0 - ������): ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (index == -1) { break; }
			users[index] = changeUser(users, users[index]);
			cout << "��������� �������" << endl;
			User::writeAllUsers(users);
			Mechanic::writeFile(ServiceStation::getInstance().getMechanics());
			Client::writeFile(ServiceStation::getInstance().getClients());
			break;
		case 3:
			users = User::showUsers();
			cout << "������� ����� ��������(0 - ������): ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (index == -1) { break; }
			if (users[index].getLogin() == name) {
				cout << "�� �� ������ ������� ����" << endl;
				break;
			}
			for (int i = 0; i < ServiceStation::getInstance().getClients().size();i++) {
				if (ServiceStation::getInstance().getClients()[i]->getLogin() == users[index].getLogin()) {
					ServiceStation::getInstance().delClient(i);
					break;
				}
			}
			for (int i = 0; i < ServiceStation::getInstance().getMechanics().size(); i++) {
				if (ServiceStation::getInstance().getMechanics()[i]->getLogin() == users[index].getLogin()) {
					ServiceStation::getInstance().delMechanic(i);
					break;
				}
			}
			for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
				if (r->getClient() == users[index].getLogin()) {
					r->setClient(r->getClient() + "(del)");
				}
			}
			users.erase(users.begin() + index);
			Request::writeFile(ServiceStation::getInstance().getRequests());
			Client::writeFile(ServiceStation::getInstance().getClients());
			User::writeAllUsers(users);
			cout << "������� ������" << endl;
			break;
		case 4:
			User::showUsers();
			break;
		case 5:
			users = User::showUsers();
			cout << "������� ����� ��������(0 - ������): ";
			index = ConsoleHelper::getIntToSize(users.size()) - 1;
			if (index == -1) { break; }
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

void Menu::adminMenuEditData(string name) {
	while (true) {
		system("cls");
		cout << "========���������========" << endl;
		cout << "1.���������� �������" << endl;
		cout << "2.��������� �������" << endl;
		cout << "3.�������� �������" << endl;
		cout << "4.�������� �������" << endl;
		cout << "5.����������� ������" << endl;
		cout << "6.����� �������" << endl;
		cout << "7.��������� �������� �� �����" << endl;
		cout << "0.������� � ����" << endl;
		cout << "-------------------------" << endl;
		cout << "��� �����: ";
		int input = ConsoleHelper::getOneInt("01234567");
		switch (input) {
		case 1:
			adminMenuEditDataAdd(name);
			break;
		case 2:
			adminMenuEditDataEdit(name);
			break;
		case 3:
			adminMenuEditDataDelete(name);
			break;
		case 4:
			adminMenuEditDataShow(name);
			break;
		case 5:
			adminMenuEditDataSort(name);
			break;
		case 6:
			adminMenuEditDataSearch(name);
			break;
		case 7: {
			vector<shared_ptr<Request>> r;
			vector<shared_ptr<Mechanic>> m;
			
			for (shared_ptr<Request> req : ServiceStation::getInstance().getRequests()) {
				if (req->getStatus() == 0) {
					r.push_back(req);
				}
			}

			if (r.size() == 0) {
				cout << "��������� ������� ���!" << endl;
				system("pause");
				break;
			}

			for (shared_ptr<Mechanic> mech : ServiceStation::getInstance().getMechanics()) {
				if (!mech->getStatus()) {
					m.push_back(mech);
				}
			}

			if (m.size() == 0) {
				cout << "��������� ��������� ���!" << endl;
				system("pause");
				break;
			}

			Request::showRequest(r);
			cout << "������� ����� ������, �������� ���������� ��������� �����: ";
			int inp_1 = ConsoleHelper::getIntToSize(r.size());

			Mechanic::showMechanic(m);
			cout << "������� ����� ��������, ������� ������ ��������� �����: ";
			int inp_2 = ConsoleHelper::getIntToSize(m.size());

			r[inp_1 - 1]->setStatus(1);
			r[inp_1 - 1]->setMechanic(m[inp_2 - 1]->getName());

			m[inp_2 - 1]->setStatus(true);
			ServiceStation::getInstance().saveAllData();
			cout << "������ �������� �������!" << endl;
			system("pause");
			break;
		}
		case 0:
			return;
		}
	}
}

void Menu::adminMenuEditDataAdd(string name) {
	shared_ptr<Vehicle> v;
	shared_ptr<Request> r;
	shared_ptr<Service> s;
	int temp;
	system("cls");
	cout << "========����������========" << endl;
	cout << "1.�������� ����� ���������� �������" << endl;
	cout << "2.�������� �����" << endl;
	cout << "3.�������� ������" << endl;
	cout << "0.�����" << endl;
	cout << "--------------------------" << endl;
	cout << "��� �����: ";
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
			while (true) {
				temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size()) - 1;
				if (temp != -1) {
					break;
				}
			}
			ServiceStation::getInstance().getClients()[temp]->addVehicle(v);
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

void Menu::adminMenuEditDataEdit(string name) {
	system("cls");
	cout << "=======���������=======" << endl;
	cout << "1.�������� ����������" << endl;
	cout << "2.�������� �����" << endl;
	cout << "3.�������� ������" << endl;
	cout << "0.�����" << endl;
	cout << "------------------------" << endl;
	cout << "��� �����: ";
	int input = ConsoleHelper::getOneInt("0123");

	int temp, choose;

	switch (input) {
	case 1:
		ServiceStation::getInstance().showVehicle();
		if (ServiceStation::getInstance().getVehicles().size() == 0) {
			cout << "����������� ���!" << endl;
		}
		cout << "������� ����� ������: ";
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getVehicles().size());
		changeVehicle(ServiceStation::getInstance().getVehicles(), ServiceStation::getInstance().getVehicles()[temp - 1]);
		break;
	case 2:
		ServiceStation::getInstance().showRequest();
		if (ServiceStation::getInstance().getRequests().size() == 0) {
			cout << "������� ���!" << endl;
		}
		cout << "������� ����� ������: ";
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size());
		changeRequest(ServiceStation::getInstance().getRequests(), ServiceStation::getInstance().getRequests()[temp - 1]);
		break;
	case 3:
		ServiceStation::getInstance().showService();
		if (ServiceStation::getInstance().getServices().size() == 0) {
			cout << "����� ���!" << endl;
		}
		cout << "������� ����� ������: ";
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getServices().size());
		changeService(ServiceStation::getInstance().getServices(), ServiceStation::getInstance().getServices()[temp - 1]);
		break;
	case 0:
		return;
	}
	ServiceStation::getInstance().saveAllData();
}

void Menu::adminMenuEditDataDelete(string name) {
	system("cls");
	cout << "=======��������========" << endl;
	cout << "1.������� ����������" << endl;
	cout << "2.������� �����" << endl;
	cout << "3.������� ������" << endl;
	cout << "0.�����" << endl;
	cout << "-------------------------" << endl;
	cout << "��� �����: ";
	int input = ConsoleHelper::getOneInt("0123");

	int temp, choose;

	switch (input) {
	case 1:
		cout << "��������!" << endl;
		cout << "��� �������� ���������� ��������������� � ������, ����� ����� ������" << endl;
		ServiceStation::getInstance().showVehicle();
		cout << "������� ���������� ����� ����������(0-������): ";
		
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getVehicles().size());
		if (temp == 0) {
			break;
		}
		
		choose = ConsoleHelper::getChoose("�� ������� ��� ������ �������?(1-��, 0-���): ");
		if (choose == 0) {
			system("pause");
			break;
		}
		for (int i = 0; i < ServiceStation::getInstance().getRequests().size();i++) {
			if (ServiceStation::getInstance().getRequests()[i]->getVehicle()->getNumber() 
				== ServiceStation::getInstance().getVehicles()[temp - 1]->getNumber()) {
				ServiceStation::getInstance().delRequest(i);
				i--;
			}
		}
		for (shared_ptr<Mechanic> m : ServiceStation::getInstance().getMechanics()) {
			for (int i = 0; i < m->getRequests().size(); i++) {
				if (m->getRequests()[i]->getStatus() == 1 && m->getRequests()[i]->getVehicle()->getNumber() == ServiceStation::getInstance().getVehicles()[temp-1]->getNumber()) {
					m->setStatus(false);
				}
				if (m->getRequests()[i]->getVehicle()->getNumber() == ServiceStation::getInstance().getVehicles()[temp - 1]->getNumber()) {
					m->delRequest(i);
					i--;
				}
			}
		}
		for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
			for (int i = 0; i < c->getVehicles().size(); i++) {
				if (c->getVehicles()[i]->getNumber() == ServiceStation::getInstance().getVehicles()[temp - 1]->getNumber()) {
					c->delVehicle(i);
				}
			}
			for (int i = 0; i < c->getRequests().size(); i++) {
				if (c->getRequests()[i]->getVehicle()->getNumber() == ServiceStation::getInstance().getVehicles()[temp - 1]->getNumber()) {
					c->delRequest(i);
				}
			}
		}
		ServiceStation::getInstance().delVehicle(temp - 1);
		cout << "���������� ������" << endl;
		break;
	case 2:
		ServiceStation::getInstance().showRequest();
		cout << "������� ���������� ����� ������(0 - ������): ";
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size());
		if (temp == 0) { break; }
		choose = ConsoleHelper::getChoose("�� ������� ��� ������ �������?(1-��, 0-���): ");
		if (choose == 0) {
			system("pause");
			break;
		}
		for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
			for (int i = 0; i < c->getRequests().size();i++) {
				if (c->getRequests()[i]->getId() == ServiceStation::getInstance().getRequests()[temp - 1]->getId()) {
					c->delRequest(i);
					i--;
				}
			}
		}
		for (shared_ptr<Mechanic> c : ServiceStation::getInstance().getMechanics()) {
			for (int i = 0; i < c->getRequests().size(); i++) {
				if (c->getRequests()[i]->getId() == ServiceStation::getInstance().getRequests()[temp - 1]->getId()) {
					c->delRequest(i);
					i--;
				}
			}
		}
		ServiceStation::getInstance().delRequest(temp - 1);
		break;
	case 3:
		ServiceStation::getInstance().showService();
		cout << "������� ���������� ����� ������(0 - ������): ";
		temp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getServices().size());
		if (temp == 0) { break; }
		choose = ConsoleHelper::getChoose("�� ������� ��� ������ �������?(1-��, 0-���): ");
		if (choose == 0) {
			system("pause");
			break;
		}
		for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
			for (int i = 0; i < r->getServices().size(); i++) {
				if (r->getServices()[i]->getServiceId() == ServiceStation::getInstance().getServices()[temp - 1]->getServiceId()) {
					r->delService(i);
				}
			}
		}
		ServiceStation::getInstance().delService(temp - 1);
		for (int i = 0; i < ServiceStation::getInstance().getRequests().size(); i++) {
			if (ServiceStation::getInstance().getRequests()[i]->getServices().size() == 0) {
				for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
					for (int j = 0; j < c->getRequests().size(); j++) {
						if (c->getRequests()[j]->getId() == ServiceStation::getInstance().getRequests()[i]->getId()) {
							c->delRequest(j);
							j--;
						}
					}
				}
				for (shared_ptr<Mechanic> c : ServiceStation::getInstance().getMechanics()) {
					for (int j = 0; j < c->getRequests().size(); j++) {
						if (c->getRequests()[j]->getId() == ServiceStation::getInstance().getRequests()[i]->getId()) {
							c->delRequest(j);
							j--;
						}
					}
				}
				ServiceStation::getInstance().delRequest(i);
			}
		}
		cout << "������ �������" << endl;
		break;
	case 0:
		return;
	}
	ServiceStation::getInstance().saveAllData();
}

void Menu::adminMenuEditDataShow(string name) {
	system("cls");
	cout << "===========�������� ������ ���============" << endl;
	cout << "1.�������� ��������" << endl;
	cout << "2.�������� ���������" << endl;
	cout << "3.�������� ����������" << endl;
	cout << "4.�������� ������" << endl;
	cout << "5.�������� ������" << endl;
	cout << "6.�������� ��������� ���������� � �������" << endl;
	cout << "7.�������� ��������� ���������� � ������" << endl;
	cout << "8.�������� ��������� ���������� � ��������" << endl;
	cout << "0.�����" << endl;
	cout << "------------------------------------------" << endl;
	cout << "��� �����: ";
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
		cout << "������� ����� �������(0 - ������): ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getClients().size());
		if (n == 0) { break; }
		shared_ptr<Client> c = ServiceStation::getInstance().getClients()[n - 1];
		c->showInfo();
		system("pause");
		break;
	}
	case 7: {
		ServiceStation::getInstance().showRequest();
		cout << "������� ����� ������(0 - ������): ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getRequests().size());
		if (n == 0) { break; }
		shared_ptr<Request> req = ServiceStation::getInstance().getRequests()[n-1];
		cout << "ID: " << req->getId() << endl;
		cout << "������: " << req->getClient() << endl;
		cout << "�������: " << (req->getMechanic() == "N/A"?"������� �� ��������": req->getMechanic()) << endl << endl;

		cout << "����������:" << endl;
		cout << "�����: " << req->getVehicle()->getNumber() << endl;
		cout << "�����: " << req->getVehicle()->getBrand() << endl;
		cout << "������: " << req->getVehicle()->getModel() << endl;
		cout << "VIN: " << req->getVehicle()->getVIN() << endl << endl;

		cout << "������:" << endl;
		Service::showService(req->getServices());
		system("pause");
		break;
	}
	case 8: {
		ServiceStation::getInstance().showMechanic();
		cout << "������� ����� ������(0 - ������): ";
		int n = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getMechanics().size());
		if (n == 0) { break; }
		shared_ptr<Mechanic> m = ServiceStation::getInstance().getMechanics()[n - 1];
		m->showInfo();
		system("pause");
	}
		break;
	case 0:
		return;
	}
	ServiceStation::getInstance().saveAllData();
}

void Menu::adminMenuEditDataSort(string name) {
	ServiceStation& s = ServiceStation::getInstance();
	system("cls");
	cout << "======���� ����������======" << endl;
	cout << "1.������������� ����������" << endl;
	cout << "2.������������� ������" << endl;
	cout << "3.������������� ������" << endl;
	cout << "4.������������� ���������" << endl;
	cout << "5.������������� ��������" << endl;
	cout << "0.�����" << endl;
	cout << "--------------------------" << endl;
	cout << "��� �����: ";

	int input = ConsoleHelper::getOneInt("012345");

	switch (input) {
	case 1:
		if (s.getVehicles().size() < 2) {
			cout << "������ ��� ���������� ������������" << endl;
		}
		system("cls");
		cout << "===������ ���������� ����===" << endl;
		cout << "1.����������� �� �������������� ������(A-Z)" << endl;
		cout << "2.����������� �� �������������� ������(Z-A)" << endl;
		cout << "3.����������� �� �����(A-Z)" << endl;
		cout << "4.����������� �� �����(Z-�)" << endl;
		cout << "5.����������� �� ������(A-Z)" << endl;
		cout << "6.����������� �� ������(Z-�)" << endl;
		cout << "7.����������� �� VIN(A-Z)" << endl;
		cout << "8.����������� �� VIN(Z-A)" << endl;
		cout << "�������� ����� ����������:";

		switch (ConsoleHelper::getOneInt("12345678")) {
		case 1:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getNumber() < b->getNumber(); }); break;
		case 2:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getNumber() > b->getNumber(); }); break;
		case 3:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getBrand() < b->getBrand(); }); break;
		case 4:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getBrand() > b->getBrand(); }); break;
		case 5:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getModel() < b->getModel(); }); break;
		case 6:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getModel() > b->getModel(); }); break;
		case 7:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getVIN() < b->getVIN(); }); break;
		case 8:sort(s.getVehicles().begin(), s.getVehicles().end(), [](const shared_ptr<Vehicle>& a, const shared_ptr<Vehicle>& b) {return a->getVIN() > b->getVIN(); }); break;
		}

		Vehicle::writeFile(s.getVehicles());
		cout << "������ ������������� � ���������!" << endl;

		break;
	case 2:
		if (s.getRequests().size() < 2) {
			cout << "������ ��� ���������� ������������" << endl;
		}
		system("cls");
		cout << "===������ ���������� �������===" << endl;
		cout << "1.����������� �� ID(1-9)" << endl;
		cout << "2.����������� �� ID(9-1)" << endl;
		cout << "3.����������� �� �������(A-Z)" << endl;
		cout << "4.����������� �� �������(Z-�)" << endl;
		cout << "5.����������� �� ��������(A-Z)" << endl;
		cout << "6.����������� �� ��������(Z-�)" << endl;
		cout << "�������� ����� ����������:";

		switch (ConsoleHelper::getOneInt("123456")) {
		case 1:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getId() < b->getId(); }); break;
		case 2:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getId() > b->getId(); }); break;
		case 3:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getClient() < b->getClient(); }); break;
		case 4:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getClient() > b->getClient(); }); break;
		case 5:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getMechanic() < b->getMechanic(); }); break;
		case 6:sort(s.getRequests().begin(), s.getRequests().end(), [](const shared_ptr<Request>& a, const shared_ptr<Request>& b) {return a->getMechanic() > b->getMechanic(); }); break;
		}

		Request::writeFile(s.getRequests());
		cout << "������ ������������� � ���������!" << endl;
		break;
	case 3:
		if (s.getServices().size() < 2) {
			cout << "������ ��� ���������� ������������" << endl;
		}
		system("cls");
		cout << "===������ ���������� �����===" << endl;
		cout << "1.����������� �� ID(1-9)" << endl;
		cout << "2.����������� �� ID(9-1)" << endl;
		cout << "3.����������� �� ��������(A-Z)" << endl;
		cout << "4.����������� �� ��������(Z-�)" << endl;
		cout << "5.����������� �� ����(1-9)" << endl;
		cout << "6.����������� �� ����(9-1)" << endl;
		cout << "7.����������� �� �������(1-9)" << endl;
		cout << "8.����������� �� �������(9-1)" << endl;
		cout << "�������� ����� ����������:";

		switch (ConsoleHelper::getOneInt("12345678")) {
		case 1:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getServiceId() < b->getServiceId(); }); break;
		case 2:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getServiceId() > b->getServiceId(); }); break;
		case 3:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getName() < b->getName(); }); break;
		case 4:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getName() > b->getName(); }); break;
		case 5:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getPrice() < b->getPrice(); }); break;
		case 6:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getPrice() > b->getPrice(); }); break;
		case 7:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getTime() < b->getTime(); }); break;
		case 8:sort(s.getServices().begin(), s.getServices().end(), [](const shared_ptr<Service>& a, const shared_ptr<Service>& b) {return a->getTime() > b->getTime(); }); break;
		}

		Service::writeFile(s.getServices());
		cout << "������ ������������� � ���������!" << endl;
		break;
	case 4:
		if (s.getMechanics().size() < 2) {
			cout << "������ ��� ���������� ������������" << endl;
		}
		system("cls");
		cout << "===������ ���������� ���������===" << endl;
		cout << "1.����������� �� �������(A-Z)" << endl;
		cout << "2.����������� �� �������(Z-A))" << endl;
		cout << "3.����������� �� email(A-Z)" << endl;
		cout << "4.����������� �� email(Z-�)" << endl;
		cout << "5.����������� �� ���������(�� ����� - �����)" << endl;
		cout << "6.����������� �� ���������(����� - �� �����)" << endl;
		cout << "�������� ����� ����������:";

		switch (ConsoleHelper::getOneInt("123456")) {
		case 1:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getSurname() < b->getSurname(); }); break;
		case 2:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getSurname() > b->getSurname(); }); break;
		case 3:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getEmail() < b->getEmail(); }); break;
		case 4:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getEmail() > b->getEmail(); }); break;
		case 5:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getStatus() < b->getStatus(); }); break;
		case 6:sort(s.getMechanics().begin(), s.getMechanics().end(), [](const shared_ptr<Mechanic>& a, const shared_ptr<Mechanic>& b) {return a->getStatus() > b->getStatus(); }); break;
		}

		Mechanic::writeFile(s.getMechanics());
		cout << "������ ������������� � ���������!" << endl;
		break;
	case 5:
		if (s.getClients().size() < 2) {
			cout << "������ ��� ���������� ������������" << endl;
		}
		system("cls");
		cout << "===������ ���������� ��������===" << endl;
		cout << "1.����������� �� �������(A-Z)" << endl;
		cout << "2.����������� �� �������(Z-A))" << endl;
		cout << "3.����������� �� email(A-Z)" << endl;
		cout << "4.����������� �� email(Z-�)" << endl;
		cout << "�������� ����� ����������:";

		switch (ConsoleHelper::getOneInt("1234")) {
		case 1:sort(s.getClients().begin(), s.getClients().end(), [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {return a->getSurname() < b->getSurname(); }); break;
		case 2:sort(s.getClients().begin(), s.getClients().end(), [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {return a->getSurname() > b->getSurname(); }); break;
		case 3:sort(s.getClients().begin(), s.getClients().end(), [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {return a->getEmail() < b->getEmail(); }); break;
		case 4:sort(s.getClients().begin(), s.getClients().end(), [](const shared_ptr<Client>& a, const shared_ptr<Client>& b) {return a->getEmail() > b->getEmail(); }); break;
		}

		Client::writeFile(s.getClients());
		cout << "������ ������������� � ���������!" << endl;
		break;
	case 0:return;
	}
	system("pause");
}

void Menu::adminMenuEditDataSearch(string name) {
	system("cls");
	cout << "=====���� ������=====" << endl;
	cout << "1.����� ����������" << endl;
	cout << "2.����� �����" << endl;
	cout << "3.����� ������" << endl;
	cout << "4.����� ��������" << endl;
	cout << "5.����� �������" << endl;
	cout << "0.�����" << endl;
	cout << "---------------------" << endl;
	cout << "��� �����: ";

	int input = ConsoleHelper::getOneInt("012345");

	switch (input) {
	case 1:
		adminMenuEditDataSearchVehicle();
		break;
	case 2:
		adminMenuEditDataSearchRequest();
		break;
	case 3:
		adminMenuEditDataSearchService();
		break;
	case 4:
		adminMenuEditDataSearchMechanic();
		break;
	case 5:
		adminMenuEditDataSearchClient();
		break;
	}

	if (input == 0) {
		return;
	}

	system("pause");
}

void Menu::adminMenuEditDataSearchVehicle() {
	system("cls");
	cout << "===���� ������ ����������===" << endl;
	cout << "1.����� �� ������" << endl;
	cout << "2.����� �� �����" << endl;
	cout << "3.����� �� ������" << endl;
	cout << "----------------------------" << endl;
	cout << "��� �����: ";

	int input = ConsoleHelper::getOneInt("123");

	vector<shared_ptr<Vehicle>> vehicles;

	string search;

	switch (input) {
	case 1:
		search = ConsoleHelper::readString("������� ����� ����������: ");
		
		for (shared_ptr<Vehicle> v : ServiceStation::getInstance().getVehicles()) {
			if (v->getNumber().find(search) != string::npos) {
				vehicles.push_back(v);
				break;
			}
		}

		break;
	case 2:
		search = ConsoleHelper::readString("������� ����� ����������: ");

		for (shared_ptr<Vehicle> v : ServiceStation::getInstance().getVehicles()) {
			if (v->getBrand().find(search) != string::npos) {
				vehicles.push_back(v);
			}
		}

		break;
	case 3:
		search = ConsoleHelper::readString("������� ������ ����������: ");

		for (shared_ptr<Vehicle> v : ServiceStation::getInstance().getVehicles()) {
			if (v->getModel().find(search) != string::npos) {
				vehicles.push_back(v);
			}
		}

		break;
	}

	if (vehicles.size() == 0) {
		cout << "����������� �� �������!" << endl;
		return;
	}

	Vehicle::showVehicle(vehicles);
}

void Menu::adminMenuEditDataSearchRequest() {
	system("cls");
	cout << "===���� ������ �������===" << endl;
	cout << "1.����� �� ID" << endl;
	cout << "2.����� �� ��������" << endl;
	cout << "3.����� �� �������" << endl;
	cout << "-------------------------" << endl;
	cout << "��� �����: ";
	

	int input = ConsoleHelper::getOneInt("123");

	vector<shared_ptr<Request>> requests;

	string search;
	int id_search;

	switch (input) {
	case 1:
		id_search = ConsoleHelper::readInt("������� ID: ");

		for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
			if (r->getId() == id_search) {
				requests.push_back(r);
				break;
			}
		}

		break;
	case 2:
		search = ConsoleHelper::readString("������� ����� ��������: ");

		for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
			if (r->getMechanic().find(search) != string::npos) {
				requests.push_back(r);
			}
		}

		break;
	case 3:
		search = ConsoleHelper::readString("������� ����� �������: ");

		for (shared_ptr<Request> r : ServiceStation::getInstance().getRequests()) {
			if (r->getClient().find(search) != string::npos) {
				requests.push_back(r);
			}
		}

		break;
	}

	if (requests.size() == 0) {
		cout << "������� �� �������!" << endl;
		return;
	}

	Request::showRequest(requests);
}

void Menu::adminMenuEditDataSearchService() {
	system("cls");
	cout << "===���� ������ �����===" << endl;
	cout << "1.����� �� ID" << endl;
	cout << "2.����� �� ��������" << endl;
	cout << "3.����� �� �������" << endl;
	cout << "-----------------------" << endl;
	cout << "��� �����: ";

	int input = ConsoleHelper::getOneInt("123");

	vector<shared_ptr<Service>> services;

	string search;
	int id_search;

	switch (input) {
	case 1:
		id_search = ConsoleHelper::readInt("������� ID: ");

		for (shared_ptr<Service> s : ServiceStation::getInstance().getServices()) {
			if (s->getServiceId() == id_search) {
				services.push_back(s);
				break;
			}
		}

		break;
	case 2:
		search = ConsoleHelper::readString("������� �������� ������: ");

		for (shared_ptr<Service> s : ServiceStation::getInstance().getServices()) {
			if (s->getName().find(search) != string::npos) {
				services.push_back(s);
			}
		}

		break;
	case 3:
		id_search = ConsoleHelper::readInt("������� ����� ���������� ������: ");

		for (shared_ptr<Service> s : ServiceStation::getInstance().getServices()) {
			if (s->getTime() == id_search) {
				services.push_back(s);
			}
		}

		break;
	}

	if (services.size() == 0) {
		cout << "������� �� �������!" << endl;
	}

	Service::showService(services);
}
void Menu::adminMenuEditDataSearchMechanic() {
	system("cls");
	cout << "===���� ������ ���������===" << endl;
	cout << "1.����� �� ������" << endl;
	cout << "2.����� �� �������" << endl;
	cout << "3.����� �� ���������" << endl;
	cout << "---------------------------" << endl;
	cout << "��� �����: ";

	int input = ConsoleHelper::getOneInt("123");

	vector<shared_ptr<Mechanic>> mechanics;

	string search;
	int id_search;

	switch (input) {
	case 1:
		search = ConsoleHelper::readString("������� �����: ");

		for (shared_ptr<Mechanic> m : ServiceStation::getInstance().getMechanics()) {
			if (m->getLogin() == search) {
				mechanics.push_back(m);
				break;
			}
		}

		break;
	case 2:
		search = ConsoleHelper::readString("������� �������: ");

		for (shared_ptr<Mechanic> m : ServiceStation::getInstance().getMechanics()) {
			if (m->getSurname().find(search) != string::npos) {
				mechanics.push_back(m);
			}
		}

		break;
	case 3:
		cout << "�� ������� ����� �������(1) ��� ���������(0)?" << endl;
		cout << "��� �����: ";

		id_search = ConsoleHelper::getOneInt("01");

		for (shared_ptr<Mechanic> m : ServiceStation::getInstance().getMechanics()) {
			if (m->getStatus() == true && id_search == 1) {
				mechanics.push_back(m);
			}
			else if(m->getStatus() == false && id_search == 0){
				mechanics.push_back(m);
			}
		}

		break;
	}

	if (mechanics.size() == 0) {
		cout << "������� �� �������!" << endl;
	}

	Mechanic::showMechanic(mechanics);
}
void Menu::adminMenuEditDataSearchClient() {
	system("cls");
	cout << "===���� ������ ��������===" << endl;
	cout << "1.����� �� ������" << endl;
	cout << "2.����� �� �������" << endl;

	cout << "�������� ����� ����:";

	int input = ConsoleHelper::getOneInt("12");

	vector<shared_ptr<Client>> clients;

	string search;

	switch (input) {
	case 1:
		search = ConsoleHelper::readString("������� �����: ");

		for (shared_ptr<Client> m : ServiceStation::getInstance().getClients()) {
			if (m->getLogin().find(search) != string::npos) {
				clients.push_back(m);
				break;
			}
		}

		break;
	case 2:
		search = ConsoleHelper::readString("������� �������: ");

		for (shared_ptr<Client> m : ServiceStation::getInstance().getClients()) {
			if (m->getSurname().find(search) != string::npos) {
				clients.push_back(m);
			}
		}

		break;
	}
	if (clients.size() == 0) {
		cout << "������� �� �������!" << endl;
	}

	Client::showClient(clients);
}

//----------------------------------------------------------------------------------------//

void Menu::authorize() {
	system("cls");
	vector<User> users = User::readUsers();
	cout << "======�����������======" << endl;
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

void Menu::registr(int role,bool access) {
	system("cls");

	vector<User> users = User::readUsers();
	cout << "======�����������======" << endl;
	string login = ConsoleHelper::readString("������� �����: ");
	if (login.size() < 4) {
		cout << "����������� ����� ������ ������ ���� 4" << endl;
		system("pause");
		return;
	}
	if (login.size() > 15) {
		cout << "������������ ����� ������ 15 ��������" << endl;
		system("pause");
		return;
	}
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
	
	cout << endl;

	if (password.size() < 4) {
		cout << "����������� ����� ������ ������ ���� 4" << endl;
		system("pause");
		return;
	}

	string salt = Hash::generateSalt();

	long long int hash = Hash::getHash(password, salt);

	User user(login, hash, role, salt, access);

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
	string car_number;
	while (true) {
		car_number = ConsoleHelper::readString("������� ����� ����������: ");
		if (!ConsoleHelper::checkString(car_number)) {
			cout << "������� ������������ �������" << endl;
			continue;
		}
		if (car_number.size() < 4) {
			cout << "����������� ����� �������������� ������ ������ ���� 4 ������a!" << endl;
			continue;
		}
		break;
	}
	
	for (shared_ptr<Vehicle> veh : ServiceStation::getInstance().getVehicles()) {
		if (veh->getNumber() == car_number) {
			cout << "���������� � ������ ������� ��� ����������" << endl;
			system("pause");
			return v;
		}
	}
	string brand;
	while (true) {
		brand = ConsoleHelper::readString("������� ����� ����������: ");
		if (!ConsoleHelper::checkString(brand)) {
			cout << "������� ������������ �������" << endl;
			continue;
		}
		break;
	}
	string model;
	while (true) {
		model = ConsoleHelper::readString("������� ������ ����������: ");
		if (!ConsoleHelper::checkString(model)) {
			cout << "������� ������������ �������" << endl;
			continue;
		}
		break;
	}
	string vin;
	while (true) {
		vin = ConsoleHelper::readString("������� VIN ����������: ");
		if (vin.size() != 17) {
			cout << "����� VIN ������ ���� 17 ��������" << endl;
			continue;
		}
		break;
	}

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

	if (ServiceStation::getInstance().getClients()[input - 1]->getVehicles().size() == 0) {
		cout << "����������� � ������� �� �������!" << endl;
		return r;
	}

	Vehicle::showVehicle(ServiceStation::getInstance().getClients()[input - 1]->getVehicles());
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

	r = make_shared<Request>(id, ServiceStation::getInstance().getClients()[input - 1]->getLogin(), ServiceStation::getInstance().getVehicles()[input_v - 1], ser, 0,false);

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

shared_ptr<Request> Menu::inputRequestForUser(string login) {
	shared_ptr<Request> r = make_shared<Request>();
	int id = ConsoleHelper::readInt("������� id ������: ");
	for (shared_ptr<Request> req : ServiceStation::getInstance().getRequests()) {
		if (req->getId() == id) {
			cout << "����� � ������ id ��� ����������" << endl;
			system("pause");
			return r;
		}
	}

	shared_ptr<Client> client;

	for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
		if (c->getLogin() == login) {
			client = c;
			break;
		}
	}

	Vehicle::showVehicle(client->getVehicles());
	cout << "������� ���������� ����� ����������: ";
	int input_v = ConsoleHelper::getIntToSize(client->getVehicles().size());

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

	r = make_shared<Request>(id, client->getLogin(), client->getVehicles()[input_v - 1], ser, 0,false);

	Request::writeOneFile(r);

	return r;
}

//---------------------------------------------------------------------------//

User Menu::changeUser(vector<User> users, User user) {
	while (true) {
		system("cls");
		cout << "���� ��������� ������������:" << endl;
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
				for (shared_ptr<Client> c : ServiceStation::getInstance().getClients()) {
					if (c->getLogin() == user.getLogin()) {
						c->setLogin(login);
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

void Menu::changeVehicle(vector<shared_ptr<Vehicle>> vehicles, shared_ptr<Vehicle> vehicle) {
	while (true) {
		system("cls");
		cout << "���� ��������� ����������:" << endl;
		cout << "�����: " << vehicle->getBrand() << endl;
		cout << "������: " << vehicle->getModel() << endl;
		cout << "�����: " << vehicle->getNumber() << endl;
		cout << "VIN: " << vehicle->getVIN() << endl;

		cout << "1.�������� �����" << endl;
		cout << "2.�������� ������" << endl;
		cout << "3.�������� �����" << endl;
		cout << "4.�������� VIN" << endl;
		cout << "0.�����" << endl;

		int input = ConsoleHelper::getOneInt("01234");

		string tmp;
		bool t = false;
		switch (input) {
		case 1:
			tmp = ConsoleHelper::readString("������� ����� �����: ");
			if (!ConsoleHelper::checkString(tmp)) {
				cout << "�������� ������ ������!" << endl;
				break;
			}
			vehicle->setBrand(tmp);
			break;
		case 2:
			tmp = ConsoleHelper::readString("������� ����� ������: ");
			if (!ConsoleHelper::checkString(tmp)) {
				cout << "�������� ������ ������!" << endl;
				break;
			}
			vehicle->setModel(tmp);
			break;
		case 3:
			tmp = ConsoleHelper::readString("������� ����� �����: ");
			if (!ConsoleHelper::checkString(tmp)) {
				cout << "�������� ������ ������!" << endl;
				break;
			}
			vehicle->setNumber(tmp);
			break;
		case 4:
			tmp = ConsoleHelper::readString("������� ����� VIN: ");
			if (tmp.size() != 17) {
				cout << "����� VIN ������ ���� 17 ��������" << endl;
				break;
			}
			for (shared_ptr<Vehicle> v : vehicles) {
				if(v->getVIN() == tmp){
					t = true;
				}
			}
			if (ConsoleHelper::checkString(tmp) == false) {
				cout << "�������� ������ ������!" << endl;
				break;
			}
			if (!t) {
				vehicle->setVIN(tmp);
			}
			else {
				cout << "���������� � ������ VIN ��� ����������" << endl;
			}
			break;
		}

		if (input == 0) {
			return;
		}
		system("pause");
	}
}

void Menu::changeRequest(vector<shared_ptr<Request>> requests, shared_ptr<Request> req) {
	while (true) {
		system("cls");
		cout << "���� ��������� ������:" << endl;
		cout << "ID: " << req->getId() << endl;
		cout << "������: " << req->getClient() << endl;
		cout << "�������: " << (req->getMechanic() == "N/A" ? "������� �� ��������" : req->getMechanic()) << endl << endl;

		cout << "����������:" << endl;
		cout << "�����: " << req->getVehicle()->getNumber() << endl;
		cout << "�����: " << req->getVehicle()->getBrand() << endl;
		cout << "������: " << req->getVehicle()->getModel() << endl;
		cout << "VIN: " << req->getVehicle()->getVIN() << endl << endl;

		cout << "������:" << endl;
		Service::showService(req->getServices());

		cout << "1.�������� ID" << endl;
		cout << "2.�������� ������" << endl;
		cout << "3.������� ������" << endl;
		cout << "0.�����" << endl;

		int input = ConsoleHelper::getOneInt("0123");

		int tmp;
		bool t = false;
		switch (input) {
		case 1:
			tmp = ConsoleHelper::readInt("������� ����� ID: ");
			for (shared_ptr<Request> r: requests) {
				if (r->getId() == tmp) {
					t = true;
				}
			}
			if (!t) {
				req->setId(tmp);
				cout << "ID �������" << endl;
			}
			else {
				cout << "������ ID ��� ����������!" << endl;
			}
			break;
		case 2:
			ServiceStation::getInstance().showService();
			if (ServiceStation::getInstance().getServices().size() == 0) {
				cout << "����� ���!" << endl;
				break;
			}
			cout << "������� ������ ������� �� ������� ��������: ";
			tmp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getServices().size());
			for (shared_ptr<Service> s : req->getServices()) {
				if (s->getServiceId() == ServiceStation::getInstance().getServices()[tmp - 1]->getServiceId()) {
					cout << "������ ������ ��� ���������" << endl;
					t = true;
				}
			}
			if (!t) {
				req->addService(ServiceStation::getInstance().getServices()[tmp - 1]);
				cout << "����� ������ ���������!" << endl;
			}
			break;
		case 3:
			if (req->getServices().size() == 1) {
				cout << "������ ������� ��������� ������!" << endl;
				break;
			}
			Service::showService(req->getServices());
			cout << "������� ����� ������, ������� �� ������� ��������: ";
			tmp = ConsoleHelper::getIntToSize(ServiceStation::getInstance().getServices().size());
			req->delService(tmp - 1);
			cout << "������ �������!" << endl;
			break;
		}
		if (input == 0) {
			return;
		}
		system("pause");
	}
}

void Menu::changeService(vector<shared_ptr<Service>> services, shared_ptr<Service> ser) {
	while (true) {
		system("cls");
		cout << "���� ��������� �����:" << endl;
		cout << "ID: " << ser->getServiceId() << endl;
		cout << "��������: " << ser->getName() << endl;
		cout << "���������: " << ser->getPrice() << endl;
		cout << "�����: " << ser->getTime() << endl << endl;

		cout << "1.�������� ID" << endl;
		cout << "2.�������� ��������" << endl;
		cout << "3.�������� ���������" << endl;
		cout << "4.�������� �����" << endl;
		cout << "0.�����" << endl;

		int input = ConsoleHelper::getOneInt("01234");

		int tmp;
		string temp;
		double price;
		bool t = false;

		switch (input) {
		case 1:
			tmp = ConsoleHelper::readInt("������� ����� ID: ");
			for (shared_ptr<Service> s : services) {
				if (s->getServiceId() == tmp) {
					t = true;
					cout << "������ � ������ ID ��� ����������!" << endl;
				}
			}
			if (!t) {
				ser->setServiceId(tmp);
				cout << "����� ID ����������" << endl;
			}
			break;
		case 2:
			temp = ConsoleHelper::readString("������� ����� ��������: ");
			for (shared_ptr<Service> s : services) {
				if (s->getName() == temp) {
					t = true;
					cout << "������ � ������ ��������� ��� ����������!" << endl;
				}
			}
			if (!t) {
				ser->setName(temp);
				cout << "����� �������� �����������" << endl;
			}
			break;
		case 3:
			price = ConsoleHelper::readDouble("������� ����� ���������: ");
			ser->setPrice(price);
			cout << "����� ��������� �����������" << endl;
			break;
		case 4:
			tmp = ConsoleHelper::readInt("������� ����� �����: ");
			ser->setTime(tmp);
			cout << "����� ����� �����������" << endl;
			break;
		}
		
		if (input == 0) {
			return;
		}
	}

}