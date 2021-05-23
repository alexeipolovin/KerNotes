#include "src/headers/appearancesettings.h"
#include "src/headers/untextedit.h"
#include <QDebug>
AppearanceSettings::AppearanceSettings(QWidget *parent, int index) : QWidget(parent)
{
    qDebug() << index;
	mainLayout = new QVBoxLayout();
	lightThemeButton = new QPushButton("Light Theme");
	checkBox = new QCheckBox("Live Preview");
	okButtonLayout = new QHBoxLayout();
	textTypeBox = new QComboBox();

	QPushButton *okButton = new QPushButton("Ok");
	QPushButton *cancelButton = new QPushButton("Cancel");

    connect(okButton, &QPushButton::clicked, this, [this](){
	    this->textType = (short) this->textTypeBox->currentIndex();
	    qDebug() << "Selected index" << this->textTypeBox->currentIndex();
	    qDebug() << "Current text" << this->textTypeBox->currentText();
        emit textTypeChanged();
        if(this->checkBox->isChecked())
        {
            emit lightThemeEnabled();
        } else {
            emit darkThemeEnabled();
        }
        this->close();
	});

    connect(cancelButton, &QPushButton::clicked, this, [this](){
        this->hide();
        this->close();
    });



	textTypeBox->addItem("HTML");
	textTypeBox->addItem("Markdown");
	textTypeBox->addItem("Txt");

	textTypeBox->setCurrentIndex(index - 1);

	okButtonLayout->addWidget(okButton);
	okButtonLayout->addWidget(cancelButton);
    okButtonLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);

	mainLayout->addWidget(lightThemeButton);
	mainLayout->addWidget(textTypeBox);
	mainLayout->addWidget(checkBox);
	mainLayout->addLayout(okButtonLayout);
    setFixedSize(300, 300);
    setLayout(mainLayout);
}

short AppearanceSettings::getTextType() const
{
//    qDebug() << "dflskjglk" << this->textType;
    return this->textType + 1;
}

AppearanceSettings::~AppearanceSettings() = default;