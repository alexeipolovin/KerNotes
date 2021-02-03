//
// Created by Kernux on 1/31/2021.
//

#ifndef KERNOTES_JSPROVIDER_H
#define KERNOTES_JSPROVIDER_H
#include <QObject>

class JsProvider : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged FINAL)
public:
    explicit JsProvider(QObject *parent = nullptr) : QObject(parent) {}

    void setText(const QString &text);

    signals:
            void textChanged(const QString &text);

private:
    QString m_text;
};


#endif //KERNOTES_JSPROVIDER_H
