#include "Client.h"

const string Client::filename = "clients.dat";

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
	this->email = "N/A";
}

void Client::addVehicle(shared_ptr<Vehicle> vehicle) {
	vehicles.push_back(vehicle);
}

void Client::addRequest(shared_ptr<Request> request) {
	requests.push_back(request);
}

/*Геттеры*/
string Client::getName() { return name; }
string Client::getSurname() { return surname; }
string Client::getEmail() { return email; }
string Client::getLogin() { return login; }
vector<shared_ptr<Vehicle>> Client::getVehicles() { return vehicles; }
vector<shared_ptr<Request>> Client::getRequests() { return requests; }

/*Сеттеры*/
void Client::setEmail(string email) { this->email = email; }

/*Чтение из файла + Запись в файл*/
vector<shared_ptr<Client>> Client::readFile(vector<shared_ptr<Request>> req, vector<shared_ptr<Vehicle>> veh) { /////
	vector<shared_ptr<Client>> clients;

	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> fields = ConsoleHelper::split(line);

		if (fields.size() != 4) {
			return clients;
		}

		string login = fields[0];
		string name = fields[1];
		string surname = fields[2];
		string email = fields[3];

		shared_ptr<Client> client = make_shared<Client>(login, name, surname, email);

		string line_2;
		getline(f, line_2);

		vector<string> fileds_2 = ConsoleHelper::split(line_2);

		for (string str : fileds_2) {
			for (shared_ptr<Request> r : req) {
				if (r->getId() == stoi(str)) {
					client->addRequest(r);
					break;
				}
			}
		}

		string line_3;
		getline(f, line_3);

		vector<string> fileds_3 = ConsoleHelper::split(line_3);

		for (string str : fileds_3) {
			for (shared_ptr<Vehicle> v : veh) {
				if (v->getNumber() == str) {
					client->addVehicle(v);
					break;
				}
			}
		}

		clients.push_back(client);
	}

	return clients;
}

void Client::writeFile(vector<shared_ptr<Client>> clients) { ////////
	ofstream f(filename, ios::binary);
	
	for (shared_ptr<Client> c : clients) {
		f << c->login << ";"
		  << c->name << ";"
		  << c->surname << ";"
		  << c->email << endl;

		for (shared_ptr<Request> r : c->getRequests()) {
			f << r->getId() << ";";
		}
		f << endl;

		for (shared_ptr<Vehicle> v : c->getVehicles()) {
			f << v->getNumber() << ";";
		}
		f << endl;
	}
}