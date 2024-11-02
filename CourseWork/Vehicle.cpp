#include "Vehicle.h"

const string Vehicle::filename = "vehicles.dat";

Vehicle::Vehicle(string car_number, string model, string brand, string vin) {
	this->car_number = car_number;
	this->model = model;
	this->brand = brand;
	this->vin = vin;
}

Vehicle::Vehicle() {
	this->car_number = "()";
	this->model = "()";
	this->brand = "()";
	this->vin = "()";
}

void Vehicle::showVehicle(vector<shared_ptr<Vehicle>> vehicles) {
	if (vehicles.size() == 0) {
		cout << "Автомобилей нет!" << endl;
		return;
	}

	cout << setw(7) << "Номер" << "|"
		<< setw(12) << "Номер авто" << "|"
		<< setw(15) << "Марка" << "|"
		<< setw(15) << "Модель" << "|"
		<< setw(30) << "VIN" << "|" << endl;

	cout << string(84, '=') << endl;
	int i = 1;
	for (shared_ptr<Vehicle> v : vehicles) {
		cout << setw(7) << i++ << "|"
			<< setw(12) << v->getNumber() << "|"
			<< setw(15) << v->getBrand() << "|"
			<< setw(15) << v->getModel() << "|"
			<< setw(30) << v->getVIN() << "|" << endl;
	}
}

/*Геттеры*/
string Vehicle::getNumber() { return car_number; }
string Vehicle::getModel() { return model; }
string Vehicle::getBrand() { return brand; }
string Vehicle::getVIN() { return vin; }

void Vehicle::setBrand(string brand) { this->brand = brand; }
void Vehicle::setModel(string model) { this->model = model; }
void Vehicle::setNumber(string number) { this->car_number = number; }
void Vehicle::setVIN(string vin) { this->vin = vin; }

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

void Vehicle::writeOneFile(shared_ptr<Vehicle> v) {
	ofstream f(filename, ios::binary | std::ios::app);

		f << v->car_number << ";"
			<< v->model << ";"
			<< v->brand << ";"
			<< v->vin << endl;
}
