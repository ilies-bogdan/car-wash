#pragma once

#include <QAbstractListModel>
#include <vector>
#include "Car.h"

class MyListModel : public QAbstractListModel {
	std::vector<Car> cars;
public:
	MyListModel(const std::vector<Car>& cars) : cars{ cars } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cars.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto regNumber = cars[index.row()].getRegNumber();
			return QString::fromStdString(regNumber);
		}
		if (role == Qt::UserRole) {
			auto regNumber = cars[index.row()].getRegNumber();
			return QString::fromStdString(regNumber);
		}
		return QVariant{};
	}

	void setCars(const std::vector<Car>& cars) {
		this->cars = cars;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), 0);
		emit dataChanged(topLeft, bottomR);
	}
};