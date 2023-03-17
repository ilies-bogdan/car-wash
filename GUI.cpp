/*
* GUI.cpp
* GUI class implementation
*/

#include "GUI.h"


void GUI::initGUI() {
	QHBoxLayout* mainLayout = new QHBoxLayout();

	// List details (Left side)
	QWidget* listWidget = new QWidget();
	QVBoxLayout* listLayout = new QVBoxLayout();
	// carsList = new QListWidget();
	listLayout->addWidget(carsListView);

	// Filter buttons
	QWidget* filterWidget = new QWidget();
	QHBoxLayout* filterLayout = new QHBoxLayout();
	filterWidget->setLayout(filterLayout);
	filterByManufacturerButton = new QPushButton("Filter by Manufacturer");
	filterLayout->addStretch();
	filterLayout->addWidget(filterByManufacturerButton);
	filterLayout->addStretch();
	filterByTypeButton = new QPushButton("Filter by Type");
	filterLayout->addWidget(filterByTypeButton);
	filterLayout->addStretch();
	listLayout->addWidget(filterWidget);

	// Sort buttons
	QWidget* sortWidget = new QWidget();
	QHBoxLayout* sortLayout = new QHBoxLayout();
	sortWidget->setLayout(sortLayout);
	sortByRegNumberButton = new QPushButton("Sort by Registration Number");
	sortLayout->addStretch();
	sortLayout->addWidget(sortByRegNumberButton);
	sortByTypeButton = new QPushButton("Sort by Type");
	sortLayout->addStretch();
	sortLayout->addWidget(sortByTypeButton);
	sortByManModelButton = new QPushButton("Sort by Manufacturer and Model");
	sortLayout->addStretch();
	sortLayout->addWidget(sortByManModelButton);
	listLayout->addWidget(sortWidget);

	// Report buttons
	QWidget* reportWidget = new QWidget();
	QHBoxLayout* reportLayout = new QHBoxLayout();
	reportWidget->setLayout(reportLayout);
	reportLayout->addStretch();
	reportManufacturerButton = new QPushButton("Report Manufacturer");
	reportLayout->addWidget(reportManufacturerButton);
	reportLayout->addStretch();
	listLayout->addWidget(reportWidget);

	mainLayout->addLayout(listLayout);

	// Car details (Right side)
	QWidget* carWidget = new QWidget();
	QFormLayout* carLayout = new QFormLayout();
	carWidget->setLayout(carLayout);
	regNumberLabel = new QLabel("Registration number: ");
	manufacturerLabel = new QLabel("Manufacturer: ");
	modelLabel = new QLabel("Model: ");
	typeLabel = new QLabel("Type: ");
	regNumberText = new QLineEdit();
	carLayout->addRow(regNumberLabel, regNumberText);
	manufacturerText = new QLineEdit();
	carLayout->addRow(manufacturerLabel, manufacturerText);
	modelText = new QLineEdit();
	carLayout->addRow(modelLabel, modelText);
	typeText = new QLineEdit();
	carLayout->addRow(typeLabel, typeText);

	// Add button with stretch
	QWidget* addWidget = new QWidget();
	QHBoxLayout* addLayout = new QHBoxLayout();
	addLayout->addStretch();
	addButton = new QPushButton("Add");
	addLayout->addWidget(addButton);
	addLayout->addStretch();
	addWidget->setLayout(addLayout);
	carLayout->addRow(addWidget);

	// Find, Delete, Update buttons
	QWidget* FDUWidget = new QWidget();
	QHBoxLayout* FDULayout = new QHBoxLayout();
	findButton = new QPushButton("Find");
	FDULayout->addWidget(findButton);
	deleteButton = new QPushButton("Delete");
	FDULayout->addWidget(deleteButton);
	updateButton = new QPushButton("Update");
	FDULayout->addWidget(updateButton);
	FDUWidget->setLayout(FDULayout);
	carLayout->addRow(FDUWidget);

	// Undo button
	QWidget* undoWidget = new QWidget();
	QHBoxLayout* undoLayout = new QHBoxLayout();
	undoWidget->setLayout(undoLayout);
	undoLayout->addStretch();
	undoButton = new QPushButton("Undo");
	undoLayout->addWidget(undoButton);
	undoLayout->addStretch();
	carLayout->addRow(undoWidget);

	// Wash list button
	QWidget* washListWidget = new QWidget();
	QVBoxLayout* washListLayout = new QVBoxLayout();
	washListWidget->setLayout(washListLayout);
	washListLabel = new QLabel("Wash List Menu");
	washListLayout->addWidget(washListLabel);
	// washListLayout->addStretch();
	washListButton = new QPushButton("Wash List");
	washListLayout->addWidget(washListButton);

	emptyWashListButton = new QPushButton("Empty Wash List");
	washListLayout->addWidget(emptyWashListButton);
	// washListLayout->addStretch();
	// carLayout->addRow(washListWidget);
	/*QWidget* washListReadOnlyWidget = new QWidget();
	QHBoxLayout* washListReadOnlyLayout = new QHBoxLayout();
	washListReadOnlyWidget->setLayout(washListReadOnlyLayout);
	washListReadOnlyLayout->addStretch();
	washListReadOnlyLayout->addWidget(washListReadOnlyButton);
	washListReadOnlyLayout->addStretch();
	carLayout->addRow(washListReadOnlyWidget);*/

	QWidget* editWashListWidget = new QWidget();
	QHBoxLayout* editWashListLayout = new QHBoxLayout();
	editWashListWidget->setLayout(editWashListLayout);

	QWidget* addWashListWidget = new QWidget();
	QVBoxLayout* addWashListLayout = new QVBoxLayout();
	addWashListWidget->setLayout(addWashListLayout);
	QLabel* washListRegNumberLabel = new QLabel("Registration number:");
	addWashListLayout->addWidget(washListRegNumberLabel);
	washListRegNumberText = new QLineEdit();
	addWashListLayout->addWidget(washListRegNumberText);
	washListAddButton = new QPushButton("Add to Wash List");
	addWashListLayout->addWidget(washListAddButton);
	editWashListLayout->addWidget(addWashListWidget);

	QWidget* generateCarsWidget = new QWidget();
	QVBoxLayout* generateCarsLayout = new QVBoxLayout();
	generateCarsWidget->setLayout(generateCarsLayout);
	QLabel* generateCarsLabel = new QLabel("Number of cars to generate:");
	generateCarsLayout->addWidget(generateCarsLabel);
	generateCarsText = new QLineEdit();
	generateCarsLayout->addWidget(generateCarsText);
	generateCarsButton = new QPushButton("Generate Wash List");
	generateCarsLayout->addWidget(generateCarsButton);
	editWashListLayout->addWidget(generateCarsWidget);

	washListLayout->addWidget(editWashListWidget);

	carLayout->addRow(washListWidget);

	mainLayout->addWidget(carWidget);

	// Manufacturer buttons
	QWidget* manufWidget = new QWidget();
	manufLayout = new QVBoxLayout();
	manufWidget->setLayout(manufLayout);
	for (const auto& entry : carsSrv.reportManufacturerCount()) {
		QPushButton* button = new QPushButton(QString::fromStdString(entry.first));
		manufButtons.push_back(button);
		manufLayout->addWidget(button);
	}
	mainLayout->addWidget(manufWidget);

	this->setLayout(mainLayout);
}

