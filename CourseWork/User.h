#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ConsoleHelper.h"

using namespace std;

class User { // login hash 1||0 salt
private:
	const static string filename;

	string login;
	long long int hash;
	bool isAdmin;
	string salt;
public:
	User();
	User(string login, long long int hash, bool isAdmin, string salt);
	static vector<User> readUsers();
	static void writeAllUsers(vector<User> users);
public:
	string getLogin() { return login; }
};

