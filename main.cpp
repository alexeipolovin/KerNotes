#include "mainwindow.h"

#include <QApplication>

#define STANDART_VERSION 1

#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // TODO: Rewrite to INI format for Linux, or create macro
    QSettings *settings = new QSettings();
    if(settings->value("VERSION").toString() == "")
    {
        settings->setValue("VERSION", STANDART_VERSION);
    }
    w.show();
    return a.exec();
}
