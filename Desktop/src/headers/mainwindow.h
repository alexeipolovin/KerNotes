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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDirModel>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QSettings>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>
#include <QFileSystemModel>
#include <libraries/markdownhighliter/markdownhighlighter.h>
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
    // QJsonModel *model;
    // QFileSystemModel *model;
    QDirModel *model;

    QSettings *settings;

    QString fileName;

    bool shown = false;

public:
    bool livePreview = false;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MarkdownHighlighter *highliter;

    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void connectAll();
    bool lightTheme;
signals:
    void lightThemeEnabled();
public slots:

    void updateUnknown();

    void TreeViewDoubleClick(const QModelIndex &index);
};
#endif // MAINWINDOW_H
