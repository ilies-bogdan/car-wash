/*
* CarValidator.h
* CarValidator class
*/

#pragma once

#include <string>
#include "Exceptions.h"
#include "Car.h"


class CarValidator {
public:
	CarValidator() noexcept = default;

	void validateCar(const Car& car);
};