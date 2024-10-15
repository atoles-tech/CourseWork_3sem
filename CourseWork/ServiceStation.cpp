#include "ServiceStation.h"

ServiceStation ServiceStation::service; // Инициализация статического поля

ServiceStation& ServiceStation::getInstance() {
	return service;
}

void ServiceStation::addVehicle(shared_ptr<Vehicle> v) {
	vehicles.push_back(v);
}

void ServiceStation::addClient(shared_ptr<Client> c) {
	clients.push_back(c);
}

void ServiceStation::addService(shared_ptr<Service> s) {
	services.push_back(s);
}

void ServiceStation::addRequest(shared_ptr<Request> r) {
	requests.push_back(r);
}

void ServiceStation::addMechanic(shared_ptr<Mechanic> m) {
	mechanics.push_back(m);
}

void ServiceStation::init() {
	this->vehicles = Vehicle::readFile();
	this->services = Service::readFile();
	this->requests = Request::readFile(vehicles,services);
	this->clients = Client::readFile(requests, vehicles);
	this->mechanics = Mechanic::readFile(requests);
}

void ServiceStation::saveAllData() {
	Vehicle::writeFile(vehicles);
	Service::writeFile(services);
	Request::writeFile(requests);
	Client::writeFile(clients);
	Mechanic::writeFile(mechanics);
}

/*Проверка*/
bool ServiceStation::hasClient(string login) {
	for (shared_ptr<Client> c : clients) {
		if (c->getLogin() == login) {
			return true;
		}
	}
	return false;
}

bool ServiceStation::hasMechanic(string login) {
	for (shared_ptr<Mechanic> m : mechanics) {
		if (m->getLogin() == login) {
			return true;
		}
	}
	return false;
}

/*Геттеры*/
vector<shared_ptr<Vehicle>> ServiceStation::getVehicles() {return vehicles;}
vector<shared_ptr<Client>> ServiceStation::getClients() {return clients;}
vector<shared_ptr<Service>> ServiceStation::getServices() { return services; }
vector<shared_ptr<Request>> ServiceStation::getRequests() { return requests; }
vector<shared_ptr<Mechanic>> ServiceStation::getMechanics() { return mechanics; }