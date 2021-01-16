#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout();
    settingsTreeLayout = new QVBoxLayout();
    textEditorSettingsLayout = new QVBoxLayout();
    setLayout(mainLayout);

}

SettingsWindow::~SettingsWindow()
{
}
