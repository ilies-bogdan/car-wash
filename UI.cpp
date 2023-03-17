/*
* UI.cpp
* UI class implementation
*/

#include "UI.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;


void Console::showMenu() {
	cout << "1. Store car" << endl;
	cout << "2. Find car" << endl;
	cout << "3. Delete car" << endl;
	cout << "4. Update car" << endl;
	cout << "5. Show all cars" << endl;
	cout << "6. Filter" << endl;
	cout << "7. Sort" << endl;
	cout << "8. Report manufacturer" << endl;
	cout << "9. Wash list" << endl;
	cout << "U - Undo" << endl;
	cout << "Press X to exit" << endl;
	cout << "Cars to wash: " << carsSrv.sizeWashList() << endl;
	cout << endl;
}

void Console::uiStoreCar() {
	cout << "Registration number: ";
	string regNumber;
	getline(cin, regNumber, '\n');
	cout << "Manufacturer: ";
	string manufacturer;
	getline(cin, manufacturer, '\n');
	cout << "Model: ";
	string model;
	getline(cin, model, '\n');
	cout << "Type: ";
	string type;
	getline(cin, type, '\n');
	this->carsSrv.storeCar(regNumber, manufacturer, model, type);
	cout << "Car stored successfully!" << endl << endl;
}

void Console::uiFindCar() {
	cout << "Registration number of the car: ";
	string regNumber;
	getline(cin, regNumber, '\n');
	Car found = this->carsSrv.findCarByRegistrationNumber(regNumber);
	cout << found.getRegNumber() + ": " + found.getManufacturer() + "-" + found.getModel() + ", " + found.getType() << endl << endl;
}

void Console::uiDeleteCar() {
	cout << "Registration number of the car: ";
	string regNumber;
	getline(cin, regNumber, '\n');
	this->carsSrv.deleteCar(regNumber);
	cout << "Car deleted successfully!" << endl << endl;
}

void Console::uiUpdateCar() {
	cout << "Registration number of the car: ";
	string regNumber;
	getline(cin, regNumber, '\n');
	cout << "Leave empty to keep the old fields..." << endl;
	cout << "New manufacturer: ";
	string newManufacturer;
	getline(cin, newManufacturer, '\n');
	cout << "New model: ";
	string newModel;
	getline(cin, newModel, '\n');
	cout << "New type: ";
	string newType;
	getline(cin, newType, '\n');
	this->carsSrv.updateCar(regNumber, newManufacturer, newModel, newType);
	cout << "Car updated successfully!" << endl << endl;
}

void Console::uiPrintCars(vector<Car> cars) {
	for (const auto& car : cars) {
		cout << car.getRegNumber() + ": " + car.getManufacturer() + "-" + car.getModel() + ", " + car.getType() << endl;
	}
	cout << endl;
}

void Console::showFilterMenu() {
	cout << "1. Filter by manufacturer" << endl;
	cout << "2. Filter by type" << endl;
}

void Console::uiFilter() {
	showFilterMenu();
	string cmd;
	getline(cin, cmd, '\n');
	if (cmd == "1") {
		uiFilterByManufacturer();
	}
	else if (cmd == "2") {
		uiFilterByType();
	}
	else {
		cout << "Invalid option!" << endl << endl;
	}
}

void Console::uiFilterByManufacturer() {
	cout << "Manufacturer to filter by: ";
	string manufacturer;
	getline(cin, manufacturer, '\n');
	vector<Car> filtered = this->carsSrv.filterByManufacturer(manufacturer);
	uiPrintCars(filtered);
}

void Console::uiFilterByType() {
	cout << "Type to filter by: ";
	string type;
	getline(cin, type, '\n');
	vector<Car> filtered{ this->carsSrv.filterByType(type) };
	uiPrintCars(filtered);
}

void Console::showSortMenu() {
	cout << "1. Sort by registration number" << endl;
	cout << "2. Sort by type" << endl;
	cout << "3. Sort by manufacturer and model" << endl;
}

