#include "qDebug.h"
#include "qguiapplication.h"
#include <Windows.h>
#include <cstdlib>
#include <filesystem>
#include <QClipboard>

#include "qtgeneralbackend.h"
#include "globaldata.h"
#include "github/githubupdater.h"
#include "steamtools.h"

QtGeneralBackend::QtGeneralBackend(QObject *parent)
    : QObject{parent}
{

}

void QtGeneralBackend::startGame()
{
    bool steamOn = SteamAPI_Init();
    std::string run = "";

    run += "start \"\" \"" + SharedGlobalDataObj->Global_LocalSettingsObj.gamepath
            + "\\steamapps\\common\\Total War WARHAMMER III\\Warhammer3.exe\"";

    std::vector<ModsData> localModsList = SharedGlobalDataObj->Global_ModsDataObj;


    std::sort(localModsList.begin(),
              localModsList.end(),
              [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });


    for(auto& i: localModsList){
        if(i.done){
            run += "  add_working_directory  \"" +
                    SharedGlobalDataObj->Global_LocalSettingsObj.gamepath +
                    "\\steamapps\\workshop\\content\\1142710\\" +
                    std::to_string(i.steamModGameId) +
                    "\";" +
                    " mod \"" + i.steamPackname + "\";";
        }
    }

    //qDebug() << QString::fromStdString(run);
    int result = system(run.c_str());
}

void QtGeneralBackend::exportPack(){
    std::string exportString = "";
    for(auto& i: SharedGlobalDataObj->Global_ModsDataObj){
        if(i.done){
            exportString += std::to_string(i.steamModGameId) + "|";
        }
    }
    QClipboard *clip = QGuiApplication::clipboard();
    clip->setText(QString::fromStdString(exportString));
}

void QtGeneralBackend::importPack(){

    QClipboard *clip = QGuiApplication::clipboard();

      // Create a string from the clipboard data
    std::string importList{QString(clip->text()).toStdString()};

    std::vector<std::pair<uint64_t, bool>> mods;

      std::string number = "";


      // Load mods
      for(int i = 0; i < importList.size(); ++i){
            number+= importList[i];
            if(importList[i] == '|'){
                mods.emplace_back(std::stoul(number), false);
                number = "";
            }
      }

      // Enable mods
      for(auto& i: SharedGlobalDataObj->Global_ModsDataObj)
      {
          for(int j = 0; j < mods.size() ; ++j){
              if(i.steamModGameId == mods[j].first)
              {
                  i.done = true;
                  mods[j].second = true;
              }
          }
      }
      // Check did all of the mods are downloaded and available if not download them
      steamAPIAccess SteamAPI;
      for(int i = 0; i < mods.size() ; ++i){
          if(!mods[i].second)
          {
              addMod(mods[i].first);
              for(auto& j: SharedGlobalDataObj->Global_ModsDataObj)
              {
                  if(j.steamModGameId == mods[i].first)
                  j.done = true;
              }
          }
      }
}

void QtGeneralBackend::removeModpack(QString name){
        std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.localPath +
                "\\Modpacks\\" + name.toStdString() + ".txt";
        if(std::filesystem::exists(path)){
            std::filesystem::remove(path);
        }
}

bool QtGeneralBackend::updateAvialable(){
    GithubUpdater obj;
    return obj.getVersionInfo();
}

void QtGeneralBackend::updateLauncher(){
    GithubUpdater obj;
    obj.getVersionInfo();
    obj.downloadPatch();
    obj.openPatchFile();
    obj.patchAndResetApp();
}

void QtGeneralBackend::addMod(uint64_t id){
    steamAPIAccess SteamAPI;
    SteamAPI.subscribeMod(id);

    SteamUGCDetails_t modDetails = SteamAPI.getModDetails(id);


    // Download the item
    SteamAPICall_t hDownloadItemResult = SteamUGC()->DownloadItem(id, true);
    SteamAPI_RunCallbacks();


    SteamAPI.waitUntilCallNotFinished(&hDownloadItemResult);

    // Insert item into launcher
    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount++;


    SharedGlobalDataObj->Global_ModsDataObj.emplace_back();
    int modPosition = SharedGlobalDataObj->Global_ModsDataObj.size() - 1;

    SharedGlobalDataObj->Global_ModsDataObj[modPosition].laucherId = modPosition;
    SharedGlobalDataObj->Global_ModsDataObj[modPosition].done = false;
    SharedGlobalDataObj->Global_ModsDataObj[modPosition].color = {255, 255, 255};
    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamModName = modDetails.m_rgchTitle;
    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamDataInSeconds = modDetails.m_rtimeUpdated;
    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.gamepath +
            "\\steamapps\\workshop\\content\\1142710\\" + std::to_string(id);
    while(1){
        if(std::filesystem::exists(path)){
            for (auto const& dir_entry : std::filesystem::directory_iterator{path})
            {
                std::string temp{dir_entry.path().string()};
                std::string s2 = temp.substr(temp.size() - 4, 4);
                if(s2 == "pack"){
                    temp = temp.erase(0, path.size() + 1);
                    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamPackname = temp;
                }
            }
            break;
        }
        else
        {
            Sleep(100);
        }
    }

    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamModGameId = id;
    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamAuthor = modDetails.m_ulSteamIDOwner;

}

void QtGeneralBackend::removeMod(uint64_t id){
    steamAPIAccess SteamAPI;
    for(int i = 0; i < SharedGlobalDataObj->Global_ModsDataObj.size(); ++i){
        if(SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId == id)
        {
            SharedGlobalDataObj->Global_ModsDataObj.erase(SharedGlobalDataObj->Global_ModsDataObj.begin() + i);
        }
    }
    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount--;
    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.gamepath +
            "\\steamapps\\workshop\\content\\1142710\\" + std::to_string(id);
    std::filesystem::remove_all(path);
    SteamAPI.unsubscribeMod(id);
}
