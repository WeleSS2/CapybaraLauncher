#include "gameconnectorservice.h"

GameConnectorService::GameConnectorService(QObject *parent)
    : QObject{parent}
{

}
//---------------  Modslist e.t.c---------------
void GameConnectorService::loadModsFromSteam(){
    loadItemsToQuery();
    loadItemsDataFromQuery();
    saveToModsData();
}

void GameConnectorService::loadItemsToQuery(){
    modsAmount = SteamUGC()->GetNumSubscribedItems();
    qDebug() << "L" << modsAmount << SteamUGC()->GetNumSubscribedItems();
    if(modsAmount > 0)
    {
        // Old function copy
        for(int i = 0; i < modsAmount; ++i){
            pushVectors(i);
        }

        SteamUGC()->GetSubscribedItems(&vItemsId[0], modsAmount);
        qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&vItemsId[0], modsAmount);
    }
    else // Implement later Logs system LOG01
        qDebug() << "GameConnectorService: loadItemsToQuery: Error when laoading items to query";
}

void GameConnectorService::pushVectors(uint64_t value){
    vItemsId.emplace_back();
    vItemsData.emplace_back();
}

void GameConnectorService::loadItemsDataFromQuery(){
    SteamAPICall_t hSteamAPICall = SteamUGC()->SendQueryUGCRequest(qHandle);
    sContentCall.Set(hSteamAPICall,
                     this,
                     &GameConnectorService::itemsCallback);

    SteamAPI_RunCallbacks();

    bool finished = SteamUtils()->IsAPICallCompleted(hSteamAPICall, &finished);
    while(!finished){
        finished = SteamUtils()->IsAPICallCompleted(hSteamAPICall, &finished);
    }

    SteamAPI_RunCallbacks();
}

void GameConnectorService::saveToModsData(){
    for(int i = 0; i < vItemsData.size(); ++i){
        vModsData.emplaceBack();
        vModsData[i].done = false;
        vModsData[i].color = {255, 255, 255};
        vModsData[i].laucherId = i;
        vModsData[i].steamModGameId = vItemsId[i];
        vModsData[i].steamDataInSeconds = vItemsData[i].m_rtimeUpdated;
        vModsData[i].steamAuthor = vItemsData[i].m_ulSteamIDOwner;
        vModsData[i].steamModName = vItemsData[i].m_rgchTitle;
        vModsData[i].steamPackname = "";
    }
    qDebug() << vModsData.size();
    loaded = true;
}

void GameConnectorService::itemsCallback(SteamUGCQueryCompleted_t* result, bool fail){
    if(fail) // LOG01
        qDebug() << "GameConnectorService: itemsCallback: Failed to load UGC Query";

    for(int i = 0; i < modsAmount; ++i){
        SteamUGC()->GetQueryUGCResult(qHandle, i, &vItemsData[i]);
    }

    SteamUGC()->ReleaseQueryUGCRequest(qHandle);
}
//---------------- Single mods and others

bool GameConnectorService::updateMod(uint64_t id){
    SteamAPICall_t hDownloadItemResult = SteamUGC()->DownloadItem(id, true);
    SteamAPI_RunCallbacks();

    waitUntilCallNotFinished(&hDownloadItemResult);
    return true;
}

bool GameConnectorService::subscribeMod(uint64_t id){
    SteamAPICall_t hDownloadItemResult;
    bool bItemSubscribed = SteamUGC()->SubscribeItem(id);
    if (bItemSubscribed)
    {
        uint64_t downloadBytes, totalBytes;
        while (true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            if (downloadBytes == totalBytes)
            {
                return true;
            }
            QThread::sleep(50);
        }
    }
    else
    {
        return false;
    }
}

bool GameConnectorService::unsubscribeMod(uint64_t id){
    if(id == 0)
    {
        return false;
    }
    SteamAPICall_t hDownloadItemResult;
    bool bItemUnsubscribed = SteamUGC()->UnsubscribeItem(id);
    if (bItemUnsubscribed)
    {
        uint64_t downloadBytes, totalBytes;
        while (true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            qDebug() << id << downloadBytes << totalBytes;

            if (downloadBytes == 0 && totalBytes == 0)
            {
                return true;
            }

            QThread::sleep(50);
        }
    }
    else
    {
        return false;
    }
}

bool GameConnectorService::waitUntilCallNotFinished(SteamAPICall_t *call)
{
    // Wait until the download is completed
    bool callCompleted = false;
    bool finished = SteamUtils()->IsAPICallCompleted(*call, &callCompleted);

    while (!callCompleted) {
        SteamAPI_RunCallbacks();
        finished = SteamUtils()->IsAPICallCompleted(*call, &callCompleted);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Add a small delay to reduce CPU usage
    }
    return callCompleted;
}