void GUI::connectSignalsSlots() {
	/*QObject::connect(carsList, &QListWidget::itemSelectionChanged, [&]() {
		auto selected{ carsList->selectedItems() };
		if (selected.isEmpty()) {
			regNumberText->setText("");
			manufacturerText->setText("");
			modelText->setText("");
			typeText->setText("");
		}
		else {
			auto selectedRegNumber{ selected.at(0) };
			auto regNumber{ selectedRegNumber->text().toStdString() };
			auto car{ carsSrv.findCarByRegistrationNumber(regNumber) };
			regNumberText->setText(QString::fromStdString(car.getRegNumber()));
			manufacturerText->setText(QString::fromStdString(car.getManufacturer()));
			modelText->setText(QString::fromStdString(car.getModel()));
			typeText->setText(QString::fromStdString(car.getType()));
		}
		});*/
	QObject::connect(carsListView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (carsListView->selectionModel()->selectedIndexes().isEmpty()) {
			return;
		}
		auto regNumber{ carsListView->selectionModel()->selectedIndexes().at(0).data().toString() };
		auto car{ carsSrv.findCarByRegistrationNumber(regNumber.toStdString()) };
		regNumberText->setText(QString::fromStdString(car.getRegNumber()));
		manufacturerText->setText(QString::fromStdString(car.getManufacturer()));
		modelText->setText(QString::fromStdString(car.getModel()));
		typeText->setText(QString::fromStdString(car.getType()));
		});

	QObject::connect(addButton, &QPushButton::clicked, this, &GUI::storeCar);
	QObject::connect(findButton, &QPushButton::clicked, this, &GUI::findCar);
	QObject::connect(deleteButton, &QPushButton::clicked, this, &GUI::deleteCar);
	QObject::connect(updateButton, &QPushButton::clicked, this, &GUI::updateCar);
	QObject::connect(filterByManufacturerButton, &QPushButton::clicked, this, &GUI::filterByManufacturer);
	QObject::connect(filterByTypeButton, &QPushButton::clicked, this, &GUI::filterByType);
	QObject::connect(sortByRegNumberButton, &QPushButton::clicked, this, [&]() {
		refreshCarsList(carsSrv.sortByRegistrationNumber());
		});
	QObject::connect(sortByTypeButton, &QPushButton::clicked, this, [&]() {
		refreshCarsList(carsSrv.sortByType());
		});
	QObject::connect(sortByManModelButton, &QPushButton::clicked, this, [&]() {
		refreshCarsList(carsSrv.sortByManufacturerModel());
		});
	QObject::connect(reportManufacturerButton, &QPushButton::clicked, this, &GUI::reportManufacturer);
	QObject::connect(undoButton, &QPushButton::clicked, this, [&]() {
		try {
			carsSrv.undo();
			updateManufacturerButtons();
			refreshCarsList(carsSrv.getAll());
		}
		catch (const RepositoryException& re) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
		}
		});

	for (auto button : manufButtons) {
		QObject::connect(button, &QPushButton::clicked, this, [=]() {
			for (const auto& entry : carsSrv.reportManufacturerCount()) {
				if (entry.first == button->text().toStdString()) {
					QMessageBox::information(this, "Manufacturer Count", QString::number(entry.second));
				}
			}
			});
	}
	QObject::connect(washListButton, &QPushButton::clicked, this, [&]() {
		WashListGUI* washList = new WashListGUI{ carsSrv };
		});
	QObject::connect(emptyWashListButton, &QPushButton::clicked, this, [&]() {
		carsSrv.emptyWashList();
		});
	QObject::connect(washListAddButton, &QPushButton::clicked, this, [&]() {
		try {
			carsSrv.addToWashList(washListRegNumberText->text().toStdString());
		}
		catch (const RepositoryException& re) {
			QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
		}
		});
