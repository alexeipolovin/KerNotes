#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDirModel>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QToolBar *toolBar;

    QToolBar *createToolbar();

    QWidget *mainWidget;
    QHBoxLayout *mainLayout;

    QTextEdit *textEdit;

    QTreeView *view;
    QDirModel *model;

    QString fileName;

    bool saveFile();
    bool openFile();

public:
    MainWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);

    ~MainWindow();
};
#endif // MAINWINDOW_H
