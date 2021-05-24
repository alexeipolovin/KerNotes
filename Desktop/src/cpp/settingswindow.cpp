/*
 * Copyright (c) 2021 Alexei Polovin (alexeipolovin@gmail.com)

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
