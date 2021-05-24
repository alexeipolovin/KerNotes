#include "src/headers/untextedit.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextDocumentFragment>
#include <QSettings>
#include <QKeyEvent>
#include <src/headers/appearancesettings.h>
#include <QMessageBox>

#define BOLD_OPEN_HTML "<b>"
#define BOLD_CLOSE_HTML "</b>"

#define CURS_OPEN_HTML "<i>"
#define CURS_CLOSE_HTML "</i>"

#define CURS_OPEN_MARKDOWN "*"
#define CURS_CLOSE_MARKDOWN "*"

#define BOLD_OPEN_MARKDOWN "**"
#define BOLD_CLOSE_MARKDOWN "**"

#define TYPE_SETTINGS "settings/file_type"


bool UnTextEdit::getIsTextChanged() const
{
    return isTextChanged;
}

void UnTextEdit::setIsTextChanged(bool value)
{
    this->isTextChanged = value;
}

short UnTextEdit::getTextType() const
{
    return textType;
}

void UnTextEdit::setTextType(short value)
{
    this->textType = value;
    auto settings = new QSettings("Kernux", "KerNotes");
    settings->setValue(TYPE_SETTINGS, value);
    delete settings;
}

QString UnTextEdit::getFileName() const
{
    return fileName;
}

void UnTextEdit::setFileName(const QString &value)
{
    this->fileName = value;
}

bool UnTextEdit::checkFileName(QStringList &fileNameList) const
{
    bool isOk = true;
    QString extension = fileNameList[fileNameList.length() - 1].split(".").back();
    qDebug() << "Extension:" << extension;
    int extensionType = 0;
    if(extension == "html")
    {
        extensionType = 1;
    } else if(extension == "md")
    {
        extensionType = 2;
    } else {
        extensionType = 3;
    }
    if(extensionType != textType)
    {
        QMessageBox::warning(nullptr, "Расширение не совпадает", "Расширение открытого вами файла не совпадает с выбранным ранее, для изменения перейдите в настройки");
//        emit openSettingsEvent();
        isOk = false;
    }
    return isOk;
}

void UnTextEdit::openFile()
{
   QSettings *settings = new QSettings("Kernux", "KerNotes");
    this->fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "Text Files (*.md *.html *.txt)");
    qDebug() << "Filename:" << fileName;
    auto splittedFile = fileName.split("/");
    checkFileName(splittedFile);
    if(this->fileName == "")
    {
        qDebug() << "File path clear!";
    } else {
        qDebug() << fileName;
        settings->setValue("lasteditedfile", fileName);
        qDebug() << "File path is not clear";
        QFile file(this->fileName);
        if(file.open(QIODevice::ReadOnly))
            setText(file.readAll());
        file.close();
    }
}

void UnTextEdit::saveFile()
{
    if(!(this->fileName == ""))
    {
            QFile file(this->fileName);
            if(file.open(QIODevice::ReadWrite))
            {
                file.write(toPlainText().toUtf8());
                qDebug() << "File Saved";
                this->isTextChanged = false;
            } else {
                qDebug() << "File not saved";
            }
            file.close();
        } else {
        // Why auto md extension? Bug or feature?
        this->fileName = QFileDialog::getSaveFileName(this, "Choose file name", QDir::currentPath(), "Text Files (*.md *.html *.txt)");
        QFile file(this->fileName);
        if(file.open(QIODevice::ReadWrite))
        {
            file.write(toMarkdown().toUtf8());
            this->isTextChanged = false;
        } else {
            qDebug() << "File not saved";
        }
        file.close();
    }
    emit fileSaved();
    

}

void UnTextEdit::placeBoldText()
{
     auto textCursor = this->textCursor();

     qDebug() << textCursor.selection().toHtml("ISO 8859-1");
     if(textCursor.hasSelection())
     {
         switch (textType) {
             case 1:
                textCursor.insertHtml(BOLD_OPEN_HTML + textCursor.selectedText() + BOLD_CLOSE_HTML);
                 break;
             case 2:
                 textCursor.insertText(BOLD_OPEN_MARKDOWN + textCursor.selectedText() + BOLD_CLOSE_MARKDOWN);
                 break;
             default:
                 qDebug() << "No selection";
         }
     } else {
         switch (textType) {
             case 1:
//                 append("<b> </b>");
//                 append(BOLD_CLOSE_HTML);
                 break;
             case 2:
                 append("****");
//                 append(BOLD_CLOSE_MARKDOWN);
                 break;
             default:
                 break;
         }
     }
}

void UnTextEdit::insertImageSnippet()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Choose file name", QDir::currentPath(), "Images (*.png *.jpeg *.jpg *.JPEG *.webp)");
    if(imagePath == "")
    {
        QMessageBox::warning(nullptr, "Изображение не выбрано", "Будет вставлена заглушка");
    }
    this->append("<img src="+imagePath+"></img>");
//    this->setText(this->toPlainText());
}


void UnTextEdit::placeCursText() {
    auto textCursor = this->textCursor();
    if (textCursor.hasSelection()) {
        qDebug() << textCursor.selection().toHtml();

        switch (textType) {
            case 1:
                textCursor.insertHtml(CURS_OPEN_HTML + textCursor.selectedText() + CURS_CLOSE_HTML);
                break;
            case 2:
                textCursor.insertText(CURS_OPEN_MARKDOWN + textCursor.selectedText() + CURS_CLOSE_MARKDOWN);
                break;
            default:
                qDebug() << "No selection";
        }
    } else {
        switch (textType) {
            case 1:
//                append("<i> </i>");
//                append(CURS_CLOSE_HTML);
                break;
            case 2:
                append("**");
//                append(CURS_CLOSE_MARKDOWN);
                break;
            default:
                break;
        }
    }
}
void UnTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        emit updateTextEdit();
        QTextEdit::keyPressEvent(event);

    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

UnTextEdit::UnTextEdit() : QTextEdit()
{
    QTextEdit();
}


void UnTextEdit::newFile()
{
    if(this->getIsTextChanged()) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "KerNotes",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::No | QMessageBox::Save  | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn == QMessageBox::No)
        {

        } else if(resBtn == QMessageBox::Yes){
            setText("");
            setFileName("");
//            setIsTextChanged(false);
            emit clearTitle();
        } else {
            this->saveFile();
//            setIsTextChanged(false);
        }
    } else {
        setFileName("");
        setText("");
        emit clearTitle();
    }
}

void UnTextEdit::increaseFontSize()
{
    qDebug() << fontPointSize();
    setFontPointSize(fontPointSize() + 10);
}

UnTextEdit::~UnTextEdit(){
    free(&textType);
}

void UnTextEdit::openLastFile(const QString& filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
        setText(file.readAll());
    file.close();
}
