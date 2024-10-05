#include "Vehicle.h"

const string Vehicle::filename = "vehicles.dat";

Vehicle::Vehicle(string car_number, string model, string brand, string vin) {
	this->car_number = car_number;
	this->model = model;
	this->brand = brand;
	this->vin = vin;
}

/*Геттеры*/
string Vehicle::getNumber() { return car_number; }
string Vehicle::getModel() { return model; }
string Vehicle::getBrand() { return brand; }
string Vehicle::getVIN() { return vin; }

vector<shared_ptr<Vehicle>> Vehicle::readFile() {
	vector<shared_ptr<Vehicle>> vehicles;

	ifstream f(filename, ios::binary);

	while (!f.eof()) {
		string line;
		getline(f, line);
		vector<string> fields = ConsoleHelper::split(line);

		if (fields.size() != 4) {
			return vehicles;
		}

		string car_number = fields[0];
		string model = fields[1];
		string brand = fields[2];
		string vin = fields[3];

		vehicles.push_back(make_shared<Vehicle>(car_number,model,brand,vin));
	}

	return vehicles;
}

void Vehicle::writeFile(vector<shared_ptr<Vehicle>> vehicles) {
	ofstream f(filename, ios::binary);

	for (shared_ptr<Vehicle> v : vehicles) {
		f << v->car_number << ";"
		  << v->model << ";"
		  << v->brand << ";"
		  << v->vin << endl;
	}
}