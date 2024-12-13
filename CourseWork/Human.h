#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <string>

using namespace std;

class Human {
protected:
	string login; // Логин аккаунта
	string name; // Имя пользователя
	string surname; // Фамилия пользователя
	string email; // Электронная почта
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

	virtual void showInfo() = 0; // Показать информации о человеке

};

#endif // !PEOPLE_H
