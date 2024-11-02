#include "Bill.h"

Bill::Bill(double sum, bool status) {
	this->sum = sum;
	this->status = status;
}

Bill::Bill() {
	this->sum = 0;
	this->status = false;
}

void Bill::approveBill() { this->status = true; }

/*Геттеры*/
double Bill::getSum() { return sum; }
bool Bill::getStatus() { return status; }