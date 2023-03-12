/* Shortly speaking, this code is a link between game session and main application
 *
 */

#pragma once
#include <QObject>
#include <QtCore/QSharedMemory>
#include "steam_api.h"

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

class SteamAPIAccess : public QObject, public SteamAPIAccessInterface
{
    Q_OBJECT
public:
    explicit SteamAPIAccess(QObject* parent = nullptr);

    const SteamAPICall_t getSteamAPICall() override;
    void loadModsFromSteam() override;
    void subscribeMod() override;
    void unsubscribeMod() override;
    void getModDetails() override;

private:
    // Working with shared memory
    template<class T>
    void setDataToSharedMemory(T& data);

    template<class T>
    void readDataFromSharedMemory(T& data);

    void setActionStatus(bool& status);


    // SteamAPI
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFInished(SteamAPICall_t* call);


//Fields
    QSharedMemory actionStatus{"ActionStatus"};
    QSharedMemory gameConnector{"GameConnector"};
    SteamAPICall_t hSteamAPiCall;
};
