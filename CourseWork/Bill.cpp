#include "Bill.h"

Bill::Bill(int sum, bool status) {
	this->sum = sum;
	this->status = status;
}

Bill::Bill() {
	this->sum = 0;
	this->status = false;
}

void Bill::approveBill() { this->status = true; }

/*�������*/
int Bill::getSum() { return sum; }
bool Bill::getStatus() { return status; }