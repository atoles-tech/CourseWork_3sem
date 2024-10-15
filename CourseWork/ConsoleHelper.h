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
	static string readString(string s); // Получить строку
	static int readInt(string s); // Получить целое число
	static double readDouble(string s); // Получить число с плавающей точкой
	static int getOneInt(string numbers); // Получить цифру из переданной строки
	static vector<string> split(string str); // Разбиваем строку
	static string getPassword(string str); // Ввод пароля(Символы закрыты символом *)
	static bool checkString(string str); // Проверка строки на ввод неккоректных символов
	static bool checkName(string name); // Проверка имени или фамилии на неккоретные символы
};

#endif CONSOLEHELPER_H