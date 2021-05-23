#ifndef APPEARANCESETTINGS_H
#define APPEARANCESETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
class AppearanceSettings: public QWidget
{
	Q_OBJECT

public:


    explicit AppearanceSettings(QWidget *parent = nullptr, int index = 1);

    explicit AppearanceSettings(QWidget *parent);
    QVBoxLayout *mainLayout;
    QPushButton *lightThemeButton;
	QStringList items;
	QCheckBox *checkBox;
	QHBoxLayout *okButtonLayout;
	QComboBox *textTypeBox;
	~AppearanceSettings();

    short getTextType() const;

	short textType;
signals:
    void lightThemeEnabled();
    void textTypeChanged();
    void darkThemeEnabled();
};
#endif