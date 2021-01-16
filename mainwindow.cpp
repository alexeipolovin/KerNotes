#include "mainwindow.h"
#include "settingswindow.h"

#include <QMenu>
#include <QToolButton>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QCloseEvent>
#include <QInputDialog>

#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"

#define STANDART_TITLE "* - KerNotes"

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
       setWindowTitle(textEdit->getFileName() +STANDART_TITLE);
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
            // Remake this
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

    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(TreeViewDoubleClick(QModelIndex)));

    auto *openShortcut = new QShortcut(this);
    openShortcut->setKey(Qt::CTRL + Qt::Key_O);
    connect(openShortcut, &QShortcut::activated, textEdit, &UnTextEdit::openFile);

    auto *saveShortcut = new QShortcut(this);
    saveShortcut->setKey(Qt::CTRL + Qt::Key_S);
    connect(saveShortcut, &QShortcut::activated, textEdit, &UnTextEdit::saveFile);

    webConnector = new WebConnector();
    connect(webConnector, &WebConnector::autoUpdatesUnknown, this, &MainWindow::updateUnknown);
    webConnector->checkUpdates();

}

void MainWindow::TreeViewDoubleClick(const QModelIndex &index)
{
   auto path = model->filePath(index);

   QFile file(path);

   if(file.open(QIODevice::ReadOnly))
   {
       this->textEdit->setText(file.readAll());
       this->fileName = path.split("/").back();
       setWindowTitle(this->fileName + STANDART_TITLE);
   }
}

void MainWindow::updateUnknown()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "KerNotes",
                                    tr("Check updates automatically\n"),
                                    QMessageBox::No | QMessageBox::Yes,
                                    QMessageBox::Yes);
        if(resBtn == QMessageBox::Yes)
        {
            this->settings->setValue(AUTO_UPDATES, true);
        } else {
            this->settings->setValue(AUTO_UPDATES, false);
        }

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    view->setFixedWidth(this->width() * 1/4);

    qDebug() << "Window resized";

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

    QAction *openFileAction = new QAction("Open file");
    connect(openFileAction, &QAction::triggered, this->textEdit, &UnTextEdit::openFile);

    QAction *saveFileAction = new QAction("Save file");
    connect(saveFileAction, &QAction::triggered, this->textEdit, &UnTextEdit::saveFile);

    QAction *openDirAction = new QAction("Open folder");
    connect(openDirAction, &QAction::triggered, this, [this]()
    {
        QString path = QFileDialog::getExistingDirectory(this, "Choose Directory",QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        this->view->setRootIndex(this->model->index(path));

    });

    QAction *changeTextLayoutAction = new QAction("Change text layout");
    connect(changeTextLayoutAction, &QAction::triggered, this, []() {

    });

    QAction *settingsAction = new QAction("Settings");
    connect(settingsAction, &QAction::triggered, this, []() {
        SettingsWindow *w = new SettingsWindow();
        w->show();
    });
    menu->addAction(openFileAction);
    menu->addAction(saveFileAction);
    menu->addAction(openDirAction);

    fileToolButon->setMenu(menu);
    fileToolButon->setPopupMode(QToolButton::MenuButtonPopup);
    fileToolButon->setText("File");

    toolBar->addWidget(fileToolButon);
    toolBar->addAction(settingsAction);

    return toolBar;
}

MainWindow::~MainWindow()
{
}
