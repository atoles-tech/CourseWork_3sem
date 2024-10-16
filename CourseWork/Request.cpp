#include "Request.h"

const string Request::filename = "requests.dat";

Request::Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status) {
	this->id = id;
	this->client = client;
	this->mechanic = "N/A";
	this->vehicle = vehicle;
	this->services = services;
	this->status = status;

	int sum = 0;
	for (auto& s : services) {
		sum += s->getPrice();
	}

	bill = Bill(sum, false);
}

/*Геттеры*/
int Request::getId() { return id; }
string Request::getClient() { return client; }
shared_ptr<Vehicle> Request::getVehicle() { return vehicle; }
Bill Request::getBill() { return bill; }
vector<shared_ptr<Service>> Request::getServices() { return services; }

/*Сеттеры*/
void Request::setStatus(int status) {this->status = status;}
void Request::setMechanic(string mechanic) { this->mechanic = mechanic; }
void Request::setClient(string client) { this->client = client; }
void Request::setId(int id) { this->id = id; }

/*Чтение из файла + запись в файл*/
vector<shared_ptr<Request>> Request::readFile(vector<shared_ptr<Vehicle>> vehicles, vector<shared_ptr<Service>> services) {
	ifstream f(filename, ios::binary);

	vector<shared_ptr<Request>> requests;

	while (!f.eof()) {
		string line; 
		getline(f, line);

		vector<string> strings = ConsoleHelper::split(line);

		if (strings.size() != 5) { return requests; }

		int id = stoi(strings[0]);
		string client = strings[1];
		string mechanic = strings[2];
		shared_ptr<Vehicle> vehicle;
		int status = stoi(strings[4]);

		for (shared_ptr<Vehicle> v : vehicles) {
			if (v->getNumber() == strings[3]) {
				vehicle = v;
				break;
			}
		}

		string line_2;
		getline(f, line_2);

		vector<string> strings_2 = ConsoleHelper::split(line_2);

		vector<shared_ptr<Service>> serv;

		for (string service_id_str : strings_2) {
			for (shared_ptr<Service> s : services) {
				if (s->getServiceId() == stoi(service_id_str)) {
					serv.push_back(s);
					break;
				}
			}
		}

		shared_ptr<Request> request = make_shared<Request>(id, client, vehicle, serv, status);
		requests.push_back(request);
	}

	return requests;
}

void Request::writeFile(vector<shared_ptr<Request>> requests) {
	ofstream f(filename, ios::binary);

	for (shared_ptr<Request> r : requests) {
		f << r->id << ";"
		  << r->client << ";"
		  << r->mechanic << ";"
		  << r->vehicle->getNumber() << ";"
		  << r->status << endl;

		for (shared_ptr<Service> s : r->services) {
			f << s->getServiceId() << ";";
		}

		f << endl;
	}
}