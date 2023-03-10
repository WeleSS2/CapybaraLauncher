#pragma once
#include <QObject>
#include <QVariant>

#include "iostream"
#include "steam_api.h"
#include "isteamclient.h"
#include "steam_gameserver.h"
#include "vector"
#include "algorithm"

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

class steamAPIAccess {
public:
    bool runGameSteamAPI();
    bool closeGameSteamAPI();

    void subscribeMod(uint64_t id);
    void unsubscribeMod(uint64_t id);
    SteamUGCDetails_t getModDetails(uint64_t id);
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFinished(SteamAPICall_t* call);



protected:

private:
};
