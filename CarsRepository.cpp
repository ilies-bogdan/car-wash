/*
* CarsRepository.cpp
* CarsRepository class implementation
*/

#include "CarsRepository.h"


CarsRepository::CarsRepository() noexcept {

}

int CarsRepository::size() noexcept {
    return this->carsRepo.size();
}

vector<Car> CarsRepository::copy() {
    vector<Car> copy;
    for (const auto& car : carsRepo) {
        copy.push_back(car);
    }
    return copy;
}

void CarsRepository::empty() noexcept {
    carsRepo.clear();
}

const vector<Car>& CarsRepository::getAll() noexcept {
    return this->carsRepo;
}

void CarsRepository::storeCar(const Car& car) {
    auto it = std::find(this->carsRepo.begin(), this->carsRepo.end(), car);
    if (it != carsRepo.end()) {
        throw RepositoryException("Car already existing!\n");
    }
    carsRepo.push_back(car);
}

const Car& CarsRepository::findCar(const Car& car) {
    auto it = std::find(this->carsRepo.begin(), this->carsRepo.end(), car);
    if (it == this->carsRepo.end()) {
        throw RepositoryException("Nonexistent car!\n");
    }
    return *it;
}

void CarsRepository::deleteCar(const Car& car) {
    auto it = std::find(this->carsRepo.begin(), this->carsRepo.end(), car);
    if (it == this->carsRepo.end()) {
        throw RepositoryException("Nonexistent car!\n");
    }
    carsRepo.erase(it);
}

void CarsRepository::updateCar(const Car& car) {
    auto it = std::find(this->carsRepo.begin(), this->carsRepo.end(), car);
    if (it == this->carsRepo.end()) {
        throw RepositoryException("Nonexistent car!\n");
    }
    *it = car;
}