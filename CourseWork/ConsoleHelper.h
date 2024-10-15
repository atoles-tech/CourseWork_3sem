#ifndef CONSOLEHELPER_H
#define CONSOLEHELPER_H

#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class ConsoleHelper {
public:
	static string readString(string s); // �������� ������
	static int readInt(string s); // �������� ����� �����
	static double readDouble(string s); // �������� ����� � ��������� ������
	static int getOneInt(string numbers); // �������� ����� �� ���������� ������
	static vector<string> split(string str); // ��������� ������
	static string getPassword(string str); // ���� ������(������� ������� �������� *)
	static bool checkString(string str); // �������� ������ �� ���� ������������ ��������
	static bool checkName(string name); // �������� ����� ��� ������� �� ����������� �������
};

#endif CONSOLEHELPER_H