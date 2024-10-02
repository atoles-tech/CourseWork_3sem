#ifndef HASH_F
#define HASH_F
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Hash {
public:
	static string generateSalt();
	static long long int getHash(string password, string salt);
};

#endif HASH_F