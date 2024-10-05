#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>

using namespace std;

class Service {
private:
	int service_id;
	string name;
	double price;
	int time; // � �����
public:
	Service(int service_id,string name, double price, int time);

	/*�������*/
	int getServiceId();
	string getName();
	double getPrice();
	int getTime();

	/*�������*/
	void setServiceId(int id);
	void setName(string name);
	void setPrice(double price);
	void setTime(int time);
};

#endif // !SERVICE_H

