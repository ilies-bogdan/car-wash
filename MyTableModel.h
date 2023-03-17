#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "Car.h"

class MyTableModel : public QAbstractTableModel {
	std::vector<Car> cars;
public:
	MyTableModel(const std::vector<Car>& cars) : cars{ cars } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cars.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			Car car = cars[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(car.getRegNumber());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(car.getManufacturer());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(car.getModel());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(car.getType());
			}
		}
		return QVariant{};
	}

	void setCars(const std::vector<Car>& cars) {
		this->cars = cars;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};