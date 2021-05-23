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
    short textType;


    QString fileName;
public:
    void openLastFile(QString filePath);
    UnTextEdit();
    ~UnTextEdit();

    bool getIsTextChanged() const;
    void setIsTextChanged(bool value);

    uint8_t type;
    short getTextType() const;
    void setTextType(short value);

    QString getFileName() const;
    void setFileName(const QString &value);
    void keyPressEvent(QKeyEvent *event);
signals:
    void fileSaved();
    void updateTextEdit();
public slots:
    void openFile();
    void saveFile();

    void placeBoldText();
    void placeCursText();

};

#endif // UNTEXTEDIT_H
