#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ConsoleHelper.h"

#ifndef USER_
#define USER_

using namespace std;

class User { // login hash 1/0 salt access
private:
	const static string filename;

	string login;
	long long int hash;
	int isAdmin;// 0 - пользователь, 1 - механик, 2 - админ
	string salt;
	bool isAccess;
public:
	User();
	User(string login, long long int hash, int isAdmin, string salt, bool isAccess);
	static User getUser(vector<User> users, string login);
	static vector<User> readUsers();
	static void writeAllUsers(vector<User> users);
	static void writeUser(User u);
public:
	string getLogin();
	string getSalt();
	long long int getHash();
	int getRole();
	bool getAccess();
};

#endif USER_