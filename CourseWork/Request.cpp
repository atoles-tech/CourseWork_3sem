#include "Request.h"

Request::Request(shared_ptr<Client> client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services) {
	this->client = client;
	this->vehicle = vehicle;
	this->services = services;
	
	int sum = 0;
	for (auto& s : services) {
		sum += s->getPrice();
	}

	bill = Bill(sum, false);
}

/*Геттеры*/
int Request::getId() { return id; }
shared_ptr<Client> Request::getClient() { return client; }
shared_ptr<Vehicle> Request::getVehicle() { return vehicle; }
Bill Request::getBill() { return bill; }
vector<shared_ptr<Service>> Request::getServices() { return services; }