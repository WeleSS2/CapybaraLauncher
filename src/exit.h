#ifndef EXIT_H
#define EXIT_H

#include <iostream>
#include <QObject>
#include <QVariant>

class cexit : public QObject
{
    Q_OBJECT
public:
    explicit cexit(QObject *parent = nullptr){};
public slots:
    void closeApp();
};
#endif // EXIT_H
