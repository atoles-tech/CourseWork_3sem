#include "Human.h"

Human::Human(string login, string name, string surname, string email) {
	this->login = login;
	this->name = name;
	this->surname = surname;
	this->email = email;
}

/*Геттеры*/
string Human::getName() { return name; }
string Human::getSurname() { return surname; }
string Human::getEmail() { return email; }
string Human::getLogin() { return login; }

/*Сеттеры*/
void Human::setEmail(string email) { this->email = email; }
void Human::setLogin(string login) { this->login = login; }
void Human::setName(string name) { this->name = name; }
void Human::setSurname(string surname) { this->surname = surname; }