void Console::uiSort() {
	showSortMenu();
	string cmd;
	getline(cin, cmd, '\n');
	if (cmd == "1") {
		uiSortByRegistrationNumber();
	}
	else if (cmd == "2") {
		uiSortByType();
	}
	else if (cmd == "3") {
		uiSortByManufacturerModel();
	}
	else {
		cout << "Invalid option!" << endl << endl;
	}
}

void Console::uiSortByRegistrationNumber() {
	vector<Car> sorted = this->carsSrv.sortByRegistrationNumber();
	uiPrintCars(sorted);
}

void Console::uiSortByType() {
	vector<Car> sorted = this->carsSrv.sortByType();
	uiPrintCars(sorted);
}

void Console::uiSortByManufacturerModel() {
	vector<Car> sorted{ this->carsSrv.sortByManufacturerModel() };
	uiPrintCars(sorted);
}

void Console::uiReportManufacturer() {
	map<string, int> res{ carsSrv.reportManufacturerCount() };
	for (const auto& entry : res) {
		cout << entry.first << ": " << entry.second << endl;
	}
	cout << endl;
}

void Console::showWashMenu() {
	cout << "1. Empty wash list" << endl;
	cout << "2. Add car to wash list" << endl;
	cout << "3. Generate wash list" << endl;
	cout << "4. Show wash list" << endl;
	cout << "5. Export to HTML file" << endl;
}

void Console::uiWashList() {
	showWashMenu();
	string cmd;
	getline(cin, cmd, '\n');
	if (cmd == "1") {
		uiEmptyWashList();
	}
	else if (cmd == "2") {
		uiAddCarToWashList();
	}
	else if (cmd == "3") {
		uiGenerateWashList();
	}
	else if (cmd == "4") {
		uiPrintCars(carsSrv.getWashList());
	}
	else if (cmd == "5") {
		uiExportWashListToFile();
	}
	else {
		cout << "Invalid option!" << endl << endl;
	}
}

void Console::uiEmptyWashList() noexcept {
	carsSrv.emptyWashList();
}

void Console::uiAddCarToWashList() {
	cout << "Registration number of the car: ";
	string regNumber;
	getline(cin, regNumber, '\n');
	carsSrv.addToWashList(regNumber);
}

void Console::uiGenerateWashList() {
	cout << "Number of cars: ";
	int number;
	cin >> number;
	if (number < 0) {
		cout << "Invalid value!" << endl;
		return;
	}
	carsSrv.generateWashList(number);
}

void Console::uiExportWashListToFile() {
	cout << "HTML file: ";
	string filePath;
	cin >> filePath;
	this->carsSrv.exportWashListToFile(filePath);
	cout << "Wash list exported successfully!" << endl << endl;
}

void Console::uiUndo() {
	this->carsSrv.undo();
}

void Console::run() {
	while (true) {
		showMenu();
		cout << ">>>";
		string cmd;
		getline(cin, cmd, '\n');
		try {
			if (cmd == "x" || cmd == "X") {
				cout << "Closing . . .";
				return;
			}
			if (cmd == "") {
				continue;
			}
			else if (cmd == "1") {
				uiStoreCar();
			}
			else if (cmd == "2") {
				uiFindCar();
			}
			else if (cmd == "3") {
				uiDeleteCar();
			}
			else if (cmd == "4") {
				uiUpdateCar();
			}
			else if (cmd == "5") {
				uiPrintCars(carsSrv.getAll());
			}
			else if (cmd == "6") {
				uiFilter();
			}
			else if (cmd == "7") {
				uiSort();
			}
			else if (cmd == "8") {
				uiReportManufacturer();
			}
			else if (cmd == "9") {
				uiWashList();
			}
			else if (cmd == "u" || cmd == "U") {
				uiUndo();
			}
			else {
				cout << "Invalid command!" << endl << endl;
			}
		}
		catch (const ValidationException& ve) {
			cout << "ValidationError:\n" + ve.getErrorMsg() << endl;
		}
		catch (const RepositoryException& re) {
			cout << "RepositoryError:\n" + re.getErrorMsg() << endl;
		}
		catch (const FileException& fe) {
			cout << "FileError:\n" + fe.getErrorMsg() << endl;
		} 
	}
}