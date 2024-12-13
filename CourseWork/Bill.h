#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>

using namespace std;

class Bill {
private:
	double sum; // Стоимость
	bool status; // Статус оплаты
public:
	Bill(double sum, bool status);
	Bill();

	void approveBill(); // Оплатить счет

	/*Геттеры*/
	double getSum();
	bool getStatus();
};

#endif
