#include "FileCarsRepository.h"


void FileCarsRepository::loadFromFile() {
	std::ifstream in(this->filePath);
	if (!in.is_open()) {
		throw FileException("File could not be opened!\n");
	}
	carsRepo.clear();
	while (!in.eof()) {
		string entry;
		getline(in, entry, '\n');
		if (!entry.empty()) {
			size_t pos{ entry.find(",") };
			string regNumber{ entry.substr(0, pos) };
			entry.erase(0, pos + 1);
			pos = entry.find(",");
			string manufacturer{ entry.substr(0, pos) };
			entry.erase(0, pos + 1);
			pos = entry.find(",");
			string model{ entry.substr(0, pos) };
			entry.erase(0, pos + 1);
			string type{ entry };
			Car car{ regNumber, manufacturer, model, type };
			CarsRepository::storeCar(car);
		}
	}
	in.close();
}

void FileCarsRepository::writeToFile() {
	std::ofstream out(filePath);
	if (!out.is_open()) {
		throw FileException("File could not be opened!\n");
	}
	for (const auto& car : CarsRepository::getAll()) {
		out << car.getRegNumber() << ",";
		out << car.getManufacturer() << ",";
		out << car.getModel() << ",";
		out << car.getType() << std::endl;
	}
	out.close();
}