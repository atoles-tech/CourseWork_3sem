#include "User.h"

const string User::filename = "users.dat";

User::User() {
	this->login = "-";
	this->hash = 0;
	this->isAdmin = false;
	this->salt = "AAAAAAAA";
}

User::User(string login, long long int hash, bool isAdmin, string salt) {
	this->login = login;
	this->hash = hash;
	this->isAdmin = isAdmin;
	this->salt = salt;
}

vector<User> User::readUsers() {
	vector<User> users;
	
	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> fields = ConsoleHelper::split(line);
		
		if (fields.size() != 4) {
			f.close();
			return users;
		}

		string login = fields[0];
		long long int hash = stoll(fields[1]);
		bool isAdmin = fields[2] == "1"?true:false;
		string salt = fields[3];

		users.push_back(User(login, hash, isAdmin, salt));
	}

	return users;
}

void User::writeAllUsers(vector<User> users) {
	ofstream f(filename, ios::binary);

	for (User u : users) {
		f << u.login << ";"
		  << u.hash << ";"
		  <<(u.isAdmin == true ? "1" : "0") << ";"
		  << u.salt << endl;
	}

}