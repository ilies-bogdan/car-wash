/*
* Undo.h
* Undo functions declarations
*/

#pragma once

#include "CarsService.h"


class Undo {
public:
	/*
	* Virtual generic undo method
	*/
	virtual void doUndo() = 0;

	virtual ~Undo() {};
};

class UndoStore : public Undo {
private:
	CarsRepository& carsRepo;
	CarsRepository& carsToWash;
	Car addedCar;
public:
	UndoStore(CarsRepository& carsRepo, CarsRepository& carsToWash, Car car) : carsRepo{ carsRepo }, carsToWash{ carsToWash }, addedCar{ car } {}
	void doUndo() override {
		carsRepo.deleteCar(addedCar);
		try {
			carsToWash.deleteCar(addedCar);
		}
		catch (...) {}
	}
};

class UndoDelete : public Undo {
private:
	CarsRepository& carsRepo;
	CarsRepository& carsToWash;
	Car deletedCar;
	bool wasInWashList;
public:
	UndoDelete(CarsRepository& carsRepo, CarsRepository& carsToWash, Car car, bool wasInWashList) : carsRepo{ carsRepo }, carsToWash{ carsToWash }, deletedCar{ car }, wasInWashList{ wasInWashList }  {}
	void doUndo() override {
		carsRepo.storeCar(deletedCar);
		// check if the car was in the wash list before deletion
		if (wasInWashList) {
			carsToWash.storeCar(deletedCar);
		}
	}
};

class UndoUpdate : public Undo {
private:
	CarsRepository& carsRepo;
	CarsRepository& carsToWash;
	Car oldCar;
public:
	UndoUpdate(CarsRepository& carsRepo, CarsRepository& carsToWash, Car car) : carsRepo{ carsRepo }, carsToWash{ carsToWash }, oldCar{ car } {}
	void doUndo() override {
		carsRepo.updateCar(oldCar);
		try {
			carsToWash.updateCar(oldCar);
		}
		catch (...) {}
	}
};