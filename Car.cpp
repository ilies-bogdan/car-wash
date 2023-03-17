/*
* Car.cpp
* Car class implementation
*/

#include "Car.h"


Car::Car(const string& regNumber, const string& manufacturer, const string& model, const string& type)
	:regNumber{ regNumber },
	manufacturer{ manufacturer },
	model{ model },
	type{ type } {
}

Car::Car(const Car& car)
	:regNumber{ car.regNumber },
	manufacturer{ car.manufacturer },
	model{ car.model },
	type{ car.type } {
}

Car& Car::operator=(const Car& car) {
	regNumber = car.regNumber;
	manufacturer = car.manufacturer;
	model = car.model;
	type = car.type;
	return *this;
}

bool Car::operator==(const Car& car) const noexcept {
	return this->regNumber == car.regNumber;
}

bool Car::operator!=(const Car& car) const noexcept {
	return !(*this == car);
}

Car::~Car() {

}

ostream& operator<<(ostream& stream, const Car& car) {
	stream << car.regNumber << " ";
	stream << car.manufacturer << " ";
	stream << car.model << " ";
	stream << car.type << "\n";
	return stream;
}