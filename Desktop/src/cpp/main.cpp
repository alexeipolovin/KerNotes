#include "src/headers/mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

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
    if (settings->value(VERSION).toString() == "")
    {
        qDebug() << "Version";
        settings->setValue(VERSION, STANDART_VERSION);
        qDebug() << settings->value(VERSION).toString();
    } else {
        qDebug() << settings->value(VERSION).toString();
    }


// windows dark theme checking and enabling
#ifdef Q_OS_WIN
    QSettings darkTheme(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)",QSettings::NativeFormat);
    if(darkTheme.value("AppsUseLightTheme")==0)
    {
        qDebug() << "Dark theme enabled";
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    QColor darkColor = QColor(45,45,45);
    QColor disabledColor = QColor(127, 127, 127);
    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(18,18,18));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    QApplication::setPalette(darkPalette);
    } else if (darkTheme.value("AppsUseLightTheme") == ""){
         QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    QColor darkColor = QColor(45,45,45);
    QColor disabledColor = QColor(127, 127, 127);
    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(18,18,18));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    } else {
        qDebug() << "Light theme enabled";
    }
//    darkTheme.deleteLater();
#endif
    w.showMaximized();
    return a.exec();
}
