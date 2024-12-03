#include "ConsoleHelper.h"

string ConsoleHelper::readString(string s) {
	cout << s;
	string str;
	while (true) {
		getline(cin, str);
		if (str.size() >= 1) {
			break;
		}
	}
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

string ConsoleHelper::getPassword(string str) {
	const int maxLength = 40;
	char input[maxLength];
	int index = 0;

	cout << str;

	while (true) {
		char ch = _getch();

		if (ch == 13) { // Enter
			break;
		}
		else if (ch == 8) { // Backspace
			if (index > 0) {
				index--;
				std::cout << "\b \b";
			}
		}
		else if(ch == ';') { // ;
			continue;
		}
		else if (index < maxLength - 1) {
			input[index++] = ch;
			std::cout << '*';
		}
	}

	input[index] = '\0';
	string s = input;

	return s;
}

bool ConsoleHelper::checkString(string str) {
	for (char c : str) {
		if (c == ';' || c == '(' || c == ')') {
			return false;
		}
	}
	return true;
}

bool ConsoleHelper::checkName(string name) {
	if (name.size() < 1) { return false; }
	for (char c : name) {
		if ((c >= 192 && c <= 223) || (c >= 224 && c <= 255)) {
			return false;
		}
	}
	return true;
}

int ConsoleHelper::getIntToSize(int size) {
	int input;
	if (size == 0) {
		return -1;
	}
	do {
		input = readInt("");
		if (input >= 1 && input <= size) {
			break;
		}
		else {
			cout << "Данного пользователя нет! Повторите попытку: " << endl;
		}
	} while (true);
	return input;
}

int ConsoleHelper::getChoose(string str) {
	cout << str;
	int input = getOneInt("01");
	return input;
}
