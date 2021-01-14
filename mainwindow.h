#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDirModel>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>
#include "untextedit.h"


#define TYPE_SETTINGS "settings/file_type"
#define FIRST_STARTUP "settings/first_startup"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *toolBar;

    QToolBar *createToolbar();

    QWidget *mainWidget;
    QHBoxLayout *mainLayout;

    UnTextEdit *textEdit;

    QTreeView *view;
    QDirModel *model;

    QSettings *settings;

    QString fileName;

    bool saveFile();
    bool openFile();

public:
    MainWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);

    ~MainWindow();
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H