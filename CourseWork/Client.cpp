#include "Client.h"

Client::Client(string login, string name, string surname, string email) {
	this->login = login;
	this->name = name;
	this->surname = surname;
	this->email = email;
}

Client::Client(string login, string name, string surname) {
	this->login = login;
	this->name = name;
	this->surname = surname;
}

void Client::addVehicle(shared_ptr<Vehicle> vehicle) {
	vehicles.push_back(vehicle);
}

/*Геттеры*/
string Client::getName() { return name; }
string Client::getSurname() { return surname; }
string Client::getEmail() { return email; }
string Client::getLogin() { return login; }
vector<shared_ptr<Vehicle>> Client::getVehicles() { return vehicles; }

/*Сеттеры*/
void Client::setEmail(string email) { this->email = email; }