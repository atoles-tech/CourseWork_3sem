#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>

#include "Menu.h"				//DANGER//
#include "HashFunc.h"
#include "User.h"
#include "ServiceStation.h"
#include "Client.h"
#include "Mechanic.h"
#include "Vehicle.h"
#include "Service.h"
#include "ConsoleHelper.h"		//DANGER//

/*Разработка автоматизированной системы функционирования станции технического обслуживания*/

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	ServiceStation::getInstance().init();
#if 1

	ServiceStation::getInstance().showClient();
	cout << endl;
	ServiceStation::getInstance().showVehicle();
	cout << endl;
	ServiceStation::getInstance().showMechanic();
	cout << endl;
	ServiceStation::getInstance().showService();
	cout << endl;
	ServiceStation::getInstance().showRequest();
	system("pause");
#endif
#if 0
	ServiceStation s = ServiceStation::getInstance();
	s.init();

	shared_ptr<Mechanic> m = make_shared<Mechanic>("admin", "123", "fs", "123@123.ru");
	m->addRequest(s.getRequests()[0]);
	s.addMechanic(m);
#endif
#if 0
	ServiceStation s = ServiceStation::getInstance();
	s.init();
	
	shared_ptr<Client> c = make_shared<Client>("user", "Nikolay", "Petrov");
	c->addRequest(s.getRequests()[0]);
	c->addVehicle(s.getVehicles()[0]);
	c->addVehicle(s.getVehicles()[1]);
	
	s.addClient(c);

	Client::writeFile(s.getClients());

	vector<shared_ptr<Client>> clients = Client::readFile(s.getRequests(), s.getVehicles());

	for (shared_ptr<Client> c : clients) {
		cout << c->getEmail() << " " << c->getVehicles()[1]->getVIN() << " " << c->getRequests()[0]->getId() << endl;
	}

	system("pause");
#endif
#if 0
	ServiceStation s = ServiceStation::getInstance();
	s.init();
	s.addRequest(make_shared<Request>(1, "user", s.getVehicles()[0], s.getServices(), 0));
	Request::writeFile(s.getRequests());
	vector<shared_ptr<Request>> r = Request::readFile(s.getVehicles(), s.getServices());
	for (shared_ptr<Service> service : r[0]->getServices()) {
		cout << service->getName() << endl;
	}
	system("pause");
#endif
#if 0
	ServiceStation s = ServiceStation::getInstance();
	s.addService(make_shared<Service>(1, "Починка двигателя",200.,100));
	s.addService(make_shared<Service>(2, "Замена масла", 20.5, 1));
	s.addService(make_shared<Service>(3, "Замена кузовной детали", 100., 7));
	s.addService(make_shared<Service>(4, "Починка салона", 250.2, 20));
	s.addService(make_shared<Service>(5, "Замена фары", 100., 10));
	
	Service::writeFile(s.getServices());
	vector<shared_ptr<Service>> services = Service::readFile();

	for (shared_ptr<Service> ser : services) {
		cout << ser->getName() << endl;
	}

	system("pause");
#endif
#if 0
	ServiceStation s = ServiceStation::getInstance();
	s.addVehicle(make_shared<Vehicle>("123456", "model x", "tesla", "12345678912345678"));
	s.addVehicle(make_shared<Vehicle>("183279", "model s", "tesla", "56578490562345658"));
	Vehicle::writeFile(s.getVehicles());

	vector<shared_ptr<Vehicle>> vehicles = Vehicle::readFile();
	
	cout << vehicles[0]->getVIN() << endl;
	cout << vehicles[1]->getVIN() << endl;

	system("pause");
#endif
#if 0
	vector<User> users;
	users.push_back(User("mech", Hash::getHash("1234", "ABCDEFGP"), 1, "ABCDEFGP", true));
	users.push_back(User("user1", Hash::getHash("1234", "ABCDEFGP"), 0, "ABCDEFGP",true));
	users.push_back(User("admin", Hash::getHash("admin", "ABCDEFGK"), 2, "ABCDEFGK",true));
	User::writeAllUsers(users);
	users = User::readUsers();
	cout << users[0].getLogin();
#endif

	Menu::initMenu();

	return 0;
}