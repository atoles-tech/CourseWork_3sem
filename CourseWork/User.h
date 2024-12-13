#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "ConsoleHelper.h"
#include "HashFunc.h"

#ifndef USER_
#define USER_

using namespace std;

class User { // login hash 1/0 salt access
private:
	const static string filename;

	string login; // Логин пользователя
	long long int hash; // Хэш пароля
	int isAdmin;// Роль ||| 0 - клиент, 1 - механик, 2 - админ
	string salt; // Соль
	bool isAccess; // Доступ к системе
public:
	User();
	User(string login, long long int hash, int isAdmin, string salt, bool isAccess);
	static User getUser(vector<User> users, string login);
	static vector<User> readUsers(); // Считать пользователя из файла
	static void writeAllUsers(vector<User> users); // Записать пользователей в файл
	static void writeUser(User u); // Записать одного пользователя в файл
	static vector<User> showUsers(); // Показать пользователей (также возвращает список всех пользователей)
public:
	static void checkFile(); // Проверить фалй с аккаунтами

	/*Геттеры*/
	string getLogin();
	string getSalt();
	long long int getHash();
	int getRole();
	bool getAccess();

	/*Сеттеры*/
	void setLogin(string login);
	void setSalt(string salt);
	void setHash(long long int hash);
	void setRole(int role);
	void setAccess(bool access);
};

#endif USER_