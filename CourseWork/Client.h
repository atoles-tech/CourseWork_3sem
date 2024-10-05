#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Vehicle.h"

using namespace std;

class Client {
private:
	string login;

	string name;
	string surname;
	string email;
	vector<shared_ptr<Vehicle>> vehicles;
public:
	Client(string login, string name, string surname, string email);
	Client(string login, string name, string surname);

	void addVehicle(shared_ptr<Vehicle> vehicle);

	/*�������*/
	string getName();
	string getSurname();
	string getEmail();
	string getLogin();
	vector<shared_ptr<Vehicle>> getVehicles();

	/*�������*/
	void setEmail(string email);
};

#endif // !CLIENT_H

