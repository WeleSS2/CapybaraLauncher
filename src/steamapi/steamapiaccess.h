#pragma once

#include <QObject>
#include <QVector>
#include <QLocalSocket>
#include "steam_api.h"

class SteamApiAccess : public QObject
{
    Q_OBJECT
public:
    explicit SteamApiAccess(QObject *parent = nullptr);

    // Run GameConnector which manage SteamApi for a game
    bool runGameSteamAPI();

    // Check did GameConnector which manage SteamAPi for a game is running if yes kill it
    bool closeGameSteamAPI();

    // Load Mods data through steam on server
    void loadModsDataSteam();

    // Get Mods data
    void getModsData();
    // Set local path for every mod
    void setModsPackname();

    // Connect to the server
    void linkToServer(QLocalSocket* socket, int maxAttempts);



    void subscribeMod(uint64_t id);
    void unsubscribeMod(uint64_t id);
    SteamUGCDetails_t getModDetails(uint64_t id);
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFinished(SteamAPICall_t* call);

    void loadItemsDataToVector();

    QString callTestFunction();

private slots:

private:
    QVector<SteamUGCDetails_t> vItemsData;

    SteamAPICall_t hSteamAPiCall;

    //QRemoteObjectHost* m_remoteHost;
    //QSharedPointer<GameConnectorService> m_connectorService;

};

