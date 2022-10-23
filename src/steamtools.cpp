#include "steamtools.h"
#include "windowsfunctions.h"
#include "globaldata.h"
#include "localfiles.h"

#include <filesystem>

void CSteamTools::LoadItemsToQuery()
{
    if(!SharedGlobalDataObj->Global_LocalSettingsObj.settingsLoaded)
    {
        WindowsFunctions winFun;
        winFun.getSteamPathFromRegistry();
    }

    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount = SteamUGC()->GetNumSubscribedItems();
    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        laucherItemId.emplace_back(i);
        VUi_ItemsId.emplace_back();
        Vs_ItemsData.emplace_back();
        SharedGlobalDataObj->Global_ModsDataObj.emplace_back();
    }

    SteamUGC()->GetSubscribedItems(&VUi_ItemsId[0], SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount);

    qHandle = SteamUGC()->CreateQueryUGCDetailsRequest(&VUi_ItemsId[0], SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount);
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





    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.gamepath + "\\steamapps\\workshop\\content\\1142710";
    for (int i = 0; i < SharedSteamToolsObj->VUi_ItemsId.size(); ++i)
        {
        std::string folder_path{path + "\\" + std::to_string(SharedSteamToolsObj->VUi_ItemsId[i])};
        for (auto const& dir_entry : std::filesystem::directory_iterator{folder_path})
            {
                std::string temp{dir_entry.path().string()};
                std::string s2 = temp.substr(temp.size() - 4, 4);
                if (s2 == "pack")
                {
                    temp.erase(0, folder_path.size() + 1);
                    SharedSteamToolsObj->localModName.emplaceBack(temp);
                }
            }
        }





    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        SharedGlobalDataObj->Global_ModsDataObj[i].laucherId = laucherItemId[i];
        SharedGlobalDataObj->Global_ModsDataObj[i].done = false;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamModName = SharedSteamToolsObj->Vs_ItemsData[i].m_rgchTitle;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamDataInSeconds = SharedSteamToolsObj->Vs_ItemsData[i].m_rtimeUpdated;
        SharedGlobalDataObj->Global_ModsDataObj[i].steamPackname = SharedSteamToolsObj->localModName[i];
        SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId = SharedSteamToolsObj->VUi_ItemsId[i];
        SharedGlobalDataObj->Global_ModsDataObj[i].steamAuthor = SharedSteamToolsObj->Vs_ItemsData[i].m_ulSteamIDOwner;
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
