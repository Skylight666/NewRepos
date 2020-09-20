#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDm.h"

class QtDm : public QMainWindow
{
    Q_OBJECT

public:
    QtDm(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtDmClass ui;
};
