#include "Carwash.h"
#include <QtWidgets/QApplication>
#include "Tests.h"
#include "GUI.h"

int runGUI(int argc, char* argv[]) {
    QApplication a(argc, argv);
    CarValidator carVal;
    FileCarsRepository carsRepo{ "cars.txt" };
    FileCarsRepository carsToWash{ "wash_list.txt" };
    CarsService carsSrv{ carVal, carsRepo, carsToWash };
    GUI gui{ carsSrv };
    gui.show();
    return a.exec();
}

int main(int argc, char* argv[]) {
    Tests tests;
    tests.runAllTests();
    return runGUI(argc, argv);
}
