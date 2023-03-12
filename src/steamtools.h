#pragma once
#include <QObject>
#include <QVariant>
#include <QtCore/QSharedMemory>
#include <QtCore/QDataStream>
#include <QtCore/QCoreApplication>
#include <QtCore/QBuffer>

#include "iostream"
#include "steam_api.h"
#include "isteamclient.h"
#include "steam_gameserver.h"
#include "vector"
#include "algorithm"

// To rework and if possible need to be removed and moved into GameConnector
class CSteamTools : public QObject
{
    Q_OBJECT
public:
    uint32 Ui_NumberOfItems;
    QVector<bool> isAvailable;
    QVector<uint32> laucherItemId;
    QVector<std::string> localModName;
    QVector<uint64> VUi_ItemsId;
    QVector<SteamUGCDetails_t> Vs_ItemsData;
    CCallResult<CSteamTools, SteamUGCQueryCompleted_t> sContentCall;

    UGCQueryHandle_t qHandle;

    explicit CSteamTools(QObject *parent = nullptr){};


    void pushVectors(int value);

public slots:
    void LoadItemsToQuery();
    void LoadItemsDataFromQuery();
    void ItemsCallback(SteamUGCQueryCompleted_t * result, bool fail);
};
inline auto SharedSteamToolsObj = std::make_shared<CSteamTools>();

class SteamAPIAccessInterface : public QObject
{
    Q_OBJECT
public:
    virtual const SteamAPICall_t getSteamAPICall() = 0;
    virtual void loadModsFromSteam() = 0;
    virtual void subscribeMod() = 0;
    virtual void unsubscribeMod() = 0;
    virtual void getModDetails() = 0;
};


class SteamAPIAccess : public QObject//, public SteamAPIAccessInterface
{
    Q_OBJECT
public:
    bool runGameSteamAPI();
    bool closeGameSteamAPI();

    template<class T>
    void setDataToSharedMemory(T& data);

    template<class T>
    bool readDataFromSharedMemory(T& data);

    bool setWorkToDo();

    bool synchronizeWithGameConnector();


    // Need to be reworked
    void subscribeMod(uint64_t id);
    void unsubscribeMod(uint64_t id);
    SteamUGCDetails_t getModDetails(uint64_t id);
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFinished(SteamAPICall_t* call);

private:
    QSharedMemory actionStatus{"ActionStatus"};
    QSharedMemory gameConnector{"GameConnector"};
    SteamAPICall_t hSteamAPiCall;
};

// Read data from gameConnector
template<class T>
bool SteamAPIAccess::readDataFromSharedMemory(T& data)
{
    // Attach to the shared memory object
    if (!gameConnector.attach()) {
        qDebug() << "Failed to attach to shared memory:" << gameConnector.errorString();
        qDebug() << gameConnector.attach();
        return false;
    }

    // Read the data from the shared memory
    QByteArray buffer;
    buffer.resize(gameConnector.size());
    gameConnector.lock();
    const char *from = (const char*)gameConnector.constData();
    char *to = buffer.data();
    memcpy(to, from, qMin(gameConnector.size(), buffer.size()));
    gameConnector.unlock();

    QDataStream stream(buffer);
    stream >> data;

    // Detach from the shared memory object
    gameConnector.detach();

    return true;
}

// Set data to gameConnector
template<class T>
void SteamAPIAccess::setDataToSharedMemory(T& data){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << data;

    if(gameConnector.attach())
    {
        if(buffer.size() != gameConnector.size())
        {
            gameConnector.detach();
            gameConnector.create(buffer.size());
        }
    }
    else
        gameConnector.create(buffer.size());

    gameConnector.lock();
    char *to = (char*)gameConnector.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(gameConnector.size(), buffer.size()));
    gameConnector.unlock();
}


