#include "steamtools.h"
#include "windowsfunctions.h"
#include "globaldata.h"
#include "localfiles.h"
#include "utility/loggingsystem.h"

#include <filesystem>
#include <QDateTime>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>

void CSteamTools::LoadItemsToQuery()
{
    //if(!SharedGlobalDataObj->Global_LocalSettingsObj.settingsLoaded)
    //{
    //    WindowsFunctions winFun;
    //    winFun.getSteamPathFromRegistry();
    //}
    if(Vs_ItemsData.size() > 0)
    {
        isAvailable.clear();
        laucherItemId.clear();
        localModName.clear();
        VUi_ItemsId.clear();
        Vs_ItemsData.clear();
        SharedSteamToolsObj->isAvailable.clear();
        SharedSteamToolsObj->laucherItemId.clear();
        SharedSteamToolsObj->localModName.clear();
        SharedSteamToolsObj->VUi_ItemsId.clear();
        SharedSteamToolsObj->Vs_ItemsData.clear();
    }

    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount = SteamUGC()->GetNumSubscribedItems();

    if(SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount > 0){
        for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
        {
            pushVectors(i);
        }
        SteamUGC()->GetSubscribedItems(&VUi_ItemsId[0], SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount);
        qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&VUi_ItemsId[0], SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount);
    }
    else
        LoggingSystem::saveLog("steamtools.cpp: LoadItemToQuery: Subscribed items is 0");
}

void CSteamTools::pushVectors(int value){
    laucherItemId.emplace_back(value);
    VUi_ItemsId.emplace_back();
    Vs_ItemsData.emplace_back();
    SharedGlobalDataObj->Global_ModsDataObj.emplace_back();
}

void CSteamTools::LoadItemsDataFromQuery()
{
    SteamAPICall_t hSteamApiCall = SteamUGC()->SendQueryUGCRequest(qHandle);
    sContentCall.Set(hSteamApiCall,
                     this,
                     &CSteamTools::ItemsCallback);
    SteamAPI_RunCallbacks();
    // Waiting on load, synchronising
    bool finished = SteamUtils()->IsAPICallCompleted(hSteamApiCall, &finished);
    while(!finished)
    {
        finished = SteamUtils()->IsAPICallCompleted(hSteamApiCall, &finished);
    }
    SteamAPI_RunCallbacks();



    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gamePath.toStdString()
            + "\\steamapps\\workshop\\content\\"
            + std::to_string(SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gameId);
    for (int i = 0; i < SharedSteamToolsObj->VUi_ItemsId.size(); ++i)
        {
            std::string folder_path{path + "\\" + std::to_string(SharedSteamToolsObj->VUi_ItemsId[i])};

            // Check did mod exist locally
            if(std::filesystem::exists(folder_path)){
                for (auto const& dir_entry : std::filesystem::directory_iterator{folder_path})
                {
                    std::string temp{dir_entry.path().string()};
                    std::string s2 = temp.substr(temp.size() - 4, 4);
                    if (s2 == "pack")
                    {
                        SharedSteamToolsObj->isAvailable.emplaceBack(1);
                        SharedGlobalDataObj->Global_ModsDataObj[i].color = {255, 255, 255};
                        temp.erase(0, folder_path.size() + 1);
                        SharedSteamToolsObj->localModName.emplaceBack(temp);
                    }
                }

                // Check did mod can be updated
                QFileInfo fileInfo(QString::fromStdString(folder_path));
                if(fileInfo.exists()){
                    QDateTime lastModified = fileInfo.lastModified();
                    if(SharedSteamToolsObj->Vs_ItemsData[i].m_rtimeUpdated > lastModified.toMSecsSinceEpoch() / 1000)
                    {
                        SharedGlobalDataObj->Global_ModsDataObj[i].color = {225, 225, 0};
                    }
                }
            }
            else
            {
                SharedSteamToolsObj->isAvailable.emplaceBack(0);
                SharedGlobalDataObj->Global_ModsDataObj[i].color = {255, 55, 55};
                SharedSteamToolsObj->localModName.emplaceBack("This mod is not available locally");
            }
        }



    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        SharedGlobalDataObj->Global_ModsDataObj[i].done = false;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamModName = SharedSteamToolsObj->Vs_ItemsData[i].m_rgchTitle;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamDataInSeconds = SharedSteamToolsObj->Vs_ItemsData[i].m_rtimeUpdated;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamPackname = SharedSteamToolsObj->localModName[i];
        SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId = SharedSteamToolsObj->VUi_ItemsId[i];
        SharedGlobalDataObj->Global_ModsDataObj[i].steamAuthor = SharedSteamToolsObj->Vs_ItemsData[i].m_ulSteamIDOwner;
        if(SharedSteamToolsObj->isAvailable[i] == false){
            SharedGlobalDataObj->Global_ModsDataObj[i].steamModName = "Mod has been removed from steam";
        }
    }
}

