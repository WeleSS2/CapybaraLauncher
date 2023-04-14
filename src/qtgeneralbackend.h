#ifndef QTGENERALBACKEND_H
#define QTGENERALBACKEND_H

#include <QObject>
#include "globaldata.h"
#include "qt/customModules/tasklist.h"

class QtGeneralBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentGameId READ getCurrentGameId WRITE setCurrentGameId NOTIFY currentGameIdChanged)
    Q_PROPERTY(bool unsafeMode READ getUnsafeMode WRITE setUnsafeMode NOTIFY unsafeModeChanged)
public:
    explicit QtGeneralBackend(QObject *parent = nullptr, TaskListList *taskListPtr = nullptr);

    Q_INVOKABLE void startGame();
    Q_INVOKABLE void exportPack();
    Q_INVOKABLE void importPack();
    Q_INVOKABLE void removeModpack(QString name);
    Q_INVOKABLE bool updateAvialable();

    Q_INVOKABLE void addTask(uint64_t id, QString taskName);
    Q_INVOKABLE void removeMod(uint64_t id);
    Q_INVOKABLE void openLocalFiles(uint64_t id);
    Q_INVOKABLE void makeLocalCopy(uint64_t id);
    Q_INVOKABLE void removeLocalCopy(uint64_t id);
    Q_INVOKABLE void openInRPFM(uint64_t id);
    Q_INVOKABLE void closeSteamAPIIfOn();

    Q_INVOKABLE void closeApp();
    Q_INVOKABLE void saveDefaultGame();

    int getCurrentGameId() const;
    void setCurrentGameId(int id);

    bool getUnsafeMode() const {return GlobalDataObj->LocalSettingsObj.unsafeMode; };
    void setUnsafeMode(bool status) {GlobalDataObj->LocalSettingsObj.unsafeMode = status; };
signals:

    void currentGameIdChanged(int newGameId);
    void unsafeModeChanged(bool status);

private:
    int m_currentGameId = 0;
    TaskListList *taskListPtr;
};

#endif // QTGENERALBACKEND_H
