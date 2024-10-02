#include <iostream>
#include "ConsoleHelper.h"
#include "User.h"
#include "HashFunc.h"

class Menu {
public:
	static void initMenu(); //Меню авторизации
	static void adminMenu(string name); //Меню администратора(менеджера/управляющего)
	static void userMenu(string name); //Меню пользователя(механика)
	static void authorize(); //Авторизация
	static void registr(); //Регистрация
};
