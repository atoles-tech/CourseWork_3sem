#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "ConsoleHelper.h"

using namespace std;

class Vehicle {
private:
	const static string filename;

	string car_number; // ������������� �����
	string model; // ������ ����������
	string brand; // ����� ����������
	string vin; // VIN ����� ���������� (������� �� 17 ��������)
public:
	Vehicle(string car_number, string model, string brand, string vin);
	Vehicle();

	/*�������*/
	string getNumber();
	string getModel();
	string getBrand();
	string getVIN();

	/*�������*/
	void setBrand(string brand);
	void setModel(string model);
	void setNumber(string number);
	void setVIN(string vin);

	static void showVehicle(vector<shared_ptr<Vehicle>> vehicles);

	/*������ �� ����� + ������ � ����*/
	static vector<shared_ptr<Vehicle>> readFile();
	static void writeFile(vector<shared_ptr<Vehicle>> vehicles);
	static void writeOneFile(shared_ptr<Vehicle> v);
};

#endif // !VEHICLE_H
