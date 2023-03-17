/*
* GUI.h
* GUI class
*/

#pragma once

#include <qwidget.h>
#include <qlistwidget.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qpainter.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include "CarsService.h"
#include "Observer.h"
#include "MyListModel.h"


class GUI : public QWidget, public Observer {
private:
	CarsService& carsSrv;
	// QListWidget* carsList;
	MyListModel* carsList;
	QListView* carsListView = new QListView();
	QLabel* regNumberLabel;
	QLabel* manufacturerLabel;
	QLabel* modelLabel;
	QLabel* typeLabel;
	QLineEdit* regNumberText;
	QLineEdit* manufacturerText;
	QLineEdit* modelText;
	QLineEdit* typeText;
	QPushButton* addButton;
	QPushButton* findButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* filterByTypeButton;
	QPushButton* filterByManufacturerButton;
	QPushButton* sortByRegNumberButton;
	QPushButton* sortByTypeButton;
	QPushButton* sortByManModelButton;
	QPushButton* reportManufacturerButton;
	QPushButton* undoButton;
	QVBoxLayout* manufLayout;
	vector<QPushButton*> manufButtons;
	QPushButton* washListButton;
	QPushButton* washListReadOnlyButton = new QPushButton("Wash List Read Only");

	QPushButton* emptyWashListButton;
	QPushButton* washListAddButton;
	QLineEdit* washListRegNumberText;
	QPushButton* generateCarsButton;
	QLineEdit* generateCarsText;

	void storeCar();
	void findCar();
	void deleteCar();
	void updateCar();
	void filterByManufacturer();
	void filterByType();
	void reportManufacturer();
	void updateManufacturerButtons();

	void update() override;
protected:
	virtual void initGUI();
	virtual void connectSignalsSlots();
	virtual void refreshCarsList(const vector<Car>&);
public:
	GUI(CarsService& carsSrv) : carsSrv{ carsSrv } {
		this->initGUI();
		carsList = new MyListModel(this->carsSrv.getAll());
		carsListView->setModel(carsList);
		this->connectSignalsSlots();
		this->refreshCarsList(carsSrv.getAll());
		this->carsSrv.addObserver(this);
	}
	~GUI();
};

class WashListGUI : public GUI {
private:
	CarsService& carsSrv;
	QWidget* washListWindow;
	QTableWidget* washTable;
	QTableView* washTableView = new QTableView();
	QPushButton* refreshWashListButton;
	QPushButton* emptyWashListButton;
	QLabel* washListRegNumberLabel;
	QLineEdit* washListRegNumberText;
	QPushButton* washListAddButton;
	QLabel* generateCarsLabel;
	QLineEdit* generateCarsText;
	QPushButton* generateCarsButton;
	QLabel* exportWashListLabel;
	QLineEdit* exportWashListText;
	QPushButton* exportWashListButton;

	void initGUI() override;
	void connectSignalsSlots() override;
	void refreshCarsList(const vector<Car>&) override;

	void update() override;
public:
	WashListGUI(CarsService& carsSrv) : GUI{ carsSrv }, carsSrv{ carsSrv } {
		this->initGUI();
		this->connectSignalsSlots();
		this->refreshCarsList(carsSrv.getWashList());
		this->carsSrv.addObserver(this);
	}
	~WashListGUI();
};

class WashListReadOnlyGUI : public QWidget, public Observer {
private:
	CarsService& carsSrv;
	void paintEvent(QPaintEvent* ev) override;

	void update() override;
public:
	WashListReadOnlyGUI(CarsService& carsSrv) : carsSrv{ carsSrv } {
		this->carsSrv.addObserver(this);
		this->setMinimumHeight(600);
		this->setMinimumWidth(900);
		this->show();
	}
	~WashListReadOnlyGUI();
};