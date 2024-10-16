#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "Request.h"

using namespace std;

class Request;

class Client {
private:
	const static string filename;

	string login;

	string name;
	string surname;
	string email;
	vector<shared_ptr<Vehicle>> vehicles;
	vector<shared_ptr<Request>> requests;
public:
	Client(string login, string name, string surname, string email);

	void addVehicle(shared_ptr<Vehicle> vehicle);
	void addRequest(shared_ptr<Request> request);

	/*�������*/
	string getName();
	string getSurname();
	string getEmail();
	string getLogin();
	vector<shared_ptr<Vehicle>> getVehicles();
	vector<shared_ptr<Request>> getRequests();

	/*�������*/
	void setEmail(string email);
	void setLogin(string login);
	void setName(string name);
	void setSurname(string surname);

	/*������ �� ����� + ������ � ����*/
	static vector<shared_ptr<Client>> readFile(vector<shared_ptr<Request>> req, vector<shared_ptr<Vehicle>> veh);
	static void writeFile(vector<shared_ptr<Client>> clients);
	static void writeOneFile(shared_ptr<Client> c);
};

#endif // !CLIENT_H

