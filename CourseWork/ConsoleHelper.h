#ifndef CONSOLEHELPER_H
#define CONSOLEHELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class ConsoleHelper {
public:
	static string readString(string s); // Получить строку
	static int readInt(string s); // Получить целое число
	static double readDouble(string s); // Получить число с плавающей точкой
	static int getOneInt(string numbers); // Получить цифру из переданной строки
	static vector<string> split(string str); // Разбиваем строку
};

#endif CONSOLEHELPER_H