QObject:connect(generateCarsButton, &QPushButton::clicked, this, [&]() {
	carsSrv.generateWashList(generateCarsText->text().toInt());
	});
/*QObject::connect(washListReadOnlyButton, &QPushButton::clicked, this, [&]() {
	WashListReadOnlyGUI* washListReadOnly = new WashListReadOnlyGUI{ carsSrv };
	});*/
}

void GUI::refreshCarsList(const vector<Car>& cars) {
	/*carsList->clear();
	for (const auto& car : cars) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(car.getRegNumber()));
		carsList->addItem(item);
	}*/
	carsList->setCars(cars);
}

GUI::~GUI() {
	carsSrv.removeObserver(this);
}

void GUI::updateManufacturerButtons() {
	// check if manufacturers match buttons (delete, update)
	auto manufacturerReport{ carsSrv.reportManufacturerCount() };
	for (auto it = manufButtons.begin(); it < manufButtons.end(); it++) {
		QPushButton* button = *it;
		if (manufacturerReport.find((*it)->text().toStdString()) == manufacturerReport.end()) {
			manufButtons.erase(it);
			delete button;
			break;
		}
	}
	// check if buttons match manufacturers (store)
	for (const auto& entry : manufacturerReport) {
		auto manufacturer{ entry.first };
		auto count{ entry.second };
		bool found{ false };
		for (auto it = manufButtons.begin(); it < manufButtons.end(); it++) {
			if (manufacturer == (*it)->text().toStdString()) {
				found = true;
				break;
			}
		}
		if (!found) {
			QPushButton* button = new QPushButton(QString::fromStdString(manufacturer));
			manufButtons.push_back(button);
			manufLayout->addWidget(button);
			QObject::connect(button, &QPushButton::clicked, this, [=]() {
				for (const auto& pair : carsSrv.reportManufacturerCount()) {
					if (pair.first == button->text().toStdString()) {
						QMessageBox::information(this, "Manufacturer Count", QString::number(pair.second));
					}
				}
				});
		}
	}
}

