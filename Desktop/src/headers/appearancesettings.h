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


    explicit AppearanceSettings(QWidget *parent = nullptr, int index = 1, bool lightTheme = false);

	QFont selectedFont;

    explicit AppearanceSettings(QWidget *parent);
    QVBoxLayout *mainLayout;
    QPushButton *lightThemeButton;
	QStringList items;
	QCheckBox *checkBox;
	QHBoxLayout *okButtonLayout;
	QComboBox *textTypeBox;
	~AppearanceSettings();

    short getTextType() const;
    QFont getNewFont();

	short textType;
signals:
    void newFontSelected();
    void lightThemeEnabled();
    void textTypeChanged();
    void darkThemeEnabled();
};
#endif