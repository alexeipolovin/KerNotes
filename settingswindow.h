#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QHBoxLayout>
#include <QWidget>

class SettingsWindow : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *mainLayout;
    QVBoxLayout *settingsTreeLayout;

    // fuck, it's just a start
    QVBoxLayout *textEditorSettingsLayout;

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

signals:

};

#endif // SETTINGSWINDOW_H
