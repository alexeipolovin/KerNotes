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
#include <QMessageBox>
#include "libraries/markdownhighlighter.h"
#include "libraries/qjsonmodel.h"

#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"

#define STANDART_TITLE_EDITED "* - KerNotes"
#define STANDART_TITLE " - KerNotes"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    textEdit = new UnTextEdit();
    previewTextEdit = new QTextEdit();
    previewTextEdit->setReadOnly(true);

    auto doc = this->textEdit->document();
    auto *highliter = new MarkdownHighlighter(doc);
    qDebug() << highliter;

    addToolBar(createToolbar());

    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();

    connect(textEdit, &UnTextEdit::textChanged, this, [this] ()
    {
       textEdit->setIsTextChanged(true);
       setWindowTitle(textEdit->getFileName() + STANDART_TITLE_EDITED);
       if(!this->shown) {
       if(previewTextEdit->toPlainText().length() > 5000)
       {
           QMessageBox::warning(nullptr, "Too large file", "Your file is too large, live preview will be disabled");
           this->shown = true;
       } else {
            this->previewTextEdit->setMarkdown(this->textEdit->toMarkdown());
       }
       }
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
                QMessageBox::warning(NULL, "Warning", "HTML is currently not supported");
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
    QString json = R"({
                       "firstName": "John",
                       "lastName": "Smith",
                       "age": 25,
                       "address":
                       {
                           "streetAddress": "21 2nd Street",
                           "city": "New York",
                           "state": "NY",
                           "postalCode": "10021"
                       },
                       "phoneNumber":
                       [
                           {
                             "type": "home",
                             "number": "212 555-1234"
                           },
                           {
                             "type": "fax",
                             "number": "646 555-4567"
                           }
                       ]
                   })";
    view = new QTreeView;
    model = new QJsonModel;
    view->setModel(model);
    model->loadJson(json.toUtf8());
//    view = new QTreeView;
//    view->setModel(model);
//    view->setRootIndex(model->index(QDir::currentPath()));
    view->setFixedWidth(this->width() * 1/4);

    mainLayout->addWidget(view);
    mainLayout->addWidget(textEdit);
    if(textEdit->getTextType() != 3)
        mainLayout->addWidget(previewTextEdit);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(TreeViewDoubleClick(QModelIndex)));

    auto *openShortcut = new QShortcut(this);
    openShortcut->setKey(Qt::CTRL + Qt::Key_O);
    connect(openShortcut, &QShortcut::activated, textEdit, &UnTextEdit::openFile);

    auto *saveShortcut = new QShortcut(this);
    saveShortcut->setKey(Qt::CTRL + Qt::Key_S);
    connect(saveShortcut, &QShortcut::activated, textEdit, &UnTextEdit::saveFile);
    connect(textEdit, &UnTextEdit::fileSaved, this, [this](){
        setWindowTitle(this->textEdit->getFileName() + STANDART_TITLE);
    });

    auto *boldShortcut = new QShortcut(this);
    boldShortcut->setKey(Qt::CTRL + Qt::Key_B);
    connect(boldShortcut, &QShortcut::activated, textEdit, &UnTextEdit::placeBoldText);

    auto *cursShortcut = new QShortcut(this);
    cursShortcut->setKey(Qt::CTRL + Qt::Key_I);
    connect(cursShortcut, &QShortcut::activated, textEdit, &UnTextEdit::placeCursText);

    auto *previewShortcut = new QShortcut(this);
    previewShortcut->setKey(Qt::CTRL + Qt::Key_P);
    connect(previewShortcut, &QShortcut::activated, this, [this](){
        this->previewTextEdit->setMarkdown(textEdit->toMarkdown());
    });

    webConnector = new WebConnector();
    connect(webConnector, &WebConnector::autoUpdatesUnknown, this, &MainWindow::updateUnknown);
    webConnector->checkUpdates();

}
// TODO: Remove this
void MainWindow::TreeViewDoubleClick(const QModelIndex &index)
{
//   auto path = model->filePath(index);
   QString path = "asd/asd/";

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
//        this->view->setRootIndex(this->model->index(path));

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
