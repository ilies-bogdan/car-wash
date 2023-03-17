/*
* CarsRepository.h
* CarsRepository class
*/

#pragma once

#include <vector>
#include <algorithm>
#include "List.h"
#include "Exceptions.h"
#include "Car.h"

using std::vector;


class CarsRepository {
protected:
	vector<Car> carsRepo;
public:
	CarsRepository() noexcept;

	/*
	* Gets the current size of the cars repository
	* Input:
	* Output: returns the size
	*/
	virtual int size() noexcept;

	/*
	* Makes an independent copy of the current cars repository
	* Input:
	* Output: returns a copy, vector<Car>
	*/
	virtual vector<Car> copy();

	/*
	* Empties the cars repository
	* Input:
	* Output:
	*/
	virtual void empty() noexcept;

	/*
	* Gets all the cars in the cars repository
	* Input:
	* Output: returns a list of all the cars
	*/
	virtual const vector<Car>& getAll() noexcept;

	/*
	* Stores a car in the cars repository
	* Input: car - const Car&
	* Output: returns nothing if the car has been stored successfully
	* Raises: RepositoryException with the following text:
	*				"Car already existing!\n", if the car has already been stored once
	*/
	virtual void storeCar(const Car&);

	/*
	* Finds a car in the cars repository
	* Input: car - const Car&
	* Output: returns a constant reference to the car if it finds it
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	virtual const Car& findCar(const Car&);

	/*
	* Deletes a car from the repository
	* Input: car - const Car&
	* Output: returns nothing if the car has been deleted successfully
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	virtual void deleteCar(const Car&);

	/*
	* Updates a car in the car repository
	* Input: car - const Car&
	* Output: returns nothing if the car has been updated successfully
	* Raises: RepositoryException with the following text:
	*				"Nonexistent car!\n", if the car is not in the cars repository
	*/
	virtual void updateCar(const Car&);

	~CarsRepository() = default;
};