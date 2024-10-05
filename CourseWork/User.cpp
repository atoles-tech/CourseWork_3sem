#include "User.h"

const string User::filename = "users.dat";

User::User() {
	this->login = "-";
	this->hash = 0;
	this->isAdmin = false;
	this->salt = "AAAAAAAA";
	this->isAccess = false;
}

User::User(string login, long long int hash, bool isAdmin, string salt, bool isAccess) {
	this->login = login;
	this->hash = hash;
	this->isAdmin = isAdmin;
	this->salt = salt;
	this->isAccess = isAccess;
}

User User::getUser(vector<User> users,string login) {
	User user;

	for (User u : users) {
		if (u.login == login) { return u; }
	}

	return user;
}

vector<User> User::readUsers() {
	vector<User> users;
	
	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> fields = ConsoleHelper::split(line);
		
		if (fields.size() != 5) {
			return users;
		}

		string login = fields[0];
		long long int hash = stoll(fields[1]);
		bool isAdmin = fields[2] == "1"?true:false;
		string salt = fields[3];
		bool isAccess = fields[4] == "1" ? true : false;

		users.push_back(User(login, hash, isAdmin, salt, isAccess));
	}

	return users;
}

void User::writeAllUsers(vector<User> users) {
	ofstream f(filename, ios::binary);

	for (User u : users) {
		f   << u.login << ";"
			<< u.hash << ";"
			<<(u.isAdmin == true ? "1" : "0") << ";"
			<< u.salt << ";"
			<<(u.isAccess == true ? "1" : "0") << ";" << endl;
	}

}

void User::writeUser(User u) {
	ofstream f(filename, ios::binary | ios::app);

	f   << u.login << ";"
		<< u.hash << ";"
		<<(u.isAdmin == true ? "1" : "0") << ";"
		<< u.salt << ";"
		<<(u.isAccess == true ? "1" : "0") << ";" << endl;
}


string User::getLogin() { return login; }
string User::getSalt() { return salt; }
long long int User::getHash() { return hash; }
bool User::getRole() { return isAdmin; }
bool User::getAccess() { return isAccess; }