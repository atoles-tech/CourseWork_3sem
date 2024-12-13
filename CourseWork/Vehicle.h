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

	string car_number; // Автомобильный номер
	string model; // Модель автомобиля
	string brand; // Марка автомобиля
	string vin; // VIN номер автомобиля (состоит из 17 символов)
public:
	Vehicle(string car_number, string model, string brand, string vin);
	Vehicle();

	/*Геттеры*/
	string getNumber();
	string getModel();
	string getBrand();
	string getVIN();

	/*Сеттеры*/
	void setBrand(string brand);
	void setModel(string model);
	void setNumber(string number);
	void setVIN(string vin);

	static void showVehicle(vector<shared_ptr<Vehicle>> vehicles);

	/*Чтение из файла + Запись в файл*/
	static vector<shared_ptr<Vehicle>> readFile();
	static void writeFile(vector<shared_ptr<Vehicle>> vehicles);
	static void writeOneFile(shared_ptr<Vehicle> v);
};

#endif // !VEHICLE_H
