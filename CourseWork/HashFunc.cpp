#include "HashFunc.h"

string Hash::generateSalt() {
	string salt = "";
	for (int i = 0; i < 8;i++) {
		char ch = (char)(rand() % 25 + 65);

		salt += ch;
	}
	return salt;
}

long long int Hash::getHash(string password, string salt) {
	long long int hash = 0;
	for (char c : password) {
		if (c == -52) { break; }
		hash += (int)c << 8;
		hash += salt[(int)c % 8] << 8;
	}
	return hash;
}