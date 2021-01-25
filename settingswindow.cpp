#include "settingswindow.h"

#include <QLabel>

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QHBoxLayout();
    settingsTreeLayout = new QVBoxLayout();
    auto label = new QLabel("lol");
    settingsTreeLayout->addWidget(label);
    textEditorSettingsLayout = new QVBoxLayout();

    mainLayout->addLayout(settingsTreeLayout);
    mainLayout->addLayout(textEditorSettingsLayout);
    setLayout(mainLayout);

}

SettingsWindow::~SettingsWindow()
{
}
