#include "QtDm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDm w;
    w.show();
    return a.exec();
}
