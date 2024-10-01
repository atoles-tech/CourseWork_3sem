#include "ConsoleHelper.h"

string ConsoleHelper::readString(string s) {
	cout << s;
	string str;
	getline(cin, str);
	return str;
}

int ConsoleHelper::readInt(string s) {
	cout << s;
	int i;
	cin.clear();
	while (true) {
		cin >> i;
		if (cin.good()) {
			cin.ignore(20, '\n');
			break;
		}
		cin.clear();
		cout << "Некорректный ввод!" << endl;
		cin.ignore(20, '\n');
	}
	return i;
}

double ConsoleHelper::readDouble(string s) {
	cout << s;
	double i;
	cin.clear();
	while (true) {
		cin >> i;
		if (cin.good()) {
			cin.ignore(20, '\n');
			break;
		}
		cin.clear();
		cout << "Некорректный ввод!" << endl;
		cin.ignore(20, '\n');
	}
	return i;
}

int ConsoleHelper::getOneInt(string numbers) {
	while (true) {
		int value = readInt("");

		if (value > 9 || value < 0) {
			cout << "Некорректный ввод!" << endl;
			continue;
		}

		for (int i = 0; i < numbers.size(); i++) {
			if (value == numbers.at(i) - '0') {
				return value;
			}
		}
		cout << "Некорректный ввод!" << endl;
	}
}

vector<string> ConsoleHelper::split(string str) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	
	while (getline(ss, token, ';')) {
		tokens.push_back(token);
	}

	return tokens;
}