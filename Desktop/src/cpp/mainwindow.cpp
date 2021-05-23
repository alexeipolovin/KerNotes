#include "src/headers/mainwindow.h"
#include "src/headers/settingswindow.h"
#include "libraries/markdownhighliter/markdownhighlighter.h"

#include <QMenu>
#include <QToolButton>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QShortcut>
#include <QCloseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QFontDialog>

#define AUTO_UPDATES "AUTO_UPDATES_AVAILABLE"

#define STANDART_TITLE_EDITED "* - KerNotes"
#define STANDART_TITLE " - KerNotes"

/**
 * @brief MainWindow::MainWindow
 * @param QWidget parent
 * @author Alexei Polovin(alexeipolovin@gmail.com)
 * Конструктор класса главного окна
*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new UnTextEdit();
    textEdit->setTabStopDistance(QFontMetricsF(textEdit->font()).horizontalAdvance(' ') * 4);

    previewTextEdit = new QTextEdit();
    previewTextEdit->setContextMenuPolicy(Qt::NoContextMenu);
    previewTextEdit->setReadOnly(true);

    addToolBar(createToolbar());

    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout();
    livePreview = false;

//    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "KerNotes",
//                                    tr("One side preview?\n"),
//                                    QMessageBox::No | QMessageBox::Yes,
//                                    QMessageBox::Yes);
//    if(resBtn == QMessageBox::Yes)
//    {
//        livePreview = true;
//        qDebug() << livePreview;

//    }
    settings = new QSettings("Kernux", "KerNotes");

    // if(settings->value(FIRST_STARTUP).toString() == "" || settings->value(TYPE_SETTINGS).toString() == "")
    // {
    QStringList items;
    items << "HTML";
    items << "MarkDown";
    items << "Txt";

    QInputDialog dialog;
    dialog.setOptions(QInputDialog::UseListViewForComboBoxItems);
    dialog.setComboBoxItems(items);
    dialog.setWindowTitle("Choose File Type");
    if (dialog.exec())
    {
        auto text = dialog.textValue();
        qDebug() << text;
        if(text == "HTML")
        {
            QMessageBox::warning(nullptr, "Warning", "HTML is supported but not actively tested");
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
        // }
        // } else {
        //     textEdit->setTextType(settings->value(TYPE_SETTINGS).toInt());
        // }
    connect(textEdit, &UnTextEdit::textChanged, this, [this] ()
    {
        qDebug() << "Live preview:" << livePreview;
        qDebug() << "Text changed event";
       short textType = this->textEdit->getTextType();
       qDebug() << "Editing:"<< textType;
       textEdit->setIsTextChanged(true);
       setWindowTitle(textEdit->getFileName() + STANDART_TITLE_EDITED);
       // TODO: Optimize this
       if(!this->shown) {
       if(previewTextEdit->toPlainText().length() > 500000)
       {
           QMessageBox::warning(nullptr, "Too large file", "Your file is too large, live preview will be disabled");
           this->shown = true;
       } else {
           switch (textType) {
               case 1:
               if(!livePreview)
               {
                   qDebug() << this->textEdit->toHtml();
                   this->previewTextEdit->setHtml(this->textEdit->toHtml());
               }
                   break;
               case 2:
               if(!livePreview)
               {
                   this->previewTextEdit->setMarkdown(this->textEdit->toMarkdown());
               } else {
               }
                   break;
               default:
                   break;
           }
       }
       }

    });
//    connect(textEdit, &UnTextEdit::updateTextEdit, this, [this] ()
//    {
//        qDebug() << "One side update event";
//       short textType = this->textEdit->getTextType();
//       textEdit->setIsTextChanged(true);
//       setWindowTitle(textEdit->getFileName() + STANDART_TITLE_EDITED);
//       // TODO: Optimize this
//       if(!this->shown) {
//       if(previewTextEdit->toPlainText().length() > 500000)
//       {
//           QMessageBox::warning(nullptr, "Too large file", "Your file is too large, live preview will be disabled");
//           this->shown = true;
//       } else {
//           int cursorPosition = this->textEdit->textCursor().position();
//           switch (textType) {
//                case 1:
//                    if(livePreview)
//                    {
//                        qDebug() <<"CurrentText:" << this->textEdit->toHtml();
////                        this->textEdit->setHtml(this->textEdit->toHtml());
//                    }
//               break;
//                case 2:
//                    if(livePreview)
//                    {
//                        qDebug() <<"CurrentText:" << this->textEdit->toMarkdown();
////                        this->textEdit->setMarkdown(this->textEdit->toMarkdown());
//                    }
//               break;
//           default:
//               break;
//           }
//           QTextCursor cursor = this->textEdit->textCursor();
//           cursor.setPosition(cursorPosition);
//           this->textEdit->setTextCursor(cursor);
//
//       }
//       }
//
//    });
//    textEdit->setTextType(2);
    qDebug() << "UnTextEdit text type:" << textEdit->getTextType();

        }
    // TODO: Remove this
    if(textEdit->getTextType() == 2)
    {
        auto doc = this->textEdit->document();
        highliter = new MarkdownHighlighter(doc);


        qDebug() << highliter;
    }
    QString json = R"({
"name":"John", "age":31, "city":"New York"
                   })";
    view = new QTreeView();
    // model = new QJsonModel();
    model = new QDirModel();
    view->setModel(model);
    view->setRootIndex(model->index(QDir::currentPath()));
    // model->loadJson(json.toUtf8());
    // TODO: fix?
    view->setFixedWidth(this->width() * 1/4);

    mainLayout->addWidget(view);
    mainLayout->addWidget(textEdit);
    if(!livePreview)
    {
        mainLayout->addWidget(previewTextEdit);
    }
    auto testButton = new QPushButton("Test");
    connect(testButton, &QPushButton::clicked, this, [this](){
        delete highliter;
    });
    mainLayout->addWidget(testButton);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    connect(view, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(TreeViewDoubleClick(const QModelIndex &)));

    auto updateShortcut = new QShortcut(this);
//    updateShortcut->setKey(Qt::Key_Enter);
//    connect(updateShortcut, &QShortcut::activated, this, [this] (){
//       emit textEdit->textChanged();
//       qDebug() << "Text changed";
//    });
    auto *openShortcut = new QShortcut(this);
    openShortcut->setKey(Qt::CTRL + Qt::Key_O);
    connect(openShortcut, &QShortcut::activated, textEdit, &UnTextEdit::openFile);

    auto *saveShortcut = new QShortcut(this);
    saveShortcut->setKey(Qt::CTRL + Qt::Key_S);
    connect(saveShortcut, &QShortcut::activated, textEdit, &UnTextEdit::saveFile);
    connect(textEdit, &UnTextEdit::fileSaved, this, [this](){
        setWindowTitle(this->textEdit->getFileName() + STANDART_TITLE);
    });

    auto imageInsertShortcut = new QShortcut(this);
    imageInsertShortcut->setKey(Qt::CTRL+Qt::Key_N);
    connect(imageInsertShortcut, &QShortcut::activated, textEdit, &UnTextEdit::insertImageSnippet);
    auto *boldShortcut = new QShortcut(this);
    boldShortcut->setKey(Qt::CTRL + Qt::Key_B);
    connect(boldShortcut, &QShortcut::activated, textEdit, &UnTextEdit::placeBoldText);

    auto *cursShortcut = new QShortcut(this);
    cursShortcut->setKey(Qt::CTRL + Qt::Key_I);
    connect(cursShortcut, &QShortcut::activated, textEdit, &UnTextEdit::placeCursText);

    auto *previewShortcut = new QShortcut(this);
    previewShortcut->setKey(Qt::CTRL + Qt::Key_P);
    connect(previewShortcut, &QShortcut::activated, this, [this]() {
        switch (this->textEdit->getTextType()) {
            case 1:
                this->previewTextEdit->setHtml(textEdit->toHtml());
//                if(livePreview)
//                {
//                    this->textEdit->setHtml(textEdit->toHtml());
//                }
                break;
            case 2:
                if(!livePreview)
                {
                    this->previewTextEdit->setMarkdown(textEdit->toMarkdown());
                }
                break;
        }
    });

    webConnector = new WebConnector();
    connect(webConnector, &WebConnector::autoUpdatesUnknown, this, &MainWindow::updateUnknown);
    webConnector->checkUpdates();

    connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(TreeViewDoubleClick(QModelIndex)));

    if(settings->value("lasteditedfile").toString() != "")
    {
        qDebug() << settings->value("lasteditedfile").toString();
        this->textEdit->openLastFile(settings->value("lasteditedfile").toString());
        textEdit->setFileName(settings->value("lasteditedfile").toString());
        setWindowTitle(textEdit->getFileName() + STANDART_TITLE_EDITED);
    }
}
// TODO: Remove this
void MainWindow::TreeViewDoubleClick(const QModelIndex &index)
{
   QString path = model->filePath(index);
   QFile file(model->filePath(index));

   if(file.open(QIODevice::ReadOnly))
   {
       this->textEdit->setText(file.readAll());
       this->fileName = path.split("/").back();
       qDebug() << this->fileName << '\n';
       setWindowTitle(this->fileName + STANDART_TITLE);
       textEdit->setFileName(this->fileName);
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
                                                            QMessageBox::No | QMessageBox::Save  | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::No)
    {
        event->ignore();
    } else if(resBtn == QMessageBox::Yes){
        event->accept();
    } else {
        textEdit->saveFile();
        event->accept();
    }
} else {
        event->accept();
    }
}

void MainWindow::connectAll()
{
    connect(textEdit, &UnTextEdit::textChanged, this, [this] ()
    {
        qDebug() << "Live preview:" << livePreview;
        qDebug() << "Text changed event";
        short textType = this->textEdit->getTextType();
        textEdit->setIsTextChanged(true);
        setWindowTitle(textEdit->getFileName() + STANDART_TITLE_EDITED);
        // TODO: Optimize this
        if(!this->shown) {
            if(previewTextEdit->toPlainText().length() > 500000)
            {
                QMessageBox::warning(nullptr, "Too large file", "Your file is too large, live preview will be disabled");
                this->shown = true;
            } else {
                switch (textType) {
                    case 1:
                        if(!livePreview)
                        {
                            this->previewTextEdit->setHtml(this->textEdit->toHtml());

                        }
                        break;
                    case 2:
                        if(!livePreview)
                        {
                            this->previewTextEdit->setMarkdown(this->textEdit->toMarkdown());
                        } else {
                        }
                        break;
                    default:
                        break;
                }
            }
        }

    });
}

QToolBar *MainWindow::createToolbar()
{
    toolBar = new QToolBar();

    toolBar->setMovable(false);

    auto *fileToolButton = new QToolButton();
    auto textWorkerButton = new QToolButton();

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

    auto boldAction = new QAction("Make text bold");
    connect(boldAction, &QAction::triggered, textEdit, &UnTextEdit::placeBoldText);

    auto cursAction = new QAction("Make text cursive");
    connect(cursAction, &QAction::triggered, textEdit, &UnTextEdit::placeCursText);

    auto imageAction = new QAction("Insert image");
    connect(imageAction, &QAction::triggered, textEdit, &UnTextEdit::insertImageSnippet);
    QMenu *makeTextMenu = new QMenu();

    QAction *changeTextLayoutAction = new QAction("Change text layout");
    connect(changeTextLayoutAction, &QAction::triggered, this, []() {

    });
    QAction *fontTestActon = new QAction("Open Font");
    connect(fontTestActon, &QAction::triggered, this, [this]()
    {
       QFont font = QFontDialog::getFont(0, this->font());
    });


    QAction *settingsAction = new QAction("Settings");
    connect(settingsAction, &QAction::triggered, this, [this]() {
        AppearanceSettings *w = new AppearanceSettings(nullptr, this->textEdit->getTextType());
        QTextDocument *docum = this->textEdit->document();
        connect(w, &AppearanceSettings::textTypeChanged, this, [this, w,docum](){
            if(w->getTextType() != this->textEdit->getTextType())
            {
                qDebug() << "New text type " <<w->getTextType();
                switch (w->getTextType())
                {
                    case 1:
                        disconnect(textEdit, &UnTextEdit::textChanged, 0, 0);
                        this->connectAll();
                        if(this->textEdit->getTextType() == 2)
                        {
                            delete highliter;
                        }
                        break;

                    case 2:
                        highliter = new MarkdownHighlighter(docum);
                        qDebug()<<highliter;
                        break;
                    default:
                        qDebug() << "new text type" << w->getTextType();
                        break;
                }
                this->textEdit->setTextType(w->getTextType());
            }
           this->textEdit->setTextType(w->getTextType());

        });
        connect(w, &AppearanceSettings::newFontSelected, this, [this, w]()
        {
            this->setFont(w->getNewFont());
        });

        w->show();

    });

    menu->addAction(openFileAction);
    menu->addAction(saveFileAction);
    menu->addAction(openDirAction);

    makeTextMenu->addAction(boldAction);
    makeTextMenu->addAction(cursAction);
    makeTextMenu->addAction(imageAction);

    fileToolButton->setMenu(menu);
    fileToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fileToolButton->setText("File");
    connect(fileToolButton, &QToolButton::clicked, textEdit, &UnTextEdit::newFile);

    connect(textEdit, &UnTextEdit::clearTitle, this, [this]()
    {
        setWindowTitle("");
    });

    textWorkerButton->setMenu(makeTextMenu);
    textWorkerButton->setPopupMode(QToolButton::InstantPopup);
    textWorkerButton->setText("Text Worker");

    toolBar->addWidget(fileToolButton);
    toolBar->addWidget(textWorkerButton);
    toolBar->addAction(settingsAction);
//    toolBar->addAction(fontTestActon);

    return toolBar;
}

MainWindow::~MainWindow()
{
    settings->setValue("lasteditedfile", this->textEdit->getFileName());
}
