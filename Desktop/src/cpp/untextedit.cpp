#include "src/headers/untextedit.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextDocumentFragment>
#include <QSettings>

#define BOLD_OPEN_HTML "<b>"
#define BOLD_CLOSE_HTML "</b>"
//TODO: Add some defines for markdown
#define CURS_OPEN_HTML "<i>"
#define CURS_CLOSE_HTML "</i>"
//TODO: refactor this
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

void UnTextEdit::openFile()
{
    this->fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath(), "Text Files (*.md *.html *.txt)");
    if(this->fileName == "")
    {
        qDebug() << "File path clear!";
    } else {
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


// TODO: Compare curs and bold in one method
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
         qDebug() << "No selection";
     }
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
            default:
                qDebug() << "No selection";
        }
    }
}

UnTextEdit::UnTextEdit() : QTextEdit()
{
    QTextEdit();
}


UnTextEdit::~UnTextEdit(){
    free(&textType);
}
