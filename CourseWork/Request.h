#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <memory>
#include "Client.h"
#include "Vehicle.h"
#include "Service.h"
#include "Bill.h"

using namespace std;

class Request {
private:

	int id;
	shared_ptr<Client> client;
	shared_ptr<Vehicle> vehicle;
	Bill bill;
	vector<shared_ptr<Service>> services;
public:
	Request(shared_ptr<Client> client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services);

	/*Геттеры*/
	int getId();
	shared_ptr<Client> getClient();
	shared_ptr<Vehicle> getVehicle();
	Bill getBill();
	vector<shared_ptr<Service>> getServices();
};

#endif // !REQUEST_H
