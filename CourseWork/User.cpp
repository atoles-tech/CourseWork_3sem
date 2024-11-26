#include "User.h"

const string User::filename = "users.dat";

User::User() {
	this->login = "-";
	this->hash = 0;
	this->isAdmin = false;
	this->salt = "AAAAAAAA";
	this->isAccess = false;
}

User::User(string login, long long int hash, int isAdmin, string salt, bool isAccess) {
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
		int isAdmin = stoi(fields[2]);
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
			<< u.isAdmin << ";"
			<< u.salt << ";"
			<<(u.isAccess == true ? "1" : "0") << ";" << endl;
	}

}

void User::writeUser(User u) {
	ofstream f(filename, ios::binary | ios::app);

	f   << u.login << ";"
		<< u.hash << ";"
		<< u.isAdmin << ";"
		<< u.salt << ";"
		<<(u.isAccess == true ? "1" : "0") << ";" << endl;
}

vector<User> User::showUsers() {
	vector<User> users = readUsers();

	cout << setw(7) << "Номер" << "|"
		<< setw(15) << "Логин" << "|"
		<< setw(10) << "Роль" << "|"
		<< setw(20) << "Доступ" << "|" << endl;

	cout << string(56,'=') << endl;

	int i = 1;
	for (User u : users) {
		cout << setw(7) << i++ << "|"
			 << setw(15) << u.login << "|"
			 << setw(10) << (u.isAdmin == 0 ? "Клиент" : (u.isAdmin == 1 ? "Механик" : "Админ")) << "|"
			 << setw(20) << (u.isAccess == true ? "Доступ разрешен" : "Доступ запрещен") << "|" <<  endl;
	}

	return users;
}


void User::checkFile() {
	ifstream f(filename, ios::binary | ios::app);
	if (f.eof()) {
		string salt = Hash::generateSalt();
		User user = User("admin", Hash::getHash("admin", salt), 2, salt, 1);
		User::writeUser(user);
	}
}


/*Геттеры*/
string User::getLogin() { return login; }
string User::getSalt() { return salt; }
long long int User::getHash() { return hash; }
int User::getRole() { return isAdmin; }
bool User::getAccess() { return isAccess; }

/**/
void User::setLogin(string login) { this->login = login; }
void User::setSalt(string salt) { this->salt = salt; }
void User::setHash(long long int hash) { this->hash = hash; }
void User::setRole(int role) { this->isAdmin = role; }
void User::setAccess(bool access) { this->isAccess = access; }