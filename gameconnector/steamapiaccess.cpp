#include "steamapiaccess.h"


SteamAPIAccess::SteamAPIAccess(QObject *parent)
    : QObject(parent)
{
    //QRemoteObjectHost host(QUrl(QStringLiteral("local:gameConnectorService")));
    //host.enableRemoting(this, "gameConnectorService");
}

const SteamAPICall_t SteamAPIAccess::getSteamAPICall(){
    return hSteamAPiCall;
}

void SteamAPIAccess::loadModsFromSteam(){

}

void SteamAPIAccess::subscribeMod()
{
    uint64_t id;
    readDataFromSharedMemory(id);
    SteamAPICall_t hAPICall;
    bool bItemSubscribed = SteamUGC()->SubscribeItem(id);
    if(bItemSubscribed)
    {
        uint64_t downloadBytes, totalBytes;
        while(true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            if(downloadBytes == totalBytes)
            {
                break;
            }
            Sleep(10);
        }
    }
    setActionStatus(true);
}

void SteamAPIAccess::unsubscribeMod(uint64_t id)
{
    SteamAPICall_t hAPiCall;
    bool bItemSubscribed = SteamUGC()->UnsubscribeItem(id);
    if(bItemSubscribed){
        uint64_t downloadBytes, totalBytes;
        while(true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            if(downloadBytes == 0 && totalBytes == 0){
                break;
            }

            Sleep(10);
        }
    }
    setActionStatus(true);
}

void SteamAPIAccess::getModDetails()
{

}

bool SteamAPIAccess::setActionStatus(bool status){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << status;

    if(!actionStatus.attach()){
        actionStatus.create(buffer.size());
    }

    actionStatus.lock();
    char *to = (char*)actionStatus.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(actionStatus.size(), buffer.size()));
    actionStatus.unlock();
    actionStatus.detach();

    return true;
}

void SteamAPIAccess::modCallback(SteamUGCQueryCompleted_t *result, bool fail)
{

}

bool SteamAPIAccess::waitUntilCallNotFInished(SteamAPICall_t *call)
{
    return false;
}
