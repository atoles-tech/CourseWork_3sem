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

	int id; // ID заказа
	string client; // Логин клиента
	string mechanic; // Логин механика
	shared_ptr<Vehicle> vehicle; // Авто на обслуживании
	Bill bill; // Счет
	vector<shared_ptr<Service>> services; // Список услуг
	int status; // 0 - ожидает | 1 - ремонтируется | 2 - отремантирован

	/*Дата создания заказа*/
	int day; 
	int month;
	int year;

public:
	Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status, bool statusBill);
	Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status, bool statusBill,int day,int month, int year);
	Request();

	void delService(int index); // Удалить услугу
	void addService(shared_ptr<Service> s); // Добавить услугу

	/*Геттеры*/
	int getId();
	int getStatus();
	string getClient();
	string getMechanic();
	shared_ptr<Vehicle> getVehicle();
	Bill& getBill();
	vector<shared_ptr<Service>> getServices();
	int getDay();
	int getMonth();
	int getYear();

	/*Сеттеры*/
	void setStatus(int status);
	void setMechanic(string mechanic);
	void setClient(string client);
	void setId(int id);

	/*Чтение из файла + запись в файл*/
	static vector<shared_ptr<Request>> readFile(vector<shared_ptr<Vehicle>> vehicles, vector<shared_ptr<Service>> services);
	static void writeFile(vector<shared_ptr<Request>> requests);
	static void writeOneFile(shared_ptr<Request> r);

	static void showRequest(vector<shared_ptr<Request>> requests); // Показать заказы
};

#endif // !REQUEST_H
