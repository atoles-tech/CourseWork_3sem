#include "Service.h"

const string Service::filename = "services.dat";

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

/*Чтение из файла + запись в файл*/
vector<shared_ptr<Service>> Service::readFile() {
	vector<shared_ptr<Service>> services;

	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> fields = ConsoleHelper::split(line);

		if (fields.size() != 4) {
			return services;
		}

		int service_id = stoi(fields[0]);
		string name = fields[1];
		double price = stod(fields[2]);
		int time = stoi(fields[3]);

		services.push_back(make_shared<Service>(service_id,name,price,time));
	}

	return services;
}

void Service::writeFile(vector<shared_ptr<Service>> services) {
	ofstream f(filename, ios::binary);

	for (shared_ptr<Service> s : services) {
		f << s->service_id << ";"
		  << s->name << ";"
		  << s->price << ";"
		  << s->time << endl;
	}
}