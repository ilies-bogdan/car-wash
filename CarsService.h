/*
* CarsService.h
* CarsService class
*/

#pragma once

#include <functional>
#include <map>
#include <fstream>
#include <random>
#include <chrono>
#include "CarValidator.h"
#include "CarsRepository.h"
#include "FileCarsRepository.h"
#include "Undo.h"
#include "Observable.h"

using std::map;
using std::ofstream;


class CarsService : public Observable {
private:
	CarValidator& carVal;
	CarsRepository& carsRepo;
	CarsRepository& carsToWash;
	vector<Undo*> undoActions;

	/*
	* General filtering method
	* Input: filterFunction - bool
	* Output: returns a vector of the cars that passed the filter function
	*/
	vector<Car> filter(std::function <bool(const Car&)> filterFunction);

	/*
	* General sorting method
	* Input: sortFunction - function with the bool(const Car&, const car&) signature (or lambda function)
	* Output: returns the sorted cars repository
	*/
	vector<Car> sort(std::function <bool(const Car&, const Car&)> sortFunction);
public:
	CarsService(CarValidator& _carVal, CarsRepository& _carsRepo, CarsRepository& _carsToWash) noexcept :carVal{ _carVal }, carsRepo{ _carsRepo }, carsToWash(_carsToWash) {}
	CarsService(const CarsService&) = delete;

	/*
	* Gets the size of the service
	* Input:
	* Output: returns the size
	*/
	int size() const noexcept;

	/*
	* Gets all the cars
	* Input:
	* Output: returns a list of all the cars
	*/
	const vector<Car> getAll() const;

	/*
	* Creates, validates and stores a car
	* Input: regNumber - const string&
	*		 manufacturer - const string&
	*		 model - const string&
	*		 type - const string&
	* Output: returns nothing if the car has been stored successfully
	* Raises: ValidationException with the following text:
	*				"Invalid registration number!\n", if the registration number field is empty
	*				"Invalid manufacturer!\n", if the manufacturer field is empty
	*				"Invalid model!\n", if the model field is empty
	*				"Invalid type!\n", if the type field is empty
	*		  RepositoryException with the following text:
	*				"Car already existing!\n", , if the car has already been stored once
	*/
	void storeCar(const string& regNumber, const string& manufacturer, const string& model, const string& type);

	/*
	* Finds a car by its registration number
	* Input: regNumber - const string&
	* Output: returns a constant reference to the car
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	const Car& findCarByRegistrationNumber(const string&);

	/*
	* Finds and deletes a car by its registration number
	* Input: regNumber - const string&
	* Output: returns nothing if the car has been deleted successfully
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	void deleteCar(const string&);

	/*
	* Finds and updates a car by its registration number
	* Input: regNumber - const string&
	*		 newManufacturer - const string&
	*		 newModel - const string&
	*		 newType - const string&
	* Output: returns nothing if the car has been updated successfully
	* Raises: ValidationException with the following text:
	*				"Invalid registration number!\n", if the registration number field is empty
	*				"Invalid manufacturer!\n", if the manufacturer field is empty
	*				"Invalid model!\n", if the model field is empty
	*				"Invalid type!\n", if the type field is empty
	*		  RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	void updateCar(const string& regNumber, const string& newManufacturer, const string& newModel, const string& newType);

	/*
	* Filters all the cars where the parameter is a substring of their manufacturer
	* Input: manufacturer - const string&
	* Output: returns the filtered vector
	*/
	vector<Car> filterByManufacturer(const string&);

	/*
	* Filters all the cars where the parameter is a substring of their  type
	* Input: type - const string&
	* Output: returns the filtered vector
	*/
	vector<Car> filterByType(const string&);

	/*
	* Sorts all the cars by their registration number in ascending order
	* Input:
	* Output: returns the sorted vector
	*/
	vector<Car> sortByRegistrationNumber();

	/*
	* Sorts all the cars by their type in descending order
	* Input:
	* Output: returns the sorted vector
	*/
	vector<Car> sortByType();

	/*
	* Sorts all the cars by manufacturer in ascending order and where the 
	* manufacturers are the same, the sorting is done by model
	* Input:
	* Output: returns the sorted vector
	*/
	vector<Car> sortByManufacturerModel();

	/*
	* Reports the count for each model
	* Input: model - const string&
	* Output: returns the number of cars for each model
	*/
	const map<string, int> reportManufacturerCount();

	/*
	* Empties the cars to wash list
	* Input:
	* Output:
	*/
	void emptyWashList() noexcept;

	/*
	* Gets the size of the to wash list
	* Input:
	* Output: returns the size
	*/
	int sizeWashList() const noexcept;

	/*
	* Gets the wash list
	* Input:
	* Output: returns a list of all the cars in the wash list
	*/
	const vector<Car>& getWashList() const noexcept;

	/*
	* Adds a car from the cars repository to the wash list by its registration number
	* Input: regNumber - const string& (must be in the cars repository)
	* Output: returns nothing if the car has been successfully added to the wash list
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*				"Car already existing!\n", if the car is already in the wash list
	*/
	void addToWashList(const string&);

	/*
	* Generates a wash list with <number> random cars from the repository
	* Input: number - int (must be > 0)
	* Output: generates the wash list
	*/
	void generateWashList(int number);

	/*
	* Exports the wash list to HTML file
	* Input: fileName - const string& (must be an HTML file)
	* Output:
	*/
	void exportWashListToFile(const string&) const;

	/*
	* Undoes the last action
	* Input:
	* Output:
	* Raises: RepositoryException with the following text:
	*			"No action to undo!\n", if the undo list is empty
	*/
	void undo();

	~CarsService();
};