void GUI::update() {
	this->refreshCarsList(carsSrv.getAll());
}

void GUI::storeCar() {
	try {
		carsSrv.storeCar(regNumberText->text().toStdString(), manufacturerText->text().toStdString(), modelText->text().toStdString(), typeText->text().toStdString());
		updateManufacturerButtons();
		refreshCarsList(carsSrv.getAll());
		regNumberText->setText("");
		manufacturerText->setText("");
		modelText->setText("");
		typeText->setText("");
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Validation Error", QString::fromStdString(ve.getErrorMsg()));
	}
	catch (const RepositoryException& re) {
		QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
	}
}

void GUI::findCar() {
	try {
		Car car{ carsSrv.findCarByRegistrationNumber(regNumberText->text().toStdString()) };
		QMessageBox::information(this, "Found Car", QString::fromStdString(car.toString()));
	}
	catch (const RepositoryException& re) {
		QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
	}
}

void GUI::deleteCar() {
	try {
		carsSrv.deleteCar(regNumberText->text().toStdString());
		updateManufacturerButtons();
		refreshCarsList(carsSrv.getAll());
	}
	catch (const RepositoryException& re) {
		QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
	}
}

void GUI::updateCar() {
	try {
		carsSrv.updateCar(regNumberText->text().toStdString(), manufacturerText->text().toStdString(), modelText->text().toStdString(), typeText->text().toStdString());
		updateManufacturerButtons();
		refreshCarsList(carsSrv.getAll());
		regNumberText->setText("");
		manufacturerText->setText("");
		modelText->setText("");
		typeText->setText("");
	}
	catch (const ValidationException& ve) {
		QMessageBox::warning(this, "Validation Error", QString::fromStdString(ve.getErrorMsg()));
	}
	catch (const RepositoryException& re) {
		QMessageBox::warning(this, "Repository Error", QString::fromStdString(re.getErrorMsg()));
	}
}

void GUI::filterByManufacturer() {
	QWidget* window = new QWidget();
	QVBoxLayout* windowLayout = new QVBoxLayout();
	window->setLayout(windowLayout);
	QWidget* substring = new QWidget();
	QHBoxLayout* substringLayout = new QHBoxLayout();
	substring->setLayout(substringLayout);
	QLabel* substringLabel = new QLabel("Manufacturer to filter by: ");
	substringLayout->addWidget(substringLabel);
	QLineEdit* substringText = new QLineEdit();
	substringLayout->addWidget(substringText);
	QPushButton* okButton = new QPushButton("Ok");
	windowLayout->addWidget(substring);
	windowLayout->addWidget(okButton);
	window->show();
	QObject::connect(okButton, &QPushButton::clicked, this, [=]() {
		QWidget* filtered = new QWidget();
		QHBoxLayout* filteredLayout = new QHBoxLayout();
		filtered->setLayout(filteredLayout);
		QListWidget* filteredItems = new QListWidget();
		filteredLayout->addWidget(filteredItems);
		for (const auto& car : carsSrv.filterByManufacturer(substringText->text().toStdString())) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(car.toString()));
			filteredItems->addItem(item);
		}
		filtered->show();
		delete window;
		});
}

