#include <iostream>
#include "ConsoleHelper.h"
#include "User.h"
#include "HashFunc.h"

class Menu {
public:
	static void initMenu(); //���� �����������
	static void adminMenu(string name); //���� ��������������(���������/������������)
	static void userMenu(string name); //���� ������������(��������)
	static void authorize(); //�����������
	static void registr(); //�����������
};
