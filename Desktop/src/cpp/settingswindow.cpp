#include "src/headers/settingswindow.h"

#include <QLabel>
#include <QPushButton>
#include <src/headers/appearancesettings.h>
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent, int index) : QWidget(parent)
{
    qDebug() << index;
    this->index = index;
    mainLayout = new QHBoxLayout();
    settingsTreeLayout = new QVBoxLayout();
    auto appearanceSettingsButton = new QPushButton("Appearance settings");
    settingsTreeLayout->addWidget(appearanceSettingsButton);
    appearanceSettingsButton->setFixedWidth(120);
    connect(appearanceSettingsButton, &QPushButton::clicked, this, &SettingsWindow::appearanceClick);
    textEditorSettingsLayout = new QVBoxLayout();
    auto label2 = new QLabel();
    textEditorSettingsLayout->addWidget(label2);

    mainLayout->addLayout(settingsTreeLayout);
    mainLayout->addLayout(textEditorSettingsLayout);
    setLayout(mainLayout);
}

short SettingsWindow::getTextType()
{
//    qDebug() << "aaaa" << appearanceSettings->getTextType();
//    qDebug() << "bbbb" << appearanceSettings->textType;
    return appearanceSettings->getTextType();
}

void SettingsWindow::appearanceClick()
{
    appearanceSettings = new AppearanceSettings(nullptr, this->index);
    connect(appearanceSettings, &AppearanceSettings::textTypeChanged, this, [this](){
       emit textTypeChanged();
    });
    appearanceSettings->show();
}


SettingsWindow::~SettingsWindow() = default;
