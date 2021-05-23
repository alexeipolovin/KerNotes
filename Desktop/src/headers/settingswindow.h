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
    short getTextType();
    ~SettingsWindow();

public slots:
    void appearanceClick();
signals:

    void textTypeChanged() const;
};

#endif // SETTINGSWINDOW_H
