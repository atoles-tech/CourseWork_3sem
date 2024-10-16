#ifndef MECHANIC_H
#define MECHANIC_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Request.h"

using namespace std;

class Request;

class Mechanic {
private:
	const static string filename;

	string login;

	string name;
	string surname;
	string email;
	bool isBusy; // true - ����� --- false - �� �����
	vector<shared_ptr<Request>> requests;
public:
	Mechanic(string login, string name, string surname, string email);

	void addRequest(shared_ptr<Request> request);

	/*�������*/
	string getLogin();
	string getName();
	string getSurname();
	string getEmail();
	bool getStatus();
	vector<shared_ptr<Request>> getRequests();

	/*�������*/
	void setStatus(bool status);
	void setLogin(string login);
	void setName(string name);
	void setSurname(string surname);
	void setEmail(string email);

	/*������ �� ����� + ������ � ����*/
	static vector<shared_ptr<Mechanic>> readFile(vector<shared_ptr<Request>> req);
	static void writeFile(vector<shared_ptr<Mechanic>> mechanics);
	static void writeOneFile(shared_ptr<Mechanic> mech);
};

#endif