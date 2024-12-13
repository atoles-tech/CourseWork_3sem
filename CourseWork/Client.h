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

	vector<shared_ptr<Vehicle>> vehicles; // Список автомобилей клиента
	vector<shared_ptr<Request>> requests; // Список заказов клиента
public:
	Client(string login, string name, string surname, string email);

	void addVehicle(shared_ptr<Vehicle> vehicle); // Добавить автомобиль
	void addRequest(shared_ptr<Request> request); // Добавить заказ
	void delVehicle(int index); // Удалить автомобиль
	void delRequest(int index); // Удалить заказ

	/*Геттеры*/
	vector<shared_ptr<Vehicle>>& getVehicles();
	vector<shared_ptr<Request>>& getRequests();

	void showInfo() override; // Показать информацию о клиенте

	/*Чтение из файла + Запись в файл*/
	static vector<shared_ptr<Client>> readFile(vector<shared_ptr<Request>> req, vector<shared_ptr<Vehicle>> veh);
	static void writeFile(vector<shared_ptr<Client>> clients);
	static void writeOneFile(shared_ptr<Client> c);
	
	static void showClient(vector<shared_ptr<Client>> clients); // Показать список клиентов
};

#endif // !CLIENT_H

