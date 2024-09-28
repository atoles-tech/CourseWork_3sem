#include <iostream>

using namespace std;

class User {
private:
	const static string filename;

	string login;
	long int hash;
	bool isAdmin;
	string salt;
public:
	User();
};

const string User::filename = "users.txt";