void GUI::filterByType() {
	QWidget* window = new QWidget();
	QVBoxLayout* windowLayout = new QVBoxLayout();
	window->setLayout(windowLayout);
	QWidget* substring = new QWidget();
	QHBoxLayout* substringLayout = new QHBoxLayout();
	substring->setLayout(substringLayout);
	QLabel* substringLabel = new QLabel("Type to filter by:");
	substringLayout->addWidget(substringLabel);
	QLineEdit* substringText = new QLineEdit();
	substringLayout->addWidget(substringText);
	windowLayout->addWidget(substring);
	QPushButton* okButton = new QPushButton("Ok");
	windowLayout->addWidget(okButton);
	window->show();
	QObject::connect(okButton, &QPushButton::clicked, this, [=]() {
		QWidget* filtered = new QWidget();
		QHBoxLayout* filteredLayout = new QHBoxLayout();
		filtered->setLayout(filteredLayout);
		QListWidget* filteredItems = new QListWidget();
		filteredLayout->addWidget(filteredItems);
		for (const auto& car : carsSrv.filterByType(substringText->text().toStdString())) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(car.toString()));
			filteredItems->addItem(item);
		}
		filtered->show();
		delete window;
		});
}

void GUI::reportManufacturer() {
	QWidget* window = new QWidget();
	QHBoxLayout* windowLayout = new QHBoxLayout();
	window->setLayout(windowLayout);
	QListWidget* report = new QListWidget();
	for (const auto& entry : carsSrv.reportManufacturerCount()) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(entry.first) + ": " + QString::number(entry.second));
		report->addItem(item);
	}
	report->show();
}

void WashListGUI::initGUI() {
	washListWindow = new QWidget();
	QHBoxLayout* washListLayout = new QHBoxLayout();
	washListWindow->setLayout(washListLayout);
	washListWindow->setMinimumHeight(600);
	washListWindow->setMinimumWidth(1000);

	// List Widget
	QWidget* listWidget = new QWidget();
	QVBoxLayout* listLayout = new QVBoxLayout();
	listWidget->setLayout(listLayout);
	washTable = new QTableWidget{ carsSrv.sizeWashList(), 4 };
	QStringList headers;
	headers << "Registration number" << "Manufacturer" << "Model" << "Type";
	washTable->setHorizontalHeaderLabels(headers);
	washTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	listLayout->addWidget(washTable);
	refreshWashListButton = new QPushButton("Refresh");
	listLayout->addWidget(refreshWashListButton);
	washListLayout->addWidget(listWidget);

	// Edit Wash List Widget
	QWidget* editWashListWidget = new QWidget();
	QVBoxLayout* editWashListLayout = new QVBoxLayout();
	editWashListWidget->setLayout(editWashListLayout);
	emptyWashListButton = new QPushButton("Empty Wash List");
	editWashListLayout->addWidget(emptyWashListButton);

	QWidget* addWashListWidget = new QWidget();
	QHBoxLayout* addWashListLayout = new QHBoxLayout();
	addWashListWidget->setLayout(addWashListLayout);
	washListRegNumberLabel = new QLabel("Registration number:");
	addWashListLayout->addWidget(washListRegNumberLabel);
	washListRegNumberText = new QLineEdit();
	addWashListLayout->addWidget(washListRegNumberText);
	washListAddButton = new QPushButton("Add to Wash List");
	addWashListLayout->addWidget(washListAddButton);
	editWashListLayout->addWidget(addWashListWidget);

	QWidget* generateCarsWidget = new QWidget();
	QHBoxLayout* generateCarsLayout = new QHBoxLayout();
	generateCarsWidget->setLayout(generateCarsLayout);
	generateCarsLabel = new QLabel("Number of cars to generate:");
	generateCarsLayout->addWidget(generateCarsLabel);
	generateCarsText = new QLineEdit();
	generateCarsLayout->addWidget(generateCarsText);
	generateCarsButton = new QPushButton("Generate Wash List");
	generateCarsLayout->addWidget(generateCarsButton);
	editWashListLayout->addWidget(generateCarsWidget);

	QWidget* exportWashListWidget = new QWidget();
	QHBoxLayout* exportWashListLayout = new QHBoxLayout();
	exportWashListWidget->setLayout(exportWashListLayout);
	exportWashListLabel = new QLabel("HTML file name:");
	exportWashListLayout->addWidget(exportWashListLabel);
	exportWashListText = new QLineEdit();
	exportWashListLayout->addWidget(exportWashListText);
	exportWashListButton = new QPushButton("Export to File");
	exportWashListLayout->addWidget(exportWashListButton);
	editWashListLayout->addWidget(exportWashListWidget);

	washListLayout->addWidget(editWashListWidget);
	washListWindow->show();
}

