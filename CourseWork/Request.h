#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "Client.h"
#include "Mechanic.h"
#include "Vehicle.h"
#include "Service.h"
#include "Bill.h"

using namespace std;

class Mechanic;
class Client;

class Request {
private:
	const static string filename;

	int id;
	string client;
	string mechanic;
	shared_ptr<Vehicle> vehicle;
	Bill bill;
	vector<shared_ptr<Service>> services;
	int status; // 0 - ожидает | 1 - ремонтируется | 2 - отремантирован
public:
	Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status);
	Request();

	void delService(int index);
	void addService(shared_ptr<Service> s);

	/*Геттеры*/
	int getId();
	int getStatus();
	string getClient();
	string getMechanic();
	shared_ptr<Vehicle> getVehicle();
	Bill getBill();
	vector<shared_ptr<Service>> getServices();

	/*Сеттеры*/
	void setStatus(int status);
	void setMechanic(string mechanic);
	void setClient(string client);
	void setId(int id);

	/*Чтение из файла + запись в файл*/
	static vector<shared_ptr<Request>> readFile(vector<shared_ptr<Vehicle>> vehicles, vector<shared_ptr<Service>> services);
	static void writeFile(vector<shared_ptr<Request>> requests);
	static void writeOneFile(shared_ptr<Request> r);

	static void showRequest(vector<shared_ptr<Request>> requests);
};

#endif // !REQUEST_H
