/*
* UI.h
* UI class
*/

#pragma once

#include <iostream>
#include <string>
#include "CarsService.h"
#include "exceptions.h"


class Console {
private:
	CarsService& carsSrv;
	/*
	* Application menu
	*/
	void showMenu();

	/*
	* Stores a car
	*/
	void uiStoreCar();

	/*
	* Finds a car
	*/
	void uiFindCar();

	/*
	* Deletes a car
	*/
	void uiDeleteCar();

	/*
	* Updates a car
	*/
	void uiUpdateCar();

	/*
	* Prints all cars
	*/
	void uiPrintCars(vector<Car> cars);

	/*
	* Filter options
	*/
	void showFilterMenu();
	
	/*
	* Filter function
	*/
	void uiFilter();

	/*
	* Filters by manufacturer
	*/
	void uiFilterByManufacturer();

	/*
	* Filters by type
	*/
	void uiFilterByType();

	/*
	* Sort options
	*/
	void showSortMenu();

	/*
	* Sort function
	*/
	void uiSort();

	/*
	* Sorts by registration number
	*/
	void uiSortByRegistrationNumber();

	/*
	* Sorts by type
	*/
	void uiSortByType();

	/*
	* Sorts by manufacturer and model
	*/
	void uiSortByManufacturerModel();

	/*
	* Reports manufacturer count
	*/
	void uiReportManufacturer();

	/*
	* Wash options
	*/
	void showWashMenu();

	/*
	* Wash list function
	*/
	void uiWashList();

	/*
	* Empties the wash list
	*/
	void uiEmptyWashList() noexcept;

	/*
	* Adds a car to the wash list
	*/
	void uiAddCarToWashList();

	/*
	* Randomly generates a wash list
	*/
	void uiGenerateWashList();

	/*
	* Exports the wash list to file
	*/
	void uiExportWashListToFile();

	/*
	* Undoes the last action
	*/
	void uiUndo();
public:
	Console(CarsService& _carsSrv) noexcept :carsSrv{ _carsSrv } {
	}

	/*
	* Application run function
	*/
	void run();

	~Console() = default;
};