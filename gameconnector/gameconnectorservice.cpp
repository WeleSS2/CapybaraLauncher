#include "gameconnectorservice.h"

GameConnectorService::GameConnectorService(QObject *parent)
    : QObject{parent}
{

}

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
