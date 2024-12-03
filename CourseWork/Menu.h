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
1 ���� ������ ����������, ������� ���������� � ������� ������, ����� ������ � �����
2 ���� ������ ����������, ������� ���������� � ������� �������, �� ����� ������ � �������
3 ���� ������� ������, ������� ���������� � ������, ��� ����� ������� �� ������
4 ���� ������ �����, ������� ���������� � ������� �/��� ��������, �� �� ����� ������ � ������� �/��� ��������
5 ���� ������ ������, ������� ���������� � ������, �� ����� �� ����� ������, �� ��� ������� � ������ ����� �������� �� {client_login}(del)

6 ��������/���������/���������� ��������� � �������� ���������� � 1 ������ ���� ��������������

����� ���� (��������)
	1 ���������� �������� �������� +
		1.1 �������� ������ + 
		1.2 �������� ������ +
		1.3 ������� ������ +
		1.4 �������� ������� +
		1.5 �������� ������ +
		1.6 <- ������� � ���� *
	2 ���������� �������
		2.1 �������� ������ +
			2.1.1 �������� ���������� ������� +
			2.1.2 �������� ����� + 
			2.1.3 �������� ������ +
			2.1.4 <- �����
		2.2 ��������� �������
			2.2.1 �������� ����������  +
			2.2.2 �������� ����� +
			2.2.3 �������� ������ +
			2.2.4 <- �����
		2.3 �������� �������
			2.3.1 ������� ���������� +
			2.3.2 ������� ����� + 
			2.3.3 ������� ������ +
			2.3.4 <- �����
		2.4 �������� ������� +
			2.4.1 ����������� ���������� +
			2.4.2 ����������� ����� +
			2.4.3 ����������� ������ + 
			2.4.4 ����������� �������� +
			2.4.5 ����������� ��������� +
			2.4.6 ����������� ��� ������������� ������ +
			2.4.7 <- �����
		2.5 ���������� �������
			2.5.1 ������������� ���������� +
			2.5.2 ������������� ������ +
			2.5.3 ������������� ������ +
			2.5.4 ������������� �������� +
			2.5.5 ������������� ��������� +
		2.6 ����� �������
			2.6.1 ������ ���������� +
			2.6.2 ������ ������ + 
			2.6.3 ������ ������ +
			2.6.4 ������ �������� +
			2.6.5 ������ ��������� +
		2.7 ��������� �������� ����� +
		2.8 <- ������� � ���� *
	0 ����� �� ��������

���������������� ����(�������)
	1 �������� ����� �������
	2 �������� ���� ��������� �������
	3 ��������� �����
	0 ����� �� ��������
	

���������������� ���� (������)
	1 �������� ����� �������
	2 �������� ����������
	3 ������� �����
	4 ����������� ���� ���������
	5 �������� ����� �� �����
	0 ����� �� ��������
*/

class Menu {
public:
	static void initMenu(); //���� �����������
	
	/*���� ��������������*/
	static void adminMenu(string name); //���� ��������������(��������)
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

	/*���� ������������*/
	static void userMenu(string name); //���� ������������(������)

	/*���� ��������*/
	static void mechanicMenu(string name); //���� ��������

	static void authorize(); //�����������
	static void registr(int role,bool access); //�����������

	static shared_ptr<Client> inputClient(string name); // ���� ������� � �������
	static shared_ptr<Mechanic> inputMechanic(string name); // ���� �������� � �������
	static shared_ptr<Request> inputRequest(); // ���� ������ � �������
	static shared_ptr<Vehicle> inputVehicle(); // ���� ���������� � �������
	static shared_ptr<Service> inputService(); // ���� ������ � �������
	static shared_ptr<Request> inputRequestForUser(string login); // ���� ������ ��� ������������

	static User changeUser(vector<User> users, User user); // ��������� ��������
	static void changeVehicle(vector<shared_ptr<Vehicle>> vehicles, shared_ptr<Vehicle> vehicle); // ��������� ����������
	static void changeRequest(vector<shared_ptr<Request>> requests, shared_ptr<Request> req); // ��������� ������
	static void changeService(vector<shared_ptr<Service>> services, shared_ptr<Service> ser); // ��������� ������
};
