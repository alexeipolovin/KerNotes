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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QHBoxLayout>
#include <QWidget>
#include "appearancesettings.h"

class SettingsWindow : public QWidget
{
    Q_OBJECT

private:


    QHBoxLayout *mainLayout;
    QVBoxLayout *settingsTreeLayout;
    // fuck, it's just a start
    QVBoxLayout *textEditorSettingsLayout;

public:
    int index;
    AppearanceSettings *appearanceSettings;
    explicit SettingsWindow(QWidget *parent= nullptr, int index = 1);
    explicit SettingsWindow(QWidget *parent = nullptr);
    inline short getTextType();
    ~SettingsWindow();

public slots:
    void appearanceClick();
signals:

    void textTypeChanged() const;
};

#endif // SETTINGSWINDOW_H
