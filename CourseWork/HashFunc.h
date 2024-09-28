#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Hash {
public:
	static string generateSalt();
	static long long int getHash(string password, string salt);
};
