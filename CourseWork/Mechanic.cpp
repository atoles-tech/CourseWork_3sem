#include "Mechanic.h"

const string Mechanic::filename = "mechanics.dat";

Mechanic::Mechanic(string login, string name, string surname, string email) : Human(login,name,surname,email) {
	isBusy = false;
}

void Mechanic::addRequest(shared_ptr<Request> request) {
	requests.push_back(request);
}
void Mechanic::delRequest(int index) {
	requests.erase(requests.begin() + index);
}

/*�������*/
bool Mechanic::getStatus() { return isBusy; }
vector<shared_ptr<Request>>& Mechanic::getRequests() { return requests; }

/*�������*/
void Mechanic::setStatus(bool status) { this->isBusy = status; }

void Mechanic::showInfo(){
	cout << "�����: " << this->getLogin() << endl;
	cout << "���: " << this->getName() << endl;
	cout << "�������: " << this->getSurname() << endl;
	cout << "Email: " << this->getEmail() << endl;
	cout << "������: " << (this->getStatus() == true ? "�����" : "��������") << endl << endl;

	cout << "������: " << endl;
	Request::showRequest(this->getRequests());
}

/*������ �� ����� + ������ � ����*/
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
	bool isBusy; // true - ����� --- false - �� �����

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

void Mechanic::writeOneFile(shared_ptr<Mechanic> mech) {
	ofstream f(filename, ios::binary | std::ios::app);

	f << mech->login << ";"
		<< mech->name << ";"
		<< mech->surname << ";"
		<< mech->email << ";"
		<< (mech->isBusy == true ? "1" : "0") << endl;

	for (shared_ptr<Request> r : mech->getRequests()) {
		f << r->getId() << ";";
	}
	f << endl;
}

void Mechanic::showMechanic(vector<shared_ptr<Mechanic>> mechanics) {
	if (mechanics.size() == 0) {
		cout << "��������� ���" << endl;
		return;
	}

	cout << setw(7) << "�����" << "|"
		<< setw(15) << "�����" << "|"
		<< setw(20) << "���" << "|"
		<< setw(20) << "�������" << "|" << endl;

	cout << string(66, '=') << endl;

	int i = 1;
	for (shared_ptr<Mechanic> m : mechanics) {
		cout << setw(7) << i++ << "|"
			<< setw(15) << m->getLogin() << "|"
			<< setw(20) << m->getName() << "|"
			<< setw(20) << m->getSurname() << "|" << endl;
	}
}