void WashListGUI::connectSignalsSlots() {
	QObject::connect(refreshWashListButton, &QPushButton::clicked, this, [&]() {
		refreshCarsList(carsSrv.getWashList());
		});
	QObject::connect(emptyWashListButton, &QPushButton::clicked, this, [&]() {
		carsSrv.emptyWashList();
		refreshCarsList(carsSrv.getWashList());
		});
	QObject::connect(washListAddButton, &QPushButton::clicked, this, [&]() {
		try {
			carsSrv.addToWashList(washListRegNumberText->text().toStdString());
			refreshCarsList(carsSrv.getWashList());
		}
		catch (const RepositoryException& re) {
			QMessageBox::warning(washListWindow, "Repository Error", QString::fromStdString(re.getErrorMsg()));
		}
		});
QObject:connect(generateCarsButton, &QPushButton::clicked, this, [&]() {
	carsSrv.generateWashList(generateCarsText->text().toInt());
	refreshCarsList(carsSrv.getWashList());
	});
QObject::connect(exportWashListButton, &QPushButton::clicked, this, [&]() {
	try {
		carsSrv.exportWashListToFile(exportWashListText->text().toStdString());
		exportWashListText->setText("");
	}
	catch (const FileException& fe) {
		QMessageBox::warning(washListWindow, "File Error", QString::fromStdString(fe.getErrorMsg()));
	}
	});
}

void WashListGUI::refreshCarsList(const vector<Car>& cars) {
	washTable->clearContents();
	washTable->setRowCount(carsSrv.sizeWashList());
	int row = 0;
	for (const auto& car : cars) {
		QTableWidgetItem* cell1 = new QTableWidgetItem(QString::fromStdString(car.getRegNumber()));
		QTableWidgetItem* cell2 = new QTableWidgetItem(QString::fromStdString(car.getManufacturer()));
		QTableWidgetItem* cell3 = new QTableWidgetItem(QString::fromStdString(car.getModel()));
		QTableWidgetItem* cell4 = new QTableWidgetItem(QString::fromStdString(car.getType()));
		washTable->setItem(row, 0, cell1);
		washTable->setItem(row, 1, cell2);
		washTable->setItem(row, 2, cell3);
		washTable->setItem(row, 3, cell4);
		row++;
	}
}

void WashListGUI::update() {
	this->refreshCarsList(carsSrv.getWashList());
}

WashListGUI::~WashListGUI() {
	carsSrv.removeObserver(this);
}

void WashListReadOnlyGUI::paintEvent(QPaintEvent* ev) {
	QPainter p{ this };
	int ind{ 0 };
	for (const auto& car : carsSrv.getWashList()) {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		srand(seed);
		// p.drawRect(rand() % width() + 1, rand() % height() + 1, 40, 20);
		p.drawImage(rand() % 1200, rand() % 600, QImage("gabi.jpg"));
	}
}

void WashListReadOnlyGUI::update() {
	repaint();
}

WashListReadOnlyGUI::~WashListReadOnlyGUI() {
	carsSrv.removeObserver(this);
}