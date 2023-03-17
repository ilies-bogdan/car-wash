/*
* FileCarsRepository.h
* FileCarsRepository class
*/

#pragma once

#include <iostream>
#include <fstream>
#include "CarsRepository.h"


class FileCarsRepository : public CarsRepository {
private:
	string filePath;
	
	/*
	* Splits a string by a delimitator
	* Input: str, delim - strings
	* Output: returns a vector of all the components
	*/
	//vector<string> split(string str, string delim);
	
	void loadFromFile();
	
	void writeToFile();
public:
	FileCarsRepository(string filePath) : filePath{ filePath } {
		CarsRepository();
	}

	int size() noexcept override {
		loadFromFile();
		return CarsRepository::size();
	}

	vector<Car> copy() override {
		loadFromFile();
		return CarsRepository::copy();
	}

	void empty() noexcept override {
		loadFromFile();
		CarsRepository::empty();
		writeToFile();
	}

	const vector<Car>& getAll() noexcept override {
		loadFromFile();
		return CarsRepository::getAll();
	}

	void storeCar(const Car& car) override {
		loadFromFile();
		CarsRepository::storeCar(car);
		writeToFile();
	}

	const Car& findCar(const Car& car) override {
		loadFromFile();
		return CarsRepository::findCar(car);
	}

	void deleteCar(const Car& car) override {
		loadFromFile();
		CarsRepository::deleteCar(car);
		writeToFile();
	}

	void updateCar(const Car& car) override {
		loadFromFile();
		CarsRepository::updateCar(car);
		writeToFile();
	}
};