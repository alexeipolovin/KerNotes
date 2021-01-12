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
    isTextChanged = value;
}

short UnTextEdit::getTextType() const
{
    return textType;
}

void UnTextEdit::setTextType(short value)
{
    textType = value;
}

QString UnTextEdit::getFileName() const
{
    return fileName;
}

void UnTextEdit::setFileName(const QString &value)
{
    fileName = value;
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
    if(!(this->fileName == "")) {
            QFile file(this->fileName);
            if(file.open(QIODevice::ReadWrite))
            {
                file.write(toPlainText().toUtf8());
                qDebug() << "File Saved";
            } else {
            }
            file.close();
        } else {
    }

}

UnTextEdit::UnTextEdit() : QTextEdit()
{

}


UnTextEdit::~UnTextEdit(){}
