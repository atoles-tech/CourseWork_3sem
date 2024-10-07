#include "Mechanic.h"

const string Mechanic::filename = "mechanics.dat";

Mechanic::Mechanic(string login, string name, string surname, string email) {
	this->login = login;
	this->name = name;
	this->surname = surname;
	this->email = email;
	isBusy = false;
}

void Mechanic::addRequest(shared_ptr<Request> request) {
	requests.push_back(request);
}

/*Геттеры*/
string Mechanic::getLogin() { return login; }
string Mechanic::getName() { return name; }
string Mechanic::getSurname() { return surname; }
string Mechanic::getEmail() { return email; }
bool Mechanic::getStatus() { return isBusy; }
vector<shared_ptr<Request>> Mechanic::getRequests() { return requests; }

/*Сеттеры*/
void Mechanic::setStatus(bool status) { this->isBusy = status; }

/*Чтение из файла + Запись в файл*/
vector<shared_ptr<Mechanic>> Mechanic::readFile(vector<shared_ptr<Request>> req) {
	vector<shared_ptr<Mechanic>> mechanics;

	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);

		vector<string> strings = ConsoleHelper::split(line);

		if (strings.size() != 5) { return mechanics; }

		string login = strings[0];
		string name = strings[1];
		string surname = strings[2];
		string email = strings[3];
		bool isBusy = strings[4] == "1"?true:false;

		shared_ptr<Mechanic> mech = make_shared<Mechanic>(login, name, surname, email);
		mech->setStatus(isBusy);

		string line_2;
		getline(f, line_2);

		vector<string> strings_2 = ConsoleHelper::split(line_2);

		for (string str : strings_2) {
			for (shared_ptr<Request> r : req) {
				if (r->getId() == stoi(str)) {
					mech->addRequest(r);
					break;
				}
			}
		}

		mechanics.push_back(mech);
	}

	return mechanics;
}

void Mechanic::writeFile(vector<shared_ptr<Mechanic>> mechanics) {
	ofstream f(filename, ios::binary);

	string login;

	string name;
	string surname;
	string email;
	bool isBusy; // true - занят --- false - не занят

	for (shared_ptr<Mechanic> m: mechanics) {
		f << m->login << ";"
		  << m->name << ";"
		  << m->surname << ";"
		  << m->email << ";"
		  << (m->isBusy == true?"1":"0") << endl;

		for (shared_ptr<Request> r : m->getRequests()) {
			f << r->getId() << ";";
		}
		f << endl;
	}
}