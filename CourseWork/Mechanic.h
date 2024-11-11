#ifndef MECHANIC_H
#define MECHANIC_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Request.h"
#include "Human.h"

using namespace std;

class Request;

class Mechanic : public Human{
private:
	const static string filename;

	bool isBusy; // true - занят --- false - не занят
	vector<shared_ptr<Request>> requests;
public:
	Mechanic(string login, string name, string surname, string email);

	void addRequest(shared_ptr<Request> request);
	void delRequest(int index);

	/*Геттеры*/
	bool getStatus();
	vector<shared_ptr<Request>> getRequests();

	/*Сеттеры*/
	void setStatus(bool status);

	/*Чтение из файла + Запись в файл*/
	static vector<shared_ptr<Mechanic>> readFile(vector<shared_ptr<Request>> req);
	static void writeFile(vector<shared_ptr<Mechanic>> mechanics);
	static void writeOneFile(shared_ptr<Mechanic> mech);

	static void showMechanic(vector<shared_ptr<Mechanic>> mechanics);
};

#endif