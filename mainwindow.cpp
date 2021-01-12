#include "mainwindow.h"

#include <QMenu>
#include <QToolButton>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    addToolBar(createToolbar());

    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();

    textEdit = new QTextEdit();

    model = new QDirModel();

    view = new QTreeView();
    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));
    view->setFixedWidth(this->width() * 1/4);

    mainLayout->addWidget(view);
    mainLayout->addWidget(textEdit);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

//    auto *openShortcut = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), nullptr);
//    connect(openShortcut, &QShortcut::activated, &MainWindow::openFile);

//    auto *saveShortcut = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), nullptr);
//    connect(saveShortcut, &QShortcut::activated, &MainWindow::saveFile);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    view->setFixedWidth(this->width() * 1/4);

}

bool MainWindow::saveFile()
{
    if(!(this->fileName == "")) {
            QFile file(this->fileName);
            if(file.open(QIODevice::ReadWrite))
            {
                file.write(textEdit->toPlainText().toUtf8());

                qDebug() << "File Saved";
            } else {
                return false;
            }
            file.close();
            return true;
        } else {
        return false;
    }

}

bool MainWindow::openFile()
{
    this->fileName = QFileDialog::getOpenFileName(this, "Open Image", QDir::currentPath(), "Text Files (*.md *.html *.txt)");
    if(this->fileName == "")
    {
        qDebug() << "File path clear!";
        return false;
    } else {
        qDebug() << "File path is not clear";
        QFile file(this->fileName);
        if(file.open(QIODevice::ReadOnly))
        textEdit->setText(file.readAll());
        file.close();
        return true;
    }

}

QToolBar *MainWindow::createToolbar()
{
    toolBar = new QToolBar();

    toolBar->setMovable(false);

    auto *fileToolButon = new QToolButton();

    QMenu *menu = new QMenu();

    auto *openFileAction = new QAction("Open...");
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    auto *saveFileAction = new QAction("Save...");
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);

    menu->addAction(openFileAction);
    menu->addAction(saveFileAction);

    fileToolButon->setMenu(menu);
    fileToolButon->setPopupMode(QToolButton::MenuButtonPopup);
    fileToolButon->setText("File");

    toolBar->addWidget(fileToolButon);

    return toolBar;
}

MainWindow::~MainWindow()
{
}

