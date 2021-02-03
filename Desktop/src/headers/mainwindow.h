#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDirModel>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>
//#include <QWebEngineView>
#include "untextedit.h"
#include "webconnector.h"
#include "libraries/qjsontreeview/qjsonmodel.h"

#define TYPE_SETTINGS "settings/file_type"
#define FIRST_STARTUP "settings/first_startup"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    WebConnector *webConnector;

    QToolBar *toolBar;
    QToolBar *createToolbar();

    QWidget *mainWidget;
    QHBoxLayout *mainLayout;

    UnTextEdit *textEdit;

    QTextEdit *previewTextEdit;
//    QWebEnginePage *previewTextEdit;
    QTreeView *view;
    QJsonModel *model;

    QSettings *settings;

    QString fileName;

    bool shown = false;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
public slots:
    void updateUnknown();
    void TreeViewDoubleClick(const QModelIndex &index);
};
#endif // MAINWINDOW_H
