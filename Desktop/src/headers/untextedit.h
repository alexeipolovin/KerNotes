/*
 * Copyright (c) 2021 Alexei Polovin (alexeipolovin@gmail.com)

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UNTEXTEDIT_H
#define UNTEXTEDIT_H
#include <QObject>
#include <QTextEdit>

class UnTextEdit : public QTextEdit
{
    Q_OBJECT
private:
    bool isTextChanged = false;

    // 1 - HTML
    // 2 - MD
    // 3 - TXT
    short textType{};


    QString fileName;

    bool checkFileName(QStringList &fileNameList) const;
public:
    void openLastFile(const QString& filePath);
    UnTextEdit();
    ~UnTextEdit() override;

    bool getIsTextChanged() const;
    void setIsTextChanged(bool value);

    uint8_t type{};
    short getTextType() const;
    void setTextType(short value);

    QString getFileName() const;
    void setFileName(const QString &value);
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void openSettingsEvent();
    void clearTitle();
    void fileSaved();
    void updateTextEdit();
public slots:
    void increaseFontSize();

    void openFile();
    void saveFile();
    void newFile();

    void placeBoldText();
    void placeCursText();
    void insertImageSnippet();
};

#endif // UNTEXTEDIT_H
