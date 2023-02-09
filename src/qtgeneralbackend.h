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
    Q_INVOKABLE void exportPack();
    Q_INVOKABLE void importPack();
    Q_INVOKABLE void removeModpack(QString name);
signals:

};

#endif // QTGENERALBACKEND_H
