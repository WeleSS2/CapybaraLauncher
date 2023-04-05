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
    qDebug() << "Update 1";
    SteamAPICall_t hDownloadItemResult = SteamUGC()->DownloadItem(id, true);
    SteamAPI_RunCallbacks();
    qDebug() << "Update 11";
    if (waitUntilCallNotFinished(&hDownloadItemResult)) {
            qDebug() << "Update 2";
            uint64_t itemState = SteamUGC()->GetItemState(id);
            while (true)
            {
                itemState = SteamUGC()->GetItemState(id);
                // Check did item is subscribed (1) + installed (4)
                if (itemState == 5) {
                    return true;
                }
                QThread::sleep(100);
                qDebug() << "|" << id << "    " << itemState;
            }
        }
        return false;
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
            QThread::sleep(100);
        }
    }
    else
    {
        return false;
    }
}

bool GameConnectorService::unsubscribeMod(uint64_t id){
    qDebug() << "Unsub in " << id;
    if(id == 0)
    {
        return false;
    }
    SteamAPICall_t hDownloadItemResult;
    bool bItemUnsubscribed = SteamUGC()->UnsubscribeItem(id);
    if (bItemUnsubscribed)
    {
        uint64_t itemState;
        while (true)
        {
            itemState = SteamUGC()->GetItemState(id);

            if (itemState != k_EItemStateSubscribed)
            {
                qDebug() << "Unsub return";
                return true;
            }

            QThread::sleep(100);
        }
    }
    else
    {
        return false;
    }
}

sModsData GameConnectorService::getModData(uint64_t id){
    SteamUGCDetails_t data;
    UGCQueryHandle_t qHandle;
    qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&id, 1);

    SteamAPICall_t hSteamApiCall = SteamUGC()->SendQueryUGCRequest(qHandle);
    CCallResult<GameConnectorService, SteamUGCQueryCompleted_t> sContentCall;
    sContentCall.Set(hSteamApiCall, this, &GameConnectorService::modCallback);

    SteamAPI_RunCallbacks();
    waitUntilCallNotFinished(&hSteamApiCall);

    SteamUGC()->GetQueryUGCResult(qHandle, 0, &data);
    SteamUGC()->ReleaseQueryUGCRequest(qHandle);

    sModsData retData;
    retData.done = false;
    retData.color = {225, 225, 225};
    retData.steamModName = data.m_rgchTitle;
    retData.steamDataInSeconds = data.m_rtimeUpdated;
    retData.steamModGameId = id;
    retData.steamAuthor = data.m_ulSteamIDOwner;

    return retData;
}

bool GameConnectorService::waitUntilCallNotFinished(SteamAPICall_t *call)
{
    // Wait until the call is completed
    bool callCompleted = false;
    bool finished = SteamUtils()->IsAPICallCompleted(*call, &callCompleted);

    while (!callCompleted) {
        SteamAPI_RunCallbacks();
        finished = SteamUtils()->IsAPICallCompleted(*call, &callCompleted);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Add a small delay to reduce CPU usage
    }
    return callCompleted;
}

void GameConnectorService::modCallback(SteamUGCQueryCompleted_t* result, bool fail)
{
    if(fail)
        qDebug() << "Failed steam UGC query for mod";
}
