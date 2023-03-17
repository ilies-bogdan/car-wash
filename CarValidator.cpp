/*
* CarValidator.cpp
* CarValidator class implementation
*/

#include "CarValidator.h"


void CarValidator::validateCar(const Car& car) {
	std::string valEx = "";
	if (car.getRegNumber() == "") {
		valEx += "Invalid registration number!\n";
	}
	if (car.getManufacturer() == "") {
		valEx += "Invalid manufacturer!\n";
	}
	if (car.getModel() == "") {
		valEx += "Invalid model!\n";
	}
	if (car.getType() == "") {
		valEx += "Invalid type!\n";
	}
	if (valEx.size() > 0) {
		throw ValidationException(valEx);
	}
}