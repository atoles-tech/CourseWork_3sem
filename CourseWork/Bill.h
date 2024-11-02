#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>

using namespace std;

class Bill {
private:
	double sum;
	bool status;
public:
	Bill(double sum, bool status);
	Bill();

	void approveBill();

	/*Геттеры*/
	double getSum();
	bool getStatus();
};

#endif
