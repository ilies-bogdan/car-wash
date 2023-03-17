/*
* Car.h
* Car class
*/

#pragma once

#include <string>	
#include <iostream>

using std::string;
using std::ostream;	


class Car {
private:
	string regNumber;
	string manufacturer;
	string model;
	string type;
public:
	Car() = default;

	Car(const string& regNumber, const string& manufacturer, const string& model, const string& type);

	Car(const Car&);

	/*
	* Overloads the assignment operator for a car
	*/
	Car& operator=(const Car&);

	/*
	* Overloads the equality operator for a car
	*/
	bool operator==(const Car&) const noexcept;

	/*
	* Overloads the inequality operator for a car
	*/
	bool operator!=(const Car&) const noexcept;

	/*
	* Gets the registration number
	*/
	string getRegNumber() const {
		return regNumber;
	}

	/*
	* Gets the manufacturer
	*/
	string getManufacturer() const {
		return manufacturer;
	}

	/*
	* Gets the model
	*/
	string getModel() const {
		return model;
	}

	/*
	* Get the type
	*/
	string getType() const {
		return type;
	}

	/*
	* Set the manufacturer
	*/
	void setManufacturer(string newManufacturer) {
		this->manufacturer = newManufacturer;
	}

	/*
	* Set the model
	*/
	void setModel(string newModel) {
		this->model = newModel;
	}

	/*
	* Set the type
	*/
	void setType(string newType) {
		this->type = newType;
	}

	/*
	* Returns the car in the following format: <regNumber>: <manufacturer> <model> - <type>
	*/
	string toString() const {
		return regNumber + ": " + manufacturer + " " + model + " - " + type;
	}

	/*
	* Insertion operator overload
	*/
	friend ostream& operator<<(ostream& stream, const Car& car);

	~Car();
};