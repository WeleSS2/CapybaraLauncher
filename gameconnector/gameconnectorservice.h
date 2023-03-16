#pragma once
#include <QObject>
#include <QColor>
#include <QThread>
#include <QDataStream>
#include <QtRemoteObjects/QRemoteObjectHost>

#include "steam_api.h"

struct sModsData {
    bool done;
    QColor color;

    uint64_t laucherId;
    uint64_t steamModGameId;
    uint64_t steamDataInSeconds;
    uint64_t steamAuthor;

    QString steamModName;
    QString steamPackname;

    friend QDataStream& operator<<(QDataStream& out, const sModsData& data){
        out << data.done
            << data.color
            << data.laucherId
            << data.steamModGameId
            << data.steamDataInSeconds
            << data.steamAuthor
            << data.steamModName
            << data.steamPackname;
        return out;
    }
};

class GameConnectorService : public QObject
{
    Q_OBJECT
public:
    explicit GameConnectorService(QObject *parent = nullptr);

    // From QtGeneralBackend
    bool updateMod(uint64_t id);
    bool subscribeMod(uint64_t id);
    bool unsubscribeMod(uint64_t id);


    // SteamTools.cpp ported here. READY
    void loadModsFromSteam(); // ACCESS

    // Inner functions
    void loadItemsToQuery();
    void pushVectors(uint64_t i);
    void loadItemsDataFromQuery();
    void saveToModsData();
    void itemsCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFinished(SteamAPICall_t *call);
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    // Return copy of items, i'm not sure on which thread server is running so it's save.
    // ACCESS
    QVector<SteamUGCDetails_t> getItemsDetails(){return vItemsData; };
    uint64_t getItemsAmount(){return modsAmount; };
    QVector<uint64_t> getItemsId(){return vItemsId; };
    QVector<sModsData> getModsData(){return vModsData; };
    sModsData getModData(uint64_t id);
    bool getStatus(){return loaded; };

private:
    uint64_t modsAmount;

    bool loaded = false;
    QVector<sModsData> vModsData;
    QVector<uint64_t> vItemsId;
    QVector<SteamUGCDetails_t> vItemsData;
    CCallResult<GameConnectorService, SteamUGCQueryCompleted_t> sContentCall;
    UGCQueryHandle_t qHandle;
};
