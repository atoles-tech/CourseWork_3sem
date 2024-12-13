#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>

#include "Menu.h"
#include "ServiceStation.h"

/*���������� ������������������ ������� ���������������� ������� ������������ ������������*/

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	ServiceStation::getInstance().init();

	Menu::initMenu();

	return 0;
}