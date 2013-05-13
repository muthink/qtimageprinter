#include "mainwindow.h"
#include "dialogmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Muthink");
    QCoreApplication::setOrganizationDomain("muthink.com");
    QCoreApplication::setApplicationName("QT Image Printer");
    DialogMain d;
    d.show();
    
    return a.exec();
}
