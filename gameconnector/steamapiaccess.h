/* Shortly speaking, this code is a link between game session and main application
 *
 */

#pragma once
#include <QObject>
#include <QVariant>
#include <QtCore/QSharedMemory>
#include <QtCore/QBuffer>
#include <QtRemoteObjects/QRemoteObjectHost>

#include <Windows.h>

#include "steam_api.h"

class SteamAPIAccessInterface : public QObject
{
    Q_OBJECT
public:
    virtual const SteamAPICall_t getSteamAPICall() = 0;
    virtual void loadModsFromSteam() = 0;
    virtual void subscribeMod() = 0;
    //virtual void unsubscribeMod() = 0;
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
    void getModDetails() override;

public slots:
    void unsubscribeMod(uint64_t id);

signals:
    void unsubscribeModSignal();

private:
    // Working with shared memory
    template<class T>
    void setDataToSharedMemory(T& data);

    template<class T>
    bool readDataFromSharedMemory(T& data);

    bool setActionStatus(bool status);


    // SteamAPI
    void modCallback(SteamUGCQueryCompleted_t* result, bool fail);
    bool waitUntilCallNotFInished(SteamAPICall_t* call);


//Fields
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

    gameConnector.detach();
}
