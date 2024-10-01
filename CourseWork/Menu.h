#include <iostream>
#include "ConsoleHelper.h"

class Menu {
public:
	static void initMenu(); //Меню авторизации
	static void adminMenu(); //Меню администратора(менеджера/управляющего)
	static void userMenu(); //Меню пользователя(механика)
	static void authorize(); //Авторизация
	static void registr(); //Регистрация
};
