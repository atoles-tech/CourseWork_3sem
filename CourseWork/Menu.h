#include <iostream>
#include <algorithm>
#include "ConsoleHelper.h"
#include "User.h"
#include "HashFunc.h"
#include "Client.h"
#include "Mechanic.h"
#include "Vehicle.h"
#include "Request.h"
#include "Service.h"
#include "ServiceStation.h"
/*
1 Если удален автомобиль, который учавствует у нейкого заказа, будет удален и заказ
2 Если удален автомобиль, который учавствует у нейкого клиента, он будет удален у клиента
3 Если удалена услуга, которая учавствует в заказе, она будет удалена из заказа
4 Если удален заказ, который учавствует у клиента и/или механика, то он будет удален у клиента и/или механика
5 Если удален клиент, который учавствует в заказе, то заказ НЕ будет удален, но имя клиента в заказе будет заменено на {client_login}(del)

6 Удаление/Изменение/Добавление механиков и клиентов происходит в 1 пункте меню администратора

Админ меню (менеджер)
	1 Управление учетными записями +
		1.1 Добавить запись + 
		1.2 Изменить запись +
		1.3 Удалить запись +
		1.4 Просмотр записей +
		1.5 Изменить доступ +
		1.6 <- Обратно в меню *
	2 Управление данными
		2.1 Добавить запись +
			2.1.1 Добавить автомобиль клиенту +
			2.1.2 Добавить заказ + 
			2.1.3 Добавить услугу +
			2.1.4 <- Назад
		2.2 Изменение записей
			2.2.1 Изменить автомобиль  +
			2.2.2 Изменить заказ +
			2.2.3 Изменить услугу +
			2.2.4 <- Назад
		2.3 Удаление записей
			2.3.1 Удалить автомобиль +
			2.3.2 Удалить заказ + 
			2.3.3 Удалить услугу +
			2.3.4 <- Назад
		2.4 Просмотр записей +
			2.4.1 Просмотреть автомобиль +
			2.4.2 Просмотреть заказ +
			2.4.3 Просмотреть услугу + 
			2.4.4 Просмотреть клиентов +
			2.4.5 Просмотреть механиков +
			2.4.6 Просмотреть чек определенного заказа +
			2.4.7 <- Назад
		2.5 Сортировка записей
			2.5.1 Отсортировать автомобили +
			2.5.2 Отсортировать заказы +
			2.5.3 Отсортировать услуги +
			2.5.4 Отсортировать клиентов +
			2.5.5 Отсортировать механиков +
		2.6 Поиск записей
			2.6.1 Искать автомобили +
			2.6.2 Искать заказы + 
			2.6.3 Искать услуги +
			2.6.4 Искать клиентов +
			2.6.5 Искать механиков +
		2.7 Назначить механику заказ +
		2.8 <- Обратно в меню *
	0 Выход из аккаунта

Пользовательское меню(механик)
	1 Просмотр своих заказов
	2 Просмотр всех свободных заказов
	3 Закончить заказ
	0 Выход из аккаунта
	

Пользовательское меню (клиент)
	1 Просмотр своих заказов
	2 Добавить автомобиль
	3 Сделать заказ
	4 Просмотреть всех механиков
	5 Просмотр счета на заказ
	0 Выход из аккаунта
*/

class Menu {
public:
	static void initMenu(); //Меню авторизации
	
	/*Меню администратора*/
	static void adminMenu(string name); //Меню администратора(менеджер)
	static void adminMenuEditAccount(string name); // 1.
	static void adminMenuEditData(string name); // 2.
	static void adminMenuEditDataAdd(string name); // 2.1.
	static void adminMenuEditDataEdit(string name); // 2.2.
	static void adminMenuEditDataDelete(string name); // 2.3.
	static void adminMenuEditDataShow(string name); // 2.4
	static void adminMenuEditDataSort(string name); // 2.5
	static void adminMenuEditDataSearch(string name); // 2.6
	static void adminMenuEditDataSearchVehicle(); // 2.6.1
	static void adminMenuEditDataSearchRequest(); // 2.6.2
	static void adminMenuEditDataSearchService(); // 2.6.3
	static void adminMenuEditDataSearchMechanic(); // 2.6.4
	static void adminMenuEditDataSearchClient(); // 2.6.5

	/*Меню пользователя*/
	static void userMenu(string name); //Меню пользователя(клиент)

	/*Меню механика*/
	static void mechanicMenu(string name); //Меню механика

	static void authorize(); //Авторизация
	static void registr(int role,bool access); //Регистрация

	static shared_ptr<Client> inputClient(string name); // Ввод клиента с консоли
	static shared_ptr<Mechanic> inputMechanic(string name); // Ввод механика с консоли
	static shared_ptr<Request> inputRequest(); // Ввод заявки с консоли
	static shared_ptr<Vehicle> inputVehicle(); // Ввод автомобиля с консоли
	static shared_ptr<Service> inputService(); // Ввод услуги с консоли
	static shared_ptr<Request> inputRequestForUser(string login); // Ввод заказа для пользователя

	static User changeUser(vector<User> users, User user); // Изменение аккаунта
	static void changeVehicle(vector<shared_ptr<Vehicle>> vehicles, shared_ptr<Vehicle> vehicle); // Изменение автомобиля
	static void changeRequest(vector<shared_ptr<Request>> requests, shared_ptr<Request> req); // Изменение заказа
	static void changeService(vector<shared_ptr<Service>> services, shared_ptr<Service> ser); // Изменение услуги
};
