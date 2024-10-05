#ifndef SERVICESTATIO_H
#define SERVICESTATIO_H

#include <iostream>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "Client.h"

using namespace std;

class ServiceStation {
private:
	static ServiceStation service;
	
	vector<shared_ptr<Vehicle>> vehicles;
	vector<shared_ptr<Client>> clients;
public:
	static ServiceStation& getInstance();
	
	/*Геттеры*/

private:
	ServiceStation() {}
};

#endif 
