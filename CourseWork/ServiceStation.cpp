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

/*Геттеры*/
vector<shared_ptr<Vehicle>> ServiceStation::getVehicles() {return vehicles;}
vector<shared_ptr<Client>> ServiceStation::getClients() {return clients;}
vector<shared_ptr<Service>> ServiceStation::getServices() { return services; }
vector<shared_ptr<Request>> ServiceStation::getRequests() { return requests; }