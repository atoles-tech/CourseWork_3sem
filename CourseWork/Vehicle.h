#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "ConsoleHelper.h"

using namespace std;

class Vehicle {
private:
	const static string filename;

	string car_number;
	string model;
	string brand;
	string vin;
public:
	Vehicle(string car_number, string model, string brand, string vin);
	
	/*Геттеры*/
	string getNumber();
	string getModel();
	string getBrand();
	string getVIN();

	/*Чтение из файла + Запись в файл*/
	static vector<shared_ptr<Vehicle>> readFile();
	static void writeFile(vector<shared_ptr<Vehicle>> vehicles);
};

#endif // !VEHICLE_H
