#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <fstream>
#include "ConsoleHelper.h"

using namespace std;

class Service {
private:
	const static string filename;

	int service_id;
	string name;
	double price;
	int time; // � �����
public:
	Service(int service_id,string name, double price, int time);
	Service();

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

	/*������ �� ����� + ������ � ����*/
	static vector<shared_ptr<Service>> readFile();
	static void writeFile(vector<shared_ptr<Service>> services);

	static void showService(vector<shared_ptr<Service>> services);
};

#endif // !SERVICE_H

