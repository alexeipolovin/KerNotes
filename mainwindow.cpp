#include "mainwindow.h"

#include <QMenu>
#include <QToolButton>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QCloseEvent>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    textEdit = new UnTextEdit();

    addToolBar(createToolbar());

    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();


    connect(textEdit, &UnTextEdit::textChanged, this, [this]()
    {
       textEdit->setIsTextChanged(true);
    });

    settings = new QSettings("Kernux", "KerNotes");

    if(settings->value(FIRST_STARTUP).toString() == "" || settings->value(TYPE_SETTINGS).toString() == "")
    {
        QStringList items;
        items << "HTML";
        items << "MarkDown";
        items << "Txt";

        QInputDialog dialog;
        dialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
        dialog.setComboBoxItems(items);
        dialog.setWindowTitle("Choose File Type");
        if(dialog.exec())
        {
            auto text = dialog.textValue();
            qDebug() << text;
            if(text == "HTML")
            {
                textEdit->setTextType(1);
                settings->setValue(TYPE_SETTINGS, 1);
            } else if(text == "MarkDown")
            {
                textEdit->setTextType(2);
                settings->setValue(TYPE_SETTINGS, 2);
            } else if(text == "Txt")
            {
                textEdit->setTextType(3);
                settings->setValue(TYPE_SETTINGS, 3);
            }
            settings->setValue(FIRST_STARTUP, "0");
        }
    } else {
        textEdit->setTextType(settings->value(TYPE_SETTINGS).toInt());
    }

    model = new QDirModel();

    view = new QTreeView();
    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));
    view->setFixedWidth(this->width() * 1/4);

    mainLayout->addWidget(view);
    mainLayout->addWidget(textEdit);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

    auto *openShortcut = new QShortcut(this);
    openShortcut->setKey(Qt::CTRL + Qt::Key_O);
    connect(openShortcut, &QShortcut::activated, textEdit, &UnTextEdit::openFile);

    auto *saveShortcut = new QShortcut(this);
    saveShortcut->setKey(Qt::CTRL + Qt::Key_S);
    connect(saveShortcut, &QShortcut::activated, textEdit, &UnTextEdit::saveFile);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    view->setFixedWidth(this->width() * 1/4);

    qDebug() << "I'm resized)";

}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if(textEdit->getIsTextChanged()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "KerNotes",
                                                                tr("Are you sure?\n"),
                                                            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes)
    {
        event->ignore();
    } else {
        event->accept();
    }
} else {
        event->accept();
    }
}


QToolBar *MainWindow::createToolbar()
{
    toolBar = new QToolBar();

    toolBar->setMovable(false);

    auto *fileToolButon = new QToolButton();

    QMenu *menu = new QMenu();

    QAction *openFileAction = new QAction("Open...");
    connect(openFileAction, &QAction::triggered, this->textEdit, &UnTextEdit::openFile);

    QAction *saveFileAction = new QAction("Save...");
    connect(saveFileAction, &QAction::triggered, this->textEdit, &UnTextEdit::saveFile);

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
