#ifndef SERVICESTATIO_H
#define SERVICESTATIO_H

#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "Vehicle.h"
#include "Client.h"
#include "Service.h"
#include "Request.h"

using namespace std;

class ServiceStation {
private:
	static ServiceStation service;
	
	vector<shared_ptr<Vehicle>> vehicles;
	vector<shared_ptr<Client>> clients;
	vector<shared_ptr<Mechanic>> mechanics;
	vector<shared_ptr<Service>> services;
	vector<shared_ptr<Request>> requests;
public:
	static ServiceStation& getInstance();
	
	void addVehicle(shared_ptr<Vehicle> v);
	void addClient(shared_ptr<Client> c);
	void addService(shared_ptr<Service> s);
	void addRequest(shared_ptr<Request> r);
	void addMechanic(shared_ptr<Mechanic> m);

	/*Вывод на экран*/
	void showClient();
	void showVehicle();
	void showMechanic();
	void showService();
	void showRequest();

	/*Инициализация*/
	void init();

	/*Сохранение*/
	void saveAllData();

	/*Проверка*/
	bool hasClient(string login);
	bool hasMechanic(string login);

	/*Геттеры*/
	vector<shared_ptr<Vehicle>> getVehicles();
	vector<shared_ptr<Client>> getClients();
	vector<shared_ptr<Service>> getServices();
	vector<shared_ptr<Request>> getRequests();
	vector<shared_ptr<Mechanic>> getMechanics();
private:
	ServiceStation() {}
};

#endif 
