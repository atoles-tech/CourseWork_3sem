#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>

using namespace std;

class Bill {
private:
	int sum;
	bool status;
public:
	Bill(int sum, bool status);
	Bill();

	void approveBill();

	/*Геттеры*/
	int getSum();
	bool getStatus();
};

#endif
