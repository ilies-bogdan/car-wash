#pragma once

#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Exceptions.h"
#include "List.h"
#include "Car.h"
#include "CarValidator.h"
#include "CarsRepository.h"
#include "FileCarsRepository.h"
#include "CarsService.h"


class Tests {
private:
	void runTestsList();

	void runTestsDomain();
	void testCreateCar();
	void testEqualCars();

	void runTestsValidation();
	void testValidCar();
	void testInvalidCar();

	void runTestsCarsRepository();
	void testCreateCopyCarsRepository();
	void testStoreFindGetAllCarsRepository();
	void testDeleteCarsRepository();
	void testUpdateCarsRepository();

	void runTestsCarsService();
	void testCreateCarsService() const noexcept;
	void testStoreFindGetAllCarsService();
	void testDeleteCarsService();
	void testUpdateCarsService();
	void testFilterReportCarsService();
	void testSortCarsService();
	void testCarsToWashService();
	void testUndo();
public:
	void runAllTests();
};