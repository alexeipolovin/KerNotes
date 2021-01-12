#ifndef UNTEXTEDIT_H
#define UNTEXTEDIT_H
#include <QObject>
#include <QTextEdit>

class UnTextEdit : public QTextEdit
{
    Q_OBJECT
private:
    bool isTextChanged;

    // 1 - HTML
    // 2 - MD
    // 3 - TXT
    short textType;


    QString fileName;
public:
    UnTextEdit();
    ~UnTextEdit();

    bool getIsTextChanged() const;
    void setIsTextChanged(bool value);

    short getTextType() const;
    void setTextType(short value);

    QString getFileName() const;
    void setFileName(const QString &value);

public slots:
    void openFile();

    void saveFile();
};

#endif // UNTEXTEDIT_H
