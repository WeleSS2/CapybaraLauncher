#pragma once
#include <QObject>
#include <QVariant>
#include <QtCore/QSharedMemory>
#include <QtCore/QDataStream>
#include <QtCore/QCoreApplication>
#include <QtCore/QBuffer>
#include <QRemoteObjectHost>


#include "../gameconnector/gameconnectorservice.h"

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
/* To move/remove idk yet
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
*/

class SteamAPIAccess : public QObject//, public SteamAPIAccessInterface
{
    Q_OBJECT
public:
    explicit SteamAPIAccess(QObject* parent = nullptr);
    bool runGameSteamAPI();
    bool closeGameSteamAPI();


    void subscribeMod(uint64_t id);
    void unsubscribeMod(uint64_t id);
    SteamUGCDetails_t getModDetails(uint64_t id);
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFinished(SteamAPICall_t* call);

private:

    SteamAPICall_t hSteamAPiCall;
};
