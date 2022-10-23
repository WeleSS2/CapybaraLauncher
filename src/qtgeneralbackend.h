#ifndef QTGENERALBACKEND_H
#define QTGENERALBACKEND_H

#include <QObject>
#include "steam_api.h"

class QtGeneralBackend : public QObject
{
    Q_OBJECT
public:
    explicit QtGeneralBackend(QObject *parent = nullptr);

    Q_INVOKABLE void startGame();
signals:

};

#endif // QTGENERALBACKEND_H
