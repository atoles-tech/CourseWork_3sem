#include "Request.h"

const string Request::filename = "requests.dat";

Request::Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status,bool statusBill) {
	this->id = id;
	this->client = client;
	this->mechanic = "N/A";
	this->vehicle = vehicle;
	this->services = services;
	this->status = status;

	double sum = 0;
	for (auto& s : services) {
		sum += s->getPrice();
	}

	bill = Bill(sum, statusBill);

	time_t now;
	time(&now);
	struct tm local;
	localtime_s(&local, &now);
	this->day = local.tm_mday;
	this->month = local.tm_mon + 1;
	this->year = local.tm_year + 1900;
}

Request::Request(int id, string client, shared_ptr<Vehicle> vehicle, vector<shared_ptr<Service>> services, int status, bool statusBill, int day, int month, int year) {
	this->id = id;
	this->client = client;
	this->mechanic = "N/A";
	this->vehicle = vehicle;
	this->services = services;
	this->status = status;

	double sum = 0;
	for (auto& s : services) {
		sum += s->getPrice();
	}

	bill = Bill(sum, statusBill);

	this->day = day;
	this->month = month;
	this->year = year;
}

Request::Request() {
	this->id = -1;
	this->client = "N/A";
	this->mechanic = "N/A";
	this->status = -1;
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

void Request::delService(int index) { 
	services.erase(index + services.begin()); 
	double sum = 0;
	for (auto& s : services) {
		sum += s->getPrice();
	}

	this->bill = Bill(sum, bill.getStatus());

	bill = Bill(sum, status);
}

void Request::addService(shared_ptr<Service> s) {
	services.push_back(s);
}

/*Геттеры*/
int Request::getId() { return id; }
int Request::getStatus() { return status; }
string Request::getClient() { return client; }
string Request::getMechanic() { return mechanic; }
shared_ptr<Vehicle> Request::getVehicle() { return vehicle; }
Bill& Request::getBill() { return bill; }
vector<shared_ptr<Service>> Request::getServices() { return services; }
int Request::getDay() { return day; }
int Request::getMonth() { return month; }
int Request::getYear() { return year; }

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
		cout << strings.size() << endl;
		
		if (strings.size() != 9) { return requests; }

		int id = stoi(strings[0]);
		string client = strings[1];
		string mechanic = strings[2];
		shared_ptr<Vehicle> vehicle;
		int status = stoi(strings[4]);
		bool statusBill = stoi(strings[5]);
		int day = stoi(strings[6]);
		int month = stoi(strings[7]);
		int year = stoi(strings[8]);

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

		shared_ptr<Request> request = make_shared<Request>(id, client, vehicle, serv, status,statusBill,day,month,year);
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
		  << r->status << ";"
		  << r->bill.getStatus() << ";"
		  << r->day << ";"
		  << r->month << ";"
		  << r->year << endl;

		for (shared_ptr<Service> s : r->services) {
			f << s->getServiceId() << ";";
		}

		f << endl;
	}
}

void Request::writeOneFile(shared_ptr<Request> r) {
	ofstream f(filename, ios::binary | std::ios::app);
	
	f   << r->id << ";"
		<< r->client << ";"
		<< r->mechanic << ";"
		<< r->vehicle->getNumber() << ";"
		<< r->status << ";"
		<< r->bill.getStatus() << ";"
		<< r->day << ";"
		<< r->month << ";"
		<< r->year << endl;

	for (shared_ptr<Service> s : r->services) {
		f << s->getServiceId() << ";";
	}

	f << endl;
	
}

void Request::showRequest(vector<shared_ptr<Request>> requests) {
	if (requests.size() == 0) {
		cout << "Заказов нет!" << endl;
		return;
	}

	cout << setw(7) << "Номер" << "|"
		<< setw(15) << "Клиент" << "|"
		<< setw(15) << "Механик" << "|"
		<< setw(15) << "Номер авто" << "|"
		<< setw(10) << "Стоимость" << "|" 
		<< setw(20) << "Статус" << "|" 
		<< setw(20) << "Статус оплаты" << "|" 
		<< setw(12) << "Дата заказа" << endl;

	cout << string(122, '=') << endl;

	int i = 1;
	for (shared_ptr<Request> r : requests) {
		cout << setw(7) << i++ << "|"
			<< setw(15) << r->getClient() << "|"
			<< setw(15) << r->getMechanic() << "|"
			<< setw(15) << r->getVehicle()->getNumber() << "|"
			<< setw(10) << r->getBill().getSum() << "|"
			<< setw(20) << (r->getStatus() == 0 ? "Ожидает" : (r->getStatus() == 1 ? "Ремонтируется" : "Отремонтирован")) << "|" 
			<< setw(20) << (r->getBill().getStatus() == true?"Оплачен":"Ожидает оплаты") << "|"
			<< r->day << '.' << r->month << "." << r->year << endl;
	}
}
