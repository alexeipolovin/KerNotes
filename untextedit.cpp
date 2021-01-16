#include "untextedit.h"

#include <QFileDialog>
#include <QFile>
#include <QDebug>

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
    for(int i = 0l; i < 100l; i++)
    {
        qDebug() << "i:" << i;
    }
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
                qDebug() << "File not saved";
    }

}

UnTextEdit::UnTextEdit() : QTextEdit()
{
    QTextEdit();
}


UnTextEdit::~UnTextEdit(){
    free(&textType);
}