void CSteamTools::ItemsCallback(SteamUGCQueryCompleted_t * result, bool fail)
{
    if(fail)
        std::cout << "Failed steam UGC query";

    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        SteamUGC()->GetQueryUGCResult(qHandle, i, &Vs_ItemsData[i]);
    }

    SteamUGC()->ReleaseQueryUGCRequest(qHandle);
}

// Run GameConnector with current steam_appid.txt
bool SteamAPIAccess::runGameSteamAPI(){
    //QProcess process;
    //process.start("GameConnector.exe");
    //process.waitForFinished();
    //return true;

    std::string run = "start \"\" \"GameConnector.exe\"";
    int result = system(run.c_str());
    if(result)
    {
        return true;
    }
    else
    {
        int limit = 0;
        QProcess process;
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq GameConnector.exe");
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        while(limit < 200)
        {
            if(output.contains("GameConnector.exe"))
            {
                qDebug() << "GameChanger is on";
                return true;
            }
            limit++;
            Sleep(10);
        }
    }
    return false;
}

// Check did any GameConnector with is running, if yes kill it.
bool SteamAPIAccess::closeGameSteamAPI(){
    QProcess process;
    process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq GameConnector.exe");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    if(output.contains("GameConnector.exe")){
        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "GameConnector.exe");
        return true;
    }
    else
        return true;

    LoggingSystem::saveLog("steamtools.cpp: closeGameSteamAPI: Closing GameConnector when closing a Capybara Launcher failed!");
}

bool SteamAPIAccess::setWorkToDo(){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << false;

    if(!actionStatus.attach()){
        actionStatus.create(buffer.size());
    }

    actionStatus.lock();
    char *to = (char*)actionStatus.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(actionStatus.size(), buffer.size()));
    actionStatus.unlock();
    return true;
}

bool SteamAPIAccess::synchronizeWithGameConnector(){
    Sleep(100);
    if(!actionStatus.attach()){
        return false;
    }

    QByteArray buffer;
    buffer.resize(actionStatus.size());
    actionStatus.lock();
    const char *from = (const char*)actionStatus.constData();
    char *to = buffer.data();
    memcpy(to, from, qMin(actionStatus.size(), buffer.size()));
    actionStatus.unlock();

    bool status;
    QDataStream stream(buffer);
    stream >> status;

    if(!status)
        return false;

    actionStatus.detach();
    return true;
}

void SteamAPIAccess::subscribeMod(uint64_t id){
    SteamAPICall_t hAPICall;
    bool bItemSubscribed = SteamUGC()->SubscribeItem(id);
    if (bItemSubscribed)
    {
        uint64_t downloadBytes, totalBytes;
        while (true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            if (downloadBytes == totalBytes)
            {
                break;
            }

            Sleep(10);
        }
    }
}

void SteamAPIAccess::unsubscribeMod(uint64_t id){
    SteamAPICall_t hApiCall;
    bool bItemUnSubscribed = SteamUGC()->UnsubscribeItem(id);
    if (bItemUnSubscribed)
    {
        uint64_t downloadBytes, totalBytes;
        while (true)
        {
            SteamUGC()->GetItemDownloadInfo(id, &downloadBytes, &totalBytes);
            if (downloadBytes == 0 && totalBytes == 0)
            {
                break;
            }

            Sleep(10);
        }
    }
}

SteamUGCDetails_t SteamAPIAccess::getModDetails(uint64_t id){
    SteamUGCDetails_t data;
    UGCQueryHandle_t qHandle;
    qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&id, 1);

    SteamAPICall_t hSteamApiCall = SteamUGC()->SendQueryUGCRequest(qHandle);
    CCallResult<SteamAPIAccess, SteamUGCQueryCompleted_t> sContentCall;
    sContentCall.Set(hSteamApiCall, this, &SteamAPIAccess::modCallback);

    SteamAPI_RunCallbacks();
    waitUntilCallNotFinished(&hSteamApiCall);

    SteamUGC()->GetQueryUGCResult(qHandle, 0, &data);
    SteamUGC()->ReleaseQueryUGCRequest(qHandle);


    return data;
}

void SteamAPIAccess::modCallback(SteamUGCQueryCompleted_t* result, bool fail)
{
    if(fail)
        std::cout << "Failed steam UGC query for mod";
}

bool SteamAPIAccess::waitUntilCallNotFinished(SteamAPICall_t *call)
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
