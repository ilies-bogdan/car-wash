#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_carwash.h"

class Carwash : public QMainWindow
{
    Q_OBJECT

public:
    Carwash(QWidget *parent = nullptr);
    ~Carwash();

private:
    Ui::carwashClass ui;
};
