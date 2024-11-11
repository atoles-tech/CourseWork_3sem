#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "Request.h"
#include "Human.h"

using namespace std;

class Request;

class Client : public Human {
private:
	const static string filename;

	vector<shared_ptr<Vehicle>> vehicles;
	vector<shared_ptr<Request>> requests;
public:
	Client(string login, string name, string surname, string email);

	void addVehicle(shared_ptr<Vehicle> vehicle);
	void addRequest(shared_ptr<Request> request);
	void delVehicle(int index);
	void delRequest(int index);

	/*Геттеры*/
	vector<shared_ptr<Vehicle>> getVehicles();
	vector<shared_ptr<Request>> getRequests();

	/*Чтение из файла + Запись в файл*/
	static vector<shared_ptr<Client>> readFile(vector<shared_ptr<Request>> req, vector<shared_ptr<Vehicle>> veh);
	static void writeFile(vector<shared_ptr<Client>> clients);
	static void writeOneFile(shared_ptr<Client> c);
	
	static void showClient(vector<shared_ptr<Client>> clients);
};

#endif // !CLIENT_H

