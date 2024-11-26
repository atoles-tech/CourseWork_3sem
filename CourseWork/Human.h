#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>

using namespace std;

class Human {
protected:
	string login;
	string name;
	string surname;
	string email;
public:
	Human(string login, string name, string surname, string email);

	/*Геттеры*/
	string getName();
	string getSurname();
	string getEmail();
	string getLogin();

	/*Сеттеры*/
	void setEmail(string email);
	void setLogin(string login);
	void setName(string name);
	void setSurname(string surname);

	virtual void showInfo() = 0;

};

#endif // !PEOPLE_H
