#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ConsoleHelper.h"

#ifndef USER_
#define USER_
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
	static User getUser(vector<User> users, string login);
	static vector<User> readUsers();
	static void writeAllUsers(vector<User> users);
public:
	string getLogin() { return login; }
	string getSalt() { return salt; }
	long long int getHash() { return hash; }
	bool getRole() { return isAdmin; }
};

#endif USER_