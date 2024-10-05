#include "Service.h"

Service::Service(int service_id, string name, double price, int time) {
	this->service_id = service_id;
	this->name = name;
	this->price = price;
	this->time = time;
}

/*Геттеры*/
int Service::getServiceId() { return service_id; }
string Service::getName() { return name; }
double Service::getPrice() { return price; }
int Service::getTime() { return time; }

/*Сеттеры*/
void Service::setServiceId(int id) { this->service_id = id; }
void Service::setName(string name) { this->name = name; }
void Service::setPrice(double price) { this->price = price; }
void Service::setTime(int time) { this->time = time; }