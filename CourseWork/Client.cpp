#include "Client.h"

const string Client::filename = "clients.dat";

Client::Client(string login, string name, string surname, string email) : Human(login, name, surname, email) {}

void Client::addVehicle(shared_ptr<Vehicle> vehicle) {
	vehicles.push_back(vehicle);
}

void Client::addRequest(shared_ptr<Request> request) {
	requests.push_back(request);
}

void Client::delVehicle(int index) { vehicles.erase(vehicles.begin() + index); }
void Client::delRequest(int index) { requests.erase(requests.begin() + index); }

/*Геттеры*/
vector<shared_ptr<Vehicle>> Client::getVehicles() { return vehicles; }
vector<shared_ptr<Request>> Client::getRequests() { return requests; }


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

void Client::writeFile(vector<shared_ptr<Client>> clients) {
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

void Client::writeOneFile(shared_ptr<Client> c) {
	ofstream f(filename, ios::binary | std::ios::app);

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

void Client::showClient(vector<shared_ptr<Client>> clients) {
	if (clients.size() == 0) {
		cout << "Клиентов нет!" << endl;
		return;
	}

	cout << setw(7) << "Номер" << "|"
		<< setw(15) << "Логин" << "|"
		<< setw(20) << "Имя" << "|"
		<< setw(20) << "Фамилия" << "|" << endl;

	cout << string(66, '=') << endl;

	int i = 1;
	for (shared_ptr<Client> c : clients) {
		cout << setw(7) << i++ << "|"
			<< setw(15) << c->getLogin() << "|"
			<< setw(20) << c->getName() << "|"
			<< setw(20) << c->getSurname() << "|" << endl;
	}
}
