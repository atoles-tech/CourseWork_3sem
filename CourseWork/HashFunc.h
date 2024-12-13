#ifndef HASH_F
#define HASH_F
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Hash {
public:
	static string generateSalt(); // Сгенерировать случайную соль из 8 символов
	static long long int getHash(string password, string salt); // Получить хэш
};

#endif HASH_F