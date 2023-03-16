#ifndef QTGENERALBACKEND_H
#define QTGENERALBACKEND_H

#include <QObject>

class QtGeneralBackend : public QObject
{
    Q_OBJECT
public:
    explicit QtGeneralBackend(QObject *parent = nullptr);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void exportPack();
    Q_INVOKABLE void importPack();
    Q_INVOKABLE void removeModpack(QString name);
    Q_INVOKABLE bool updateAvialable();
    Q_INVOKABLE void updateLauncher();


    Q_INVOKABLE void updateMod(uint64_t id);
    Q_INVOKABLE void addMod(uint64_t id);
    Q_INVOKABLE void removeMod(uint64_t id);
    Q_INVOKABLE void openLocalFiles(uint64_t id);
    Q_INVOKABLE void makeLocalCopy(uint64_t id);
    Q_INVOKABLE void removeLocalCopy(uint64_t id);
    Q_INVOKABLE void openInRPFM(uint64_t id);
    Q_INVOKABLE void closeSteamAPIIfOn();

    Q_INVOKABLE void closeApp();

signals:

};

#endif // QTGENERALBACKEND_H
