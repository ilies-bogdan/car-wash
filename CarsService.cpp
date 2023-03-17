/*
* CarsService.h
* CarsService class
*/

#include "CarsService.h"


vector<Car> CarsService::filter(std::function <bool(const Car&)> filterFunction) {
    vector<Car> result(carsRepo.size());
    vector<Car> all{ carsRepo.getAll() };
    auto it = std::copy_if(all.begin(), all.end(), result.begin(), filterFunction);
    result.resize(std::distance(result.begin(), it));
    return result;
}

vector<Car> CarsService::sort(std::function <bool(const Car&, const Car&)> sortFunction) {
    vector<Car> sorted{ this->carsRepo.copy() };
    std::sort(sorted.begin(), sorted.end(), sortFunction);
    return sorted;
}

int CarsService::size() const noexcept {
    return this->carsRepo.size();
}

const vector<Car> CarsService::getAll() const {
    return this->carsRepo.getAll();
}

void CarsService::storeCar(const string& regNumber, const string& manufacturer, const string& model, const string& type) {
    Car car{ regNumber, manufacturer, model, type };
    this->carVal.validateCar(car);
    this->carsRepo.storeCar(car);
    undoActions.push_back(new UndoStore(this->carsRepo, this->carsToWash, car));
    this->notifyAll();
}

const Car& CarsService::findCarByRegistrationNumber(const string& regNumber) {
    Car toSearch{ regNumber, "", "", "" };
    return this->carsRepo.findCar(toSearch);
}

void CarsService::deleteCar(const string& regNumber) {
    Car toFind{ regNumber, "", "", "" };
    Car car{ this->carsRepo.findCar(toFind) };
    bool wasInWashList = true;
    try {
        Car inWashList{ carsToWash.findCar(toFind) };
    }
    catch (const RepositoryException& re) {
        wasInWashList = false;
    }

    this->carsRepo.deleteCar(car);
    try {
        this->carsToWash.deleteCar(car);
    }
    catch (...) {
    }
    this->undoActions.push_back(new UndoDelete(this->carsRepo, this->carsToWash, car, wasInWashList));
    this->notifyAll();
}

void CarsService::updateCar(const string& regNumber, const string& newManufacturer, const string& newModel, const string& newType) {
    Car car{ regNumber, newManufacturer, newModel, newType };
    Car found = this->carsRepo.findCar(car);
    if (newManufacturer == "") {
        car.setManufacturer(found.getManufacturer());
    }
    if (newModel == "") {
        car.setModel(found.getModel());
    }
    if (newType == "") {
        car.setType(found.getType());
    }
    this->carVal.validateCar(car);
    this->carsRepo.updateCar(car);
    try {
        this->carsToWash.updateCar(car);
    }
    catch (...) {
    }
    this->undoActions.push_back(new UndoUpdate(this->carsRepo, this->carsToWash, found));
    this->notifyAll();
}

vector<Car> CarsService::filterByManufacturer(const string& manufacturer) {
     return this->filter([&](const Car& car) {return car.getManufacturer().find(manufacturer) != string::npos;});
}

vector<Car> CarsService::filterByType(const string& type) {
    return this->filter([&](const Car& car) {return car.getType().find(type) != string::npos;});
}

vector<Car> CarsService::sortByRegistrationNumber() {
    return this->sort([](const Car& first, const Car& second) {return first.getRegNumber() < second.getRegNumber();});
}

vector<Car> CarsService::sortByType() {
    return this->sort([](const Car& first, const Car& second) {return first.getType() > second.getType();});
}

vector<Car> CarsService::sortByManufacturerModel() {
    return this->sort([](const Car& first, const Car& second) {
        if (first.getManufacturer() == second.getManufacturer()) {
            return first.getModel() < second.getModel();
        }
        return first.getManufacturer() < second.getManufacturer();
        });
}

const map<string, int> CarsService::reportManufacturerCount() {
    map<string, int> res;
    for (const auto& car : getAll()) {
        auto it = res.find(car.getManufacturer());
        if (it == res.end()) {
            res.insert(std::pair<string, int>(car.getManufacturer(), 1));
        }
        else {
            (*it).second++;
        }
    }
    return res;
}

void CarsService::emptyWashList() noexcept {
    carsToWash.empty();
    this->notifyAll();
}

int CarsService::sizeWashList() const noexcept {
    return carsToWash.size();
}

const vector<Car>& CarsService::getWashList() const noexcept {
    return this->carsToWash.getAll();
}

void CarsService::addToWashList(const string& regNumber) {
    Car car = carsRepo.findCar(Car(regNumber, "", "", ""));
    carsToWash.storeCar(car);
    this->notifyAll();
}

void CarsService::generateWashList(int number) {
    carsToWash.empty();
    vector<Car> copyRepo{ carsRepo.copy() };
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(copyRepo.begin(), copyRepo.end(), std::default_random_engine(seed));
    int counter{ 0 };
    while (counter != number && counter != carsRepo.size()) {
        carsToWash.storeCar(copyRepo.at(counter));
        counter++;
    }
    this->notifyAll();
}

void CarsService::exportWashListToFile(const string& filePath) const {
    ofstream out(filePath);
    if (!out.is_open()) {
        throw FileException("File could not be opened!\n");
    }
    string extension{ " " };
    for (size_t i = filePath.length() - 1; i > filePath.length() - 6; i--) {
        extension += filePath.at(i);
    }
    if (extension != " lmth.") {
        throw FileException("File is not an HTML file!\n");
    }
    for (const auto& car : this->getWashList()) {
        out << car;
    }
}

void CarsService::undo() {
    if (undoActions.empty()) {
        throw RepositoryException("No action to undo!\n");
    }
    Undo* action{ undoActions.back() };
    action->doUndo();
    undoActions.pop_back();
    delete action;
    this->notifyAll();
}

CarsService::~CarsService() {
    for (const auto& action : this->undoActions) {
        delete action;
    }
}