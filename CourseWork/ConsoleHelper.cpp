#include "ConsoleHelper.h"

string ConsoleHelper::readString() {
	string str;
	getline(cin, str);
	return str;
}

int ConsoleHelper::readInt() {
	while (true) {
		try {
			int value;
			cin >> value;
			return value;
		}
		catch (runtime_error) {}
	}
}

double ConsoleHelper::readDouble() {
	while (true) {
		try {
			double value;
			cin >> value;
			return value;
		}
		catch (runtime_error) {}
	}
}
