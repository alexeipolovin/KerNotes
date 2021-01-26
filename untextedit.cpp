#include "untextedit.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextDocumentFragment>

#define BOLD_OPEN_HTML "<b>"
#define BOLD_CLOSE_HTML "</b>"

#define CURS_OPEN_HTML "<i>"
#define CURS_CLOSE_HTML "</i>"


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


// Compare in one method
void UnTextEdit::placeBoldText()
{
     auto textCursor = this->textCursor();

     qDebug() << textCursor.selection().toHtml("ISO 8859-1");
     if(textCursor.hasSelection())
     {
         if(this->textType == 1)
            textCursor.insertHtml(BOLD_OPEN_HTML + textCursor.selectedText() + BOLD_CLOSE_HTML);
     } else {
         qDebug() << "No Selection";
     }
}

void UnTextEdit::placeCursText()
{
    auto textCursor = this->textCursor();
    if(textCursor.hasSelection())
    {
        qDebug() << textCursor.selection().toHtml();

        if(this->textType == 1)
            textCursor.insertHtml(CURS_OPEN_HTML + textCursor.selectedText() + CURS_CLOSE_HTML);
    } else {
        qDebug() << "No selection";
    }
}

UnTextEdit::UnTextEdit() : QTextEdit()
{
    QTextEdit();
}


UnTextEdit::~UnTextEdit(){
    free(&textType);
}
