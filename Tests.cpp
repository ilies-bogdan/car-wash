#include "Tests.h"


void Tests::runAllTests() {
	std::cout << "Running tests..." << std::endl;
	runTestsList();
	runTestsDomain();
	runTestsValidation();
	runTestsCarsRepository();
	runTestsCarsService();
	std::cout << "All tests passed successfully!" << std::endl << std::endl;
}

void Tests::runTestsList() {
	List<Car> list;
	assert(list.size() == 0);
	Car car1{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	Car car2{ "B 63 USU", "Dacia", "Logan", "Sedan" };
	Car car3{ "MM 04 ROV", "Volkswagen", "Bora", "Sedan" };
	list.add(car1);
	list.add(car2);
	list.add(car3);
	assert(list.size() == 3);
	ListIterator<Car> it = list.begin();
	assert(it.get() == car1);
	assert(*it == car1);
	it.next();
	assert(it.get() == car2);
	list.remove(it);
	assert(list.size() == 2);
	assert(list.get(1) == car3);
	List<Car> other{ list };
	assert(other.size() == 2);
	other = list;
	assert(other.size() == 2);
	const ListIterator<Car> it2 = list.end();
	assert(!it2.valid());
	const ListIterator<Car> it3 = ListIterator<Car>(list, 1);
	assert(*it3 == car3);
}

void Tests::runTestsDomain() {
	testCreateCar();
	testEqualCars();
}

void Tests::testCreateCar() {
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	assert(car.getRegNumber() == "MM 05 KAX");
	assert(car.getManufacturer() == "Volkswagen");
	assert(car.getModel() == "Golf");
	assert(car.getType() == "Hatchback");
	car.setManufacturer("Dacia");
	car.setModel("Logan");
	car.setType("Sedan");
	assert(car.getManufacturer() == "Dacia");
	assert(car.getModel() == "Logan");
	assert(car.getType() == "Sedan");
	Car other{ car };
	assert(other.getRegNumber() == car.getRegNumber());
	Car another;
	another = car;
	assert(another == car);
	std::ostringstream os;
	os << car;
	assert(os.str() == "MM 05 KAX Dacia Logan Sedan\n");
	assert(car.toString() == "MM 05 KAX: Dacia Logan - Sedan");
}

void Tests::testEqualCars() {
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	Car eq{ "MM 05 KAX", "Dacia", "Logan", "Sedan" };
	assert(car == eq);
	Car notEq{ "MM 11 KAX", "Volkswagen", "Golf", "Hatchback" };
	assert(car != notEq);
}

void Tests::runTestsValidation() {
	testValidCar();
	testInvalidCar();
}

void Tests::testValidCar() {
	Car valCar{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	CarValidator carVal;
	carVal.validateCar(valCar);
	assert(true);
}

void Tests::testInvalidCar() {
	Car invalCar{ "", "", "", "" };
	CarValidator carVal;
	try {
		carVal.validateCar(invalCar);
		assert(false);
	}
	catch (const ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid registration number!\nInvalid manufacturer!\nInvalid model!\nInvalid type!\n");
	}
}

void Tests::runTestsCarsRepository() {
	testCreateCopyCarsRepository();
	testStoreFindGetAllCarsRepository();
	testDeleteCarsRepository();
	testUpdateCarsRepository();
}

void Tests::testCreateCopyCarsRepository() {
	string filePath{ "test_cars.txt" };
	std::ofstream out(filePath, std::ofstream::trunc);
	FileCarsRepository carsRepo{ filePath };
	// CarsRepository carsRepo;
	assert(carsRepo.size() == 0);
	carsRepo.storeCar(Car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" });
	vector<Car> copy{ carsRepo.copy() };
	assert(copy.size() == 1);
	copy.push_back(Car{ "MM 05 KAX", "Dacia", "Logan", "Sedan" });
	assert(copy.size() == 2);
	assert(carsRepo.size() == 1);
	carsRepo.empty();
	assert(carsRepo.size() == 0);
}

void Tests::testStoreFindGetAllCarsRepository() {
	string filePath{ "test_cars.txt" };
	std::ofstream out(filePath, std::ofstream::trunc);
	FileCarsRepository carsRepo{ filePath };
	// CarsRepository carsRepo;
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	carsRepo.storeCar(car);
	assert(carsRepo.size() == 1);
	try {
		carsRepo.storeCar(car);
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Car already existing!\n");
	}
	vector<Car> all{ carsRepo.getAll() };
	assert(all.at(0) == car);
	Car found{ carsRepo.findCar(car) };
	assert(found == car);
	Car nonexistent{ "", "", "", "" };
	try {
		carsRepo.findCar(nonexistent);
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
}

void Tests::testDeleteCarsRepository() {
	string filePath{ "test_cars.txt" };
	std::ofstream out(filePath, std::ofstream::trunc);
	FileCarsRepository carsRepo{ filePath };
	// CarsRepository carsRepo;
	Car car1{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	Car car2{ "B 63 USU", "Dacia", "Logan", "Sedan" };
	carsRepo.storeCar(car1);
	carsRepo.storeCar(car2);
	assert(carsRepo.size() == 2);
	carsRepo.deleteCar(car2);
	assert(carsRepo.size() == 1);
	try {
		carsRepo.deleteCar(car2);
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
}

void Tests::testUpdateCarsRepository() {
	string filePath{ "test_cars.txt" };
	std::ofstream out(filePath, std::ofstream::trunc);
	FileCarsRepository carsRepo{ filePath };
	// CarsRepository carsRepo;
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	carsRepo.storeCar(car);
	Car newCar{ "MM 05 KAX", "Dacia", "Logan", "Sedan" };
	carsRepo.updateCar(newCar);
	Car found = carsRepo.findCar(car);
	assert(found.getManufacturer() == newCar.getManufacturer());
	Car nonExistent{ "MM 11 KAX", "Volkswagen", "Golf", "Hatchback" };
	try {
		carsRepo.updateCar(nonExistent);
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
}

void Tests::runTestsCarsService() {
	testCreateCarsService();
	testStoreFindGetAllCarsService();
	testUpdateCarsService();
	testDeleteCarsService();
	testFilterReportCarsService();
	testSortCarsService();
	testCarsToWashService();
	testUndo();
}

void Tests::testCreateCarsService() const noexcept {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService const carsSrv{ carVal, carsRepo, carsToWash };
	assert(carsSrv.size() == 0);
}

void Tests::testStoreFindGetAllCarsService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	assert(carsSrv.size() == 1);
	vector<Car> all{ carsSrv.getAll() };
	assert(all.at(0) == car);
	try {
		carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Car already existing!\n");
	}
	try {
		carsSrv.storeCar("", "", "", "");
		assert(false);
	}
	catch (const ValidationException& ve) {
		assert(ve.getErrorMsg() == "Invalid registration number!\nInvalid manufacturer!\nInvalid model!\nInvalid type!\n");
	}
	Car found{ carsSrv.findCarByRegistrationNumber("MM 05 KAX") };
	assert(found == car);
	try {
		carsSrv.findCarByRegistrationNumber("");
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
}

void Tests::testDeleteCarsService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	assert(carsSrv.size() == 1);
	carsSrv.deleteCar("MM 05 KAX");
	assert(carsSrv.size() == 0);
	try {
		carsSrv.deleteCar("MM 05 KAX");
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
}

void Tests::testUpdateCarsService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	Car car{ "MM 05 KAX", "Volkswagen", "Golf", "Hatchback" };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	carsSrv.updateCar("MM 05 KAX", "Dacia", "Logan", "Sedan");
	Car found{ carsSrv.findCarByRegistrationNumber("MM 05 KAX") };
	assert(found == car);
	assert(found.getManufacturer() == "Dacia");
	assert(found.getModel() == "Logan");
	assert(found.getType() == "Sedan");
	carsSrv.updateCar("MM 05 KAX", "", "", "");
	found = carsSrv.findCarByRegistrationNumber("MM 05 KAX");
	assert(found == car);
	assert(found.getManufacturer() == "Dacia");
	assert(found.getModel() == "Logan");
	assert(found.getType() == "Sedan");
}

void Tests::testFilterReportCarsService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	carsSrv.storeCar("B 63 USU", "Dacia", "Logan", "Sedan");
	carsSrv.storeCar("MM 04 ROV", "Volkswagen", "Bora", "Sedan");
	vector<Car> filtered{ carsSrv.filterByManufacturer("wag") };
	assert(filtered.size() == 2);
	filtered = carsSrv.filterByManufacturer("ac");
	assert(filtered.size() == 1);
	filtered = carsSrv.filterByManufacturer("bmasdft");
	assert(filtered.size() == 0);
	filtered = carsSrv.filterByType("ch");
	assert(filtered.size() == 1);
	filtered = carsSrv.filterByType("bmasdft");
	assert(filtered.size() == 0);
	filtered = carsSrv.filterByType("eda");
	assert(filtered.size() == 2);
	map<string, int> models { carsSrv.reportManufacturerCount() };
	assert(models.at("Volkswagen") == 2);
	assert(models.at("Dacia") == 1);
}

void Tests::testSortCarsService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	carsSrv.storeCar("B 63 USU", "Dacia", "Logan", "Sedan");
	carsSrv.storeCar("MM 04 ROV", "Volkswagen", "Bora", "Sedan");
	vector<Car> sorted{ carsSrv.sortByRegistrationNumber() };
	assert(sorted.size() == 3);
	assert(sorted.at(0).getRegNumber() == "B 63 USU");
	assert(sorted.at(1).getRegNumber() == "MM 04 ROV");
	assert(sorted.at(2).getRegNumber() == "MM 05 KAX");
	sorted = carsSrv.sortByType();
	assert(sorted.size() == 3);
	assert(sorted.at(0).getRegNumber() == "MM 04 ROV" || sorted.at(1).getRegNumber() == "MM 04 ROV");
	assert(sorted.at(1).getRegNumber() == "B 63 USU" || sorted.at(0).getRegNumber() == "B 63 USU");
	assert(sorted.at(2).getRegNumber() == "MM 05 KAX");
	sorted = carsSrv.sortByManufacturerModel();
	assert(sorted.size() == 3);
	assert(sorted.at(0).getRegNumber() == "B 63 USU");
	assert(sorted.at(1).getRegNumber() == "MM 04 ROV");
	assert(sorted.at(2).getRegNumber() == "MM 05 KAX");
}

void Tests::testCarsToWashService() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	carsSrv.storeCar("B 63 USU", "Dacia", "Logan", "Sedan");
	carsSrv.storeCar("MM 04 ROV", "Volkswagen", "Bora", "Sedan");
	assert(carsSrv.sizeWashList() == 0);
	carsSrv.addToWashList("MM 05 KAX");
	carsSrv.addToWashList("B 63 USU");
	vector<Car> all = carsSrv.getWashList();
	assert(all.size() == 2);
	assert(carsSrv.sizeWashList() == 2);
	try {
		carsSrv.addToWashList("MM 05 KAX");
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Car already existing!\n");
	}
	try {
		carsSrv.addToWashList("CJ 69 ADS");
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "Nonexistent car!\n");
	}
	carsSrv.emptyWashList();
	assert(carsToWash.size() == 0);
	carsSrv.generateWashList(10);
	assert(carsSrv.sizeWashList() == 3);
	assert(carsSrv.getWashList().at(0).getRegNumber() == "MM 05 KAX" || carsSrv.getWashList().at(0).getRegNumber() == "B 63 USU" || carsSrv.getWashList().at(0).getRegNumber() == "MM 04 ROV");
	string fileName{ "test_export.html" };
	carsSrv.exportWashListToFile(fileName);
	try {
		carsSrv.exportWashListToFile("test_export.txt");
		assert(false);
	}
	catch (const FileException& fe) {
		assert(fe.getErrorMsg() == "File is not an HTML file!\n");
	}
}

void Tests::testUndo() {
	CarValidator carVal;
	CarsRepository carsRepo;
	CarsRepository carsToWash;
	CarsService carsSrv{ carVal, carsRepo, carsToWash };
	try {
		carsSrv.undo();
		assert(false);
	}
	catch (const RepositoryException& re) {
		assert(re.getErrorMsg() == "No action to undo!\n");
	}
	carsSrv.storeCar("MM 05 KAX", "Volkswagen", "Golf", "Hatchback");
	carsSrv.storeCar("B 63 USU", "Dacia", "Logan", "Sedan");
	carsSrv.storeCar("MM 04 ROV", "Volkswagen", "Bora", "Sedan");
	assert(carsSrv.size() == 3);
	carsSrv.undo();
	assert(carsSrv.size() == 2);
	carsSrv.deleteCar("MM 05 KAX");
	assert(carsSrv.size() == 1);
	carsSrv.undo();
	assert(carsRepo.size() == 2);
	assert(carsRepo.getAll().at(1).getRegNumber() == "MM 05 KAX");
	carsSrv.updateCar("MM 05 KAX", "Dacia", "Logan", "Sedan");
	assert(carsRepo.getAll().at(1).getManufacturer() == "Dacia");
	carsSrv.undo();
	assert(carsRepo.getAll().at(1).getManufacturer() == "Volkswagen");
}