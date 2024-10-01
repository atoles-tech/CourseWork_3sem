#ifndef CONSOLEHELPER_H
#define CONSOLEHELPER_H

#include <iostream>
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
};

#endif CONSOLEHELPER_H