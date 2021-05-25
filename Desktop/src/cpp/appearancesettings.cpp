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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "src/headers/appearancesettings.h"
#include "src/headers/untextedit.h"
#include <QDebug>
#include <QFontDialog>
#include <QLineEdit>
#include <QLabel>

// Icon from https://freeicons.io/social-media/icons-settings-icon-9616
AppearanceSettings::AppearanceSettings(QWidget *parent, int index, bool lightTheme, QString syncType, QString url) : QWidget(parent)
{

    qDebug() << index;
	mainLayout = new QVBoxLayout();
	lightThemeButton = new QPushButton("Light Theme");
	checkBox = new QCheckBox("Light Theme");
	checkBox->setChecked(lightTheme);
	auto syncTypeCheckBox = new QCheckBox("String sync");
	auto urlLabel = new QLabel("Url:");
	auto lineEditLay = new QHBoxLayout();
	auto input = new QLineEdit();
    this->syncType = syncType;

    input->setText(url);

    qDebug() << syncType;

    if(syncType == "Binary")
    {
        syncTypeCheckBox->setChecked(false);
    } else {
        syncTypeCheckBox->setChecked(true);
    }


	lineEditLay->addWidget(urlLabel);
	lineEditLay->addWidget(input);

	okButtonLayout = new QHBoxLayout();
	textTypeBox = new QComboBox();
	QPushButton *fontSelectButton = new QPushButton("Select Font");

	QPushButton *okButton = new QPushButton("Ok");
	QPushButton *cancelButton = new QPushButton("Cancel");

    connect(okButton, &QPushButton::clicked, this, [this, syncTypeCheckBox, input, url](){
	    this->textType = (short) this->textTypeBox->currentIndex();
	    qDebug() << "Selected index" << this->textTypeBox->currentIndex();
	    qDebug() << "Current text" << this->textTypeBox->currentText();
        emit textTypeChanged();
        if(this->checkBox->isChecked())
        {
            qDebug() << "LIGHT THEME ALERT";
            emit lightThemeEnabled();
        } else {
            emit darkThemeEnabled();
        }

        if(syncTypeCheckBox->isChecked())
        {
            this->syncType = "Text";
            emit newSyncType();
        } else {
            this->syncType = "Binary";
            emit newSyncType();
        }

        if(input->text() != url)
        {
            this->mbUrl = input->text();
            emit newUrl();
        }
        this->close();
	});

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        this->hide();
        this->close();
    });

    connect(fontSelectButton, &QPushButton::clicked, this, [this]()
    {
        selectedFont = QFontDialog::getFont(0, this->font());
        emit newFontSelected();
    });

    setWindowIcon(QIcon(":/icons/settings.png"));
    setWindowTitle("Settings");


	textTypeBox->addItem("HTML");
	textTypeBox->addItem("Markdown");
	textTypeBox->addItem("Txt");

	textTypeBox->setCurrentIndex(index - 1);

	okButtonLayout->addWidget(okButton);
	okButtonLayout->addWidget(cancelButton);
    okButtonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

//	mainLayout->addWidget(lightThemeButton);
	mainLayout->addWidget(textTypeBox);
	mainLayout->addWidget(checkBox);
	mainLayout->addWidget(fontSelectButton);
	mainLayout->addWidget(syncTypeCheckBox);
	mainLayout->addLayout(lineEditLay);
	mainLayout->addLayout(okButtonLayout);
    setFixedSize(300, 300);
    setLayout(mainLayout);
}

short AppearanceSettings::getTextType() const
{
//    qDebug() << "dflskjglk" << this->textType;
    return this->textType + 1;
}

QString AppearanceSettings::getUrl() {
    return this->mbUrl;
}

QFont AppearanceSettings::getNewFont()
{
    return this->selectedFont;
}

QString AppearanceSettings::getSyncType() {
    return this->syncType;
}

AppearanceSettings::~AppearanceSettings() = default;