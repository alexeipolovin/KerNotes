#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#define STANDART_VERSION "1"
#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"
#define VERSION "VERSION"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // icon from https://freeicons.io/
    // icon made by https://freeicons.io/profile/823 (Muhammad Haq (thank's))
    w.setWindowIcon(QIcon(":/icons/favicon.png"));
    // TODO: Rewrite to INI format for Linux, or create macro and fix it
    QSettings *settings = new QSettings("Kernux", "KerNotes");
    if(settings->value(VERSION).toString() == "")
    {
        qDebug() << "Version";
        settings->setValue(VERSION, STANDART_VERSION);
        qDebug() << settings->value(VERSION).toString();
    } else {
        qDebug() << settings->value(VERSION).toString();
    }
    w.showMaximized();
    return a.exec();
}
