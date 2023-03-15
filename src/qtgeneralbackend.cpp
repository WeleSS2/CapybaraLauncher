#include "qDebug.h"
#include "qguiapplication.h"
#include <Windows.h>
#include <cstdlib>
#include <filesystem>

#include <QClipboard>
#include <QDesktopServices>
#include <QFile>

#include "qqmlcontext.h"
#include "qtgeneralbackend.h"
#include "steamapi/steamapiaccess.h"
#include "globaldata.h"
#include "github/githubupdater.h"
//#include "qt/customModules/infobox.h"
#include "utility/utility.h"
#include "localfiles/localmods.h"
#include "utility/loggingsystem.h"

QtGeneralBackend::QtGeneralBackend(QObject *parent)
    : QObject{parent}
{

}

void QtGeneralBackend::startGame()
{
    std::string run = "";

    run += "start \"\" \"" + GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
            + "\\steamapps\\common\\Total War WARHAMMER III\\Warhammer3.exe\"";

    QVector<sModsData> localModsList = GlobalDataObj->ModsDataObj;


    std::sort(localModsList.begin(),
              localModsList.end(),
              [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });


    std::string localModsPath = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\LocalMods"
            + "\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId);

    for(auto& i: localModsList){
        if(i.done){
            if(i.steamModGameId != 0)
            {
                run += "  add_working_directory  \""
                        + GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
                        + "\\steamapps\\workshop\\content\\"
                        + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                        + "\\"
                        + std::to_string(i.steamModGameId)
                        + "\";"
                        + " mod \"" + i.steamPackname.toStdString() + "\";";
            }
            else
            {
                run += "  add_working_directory  \""
                        + localModsPath
                        + "\";"
                        + " mod \"" + i.steamPackname.toStdString() + "\";";
            }
        }
    }

    int result = system(run.c_str());
}

void QtGeneralBackend::exportPack(){
    std::string exportString = "";
    for(auto& i: GlobalDataObj->ModsDataObj){
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
      for(auto& i: GlobalDataObj->ModsDataObj)
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
      for(int i = 0; i < mods.size() ; ++i){
          if(!mods[i].second)
          {
              addMod(mods[i].first);
              for(auto& j: GlobalDataObj->ModsDataObj)
              {
                  if(j.steamModGameId == mods[i].first)
                  j.done = true;
              }
          }
      }
}

void QtGeneralBackend::removeModpack(QString name){
        std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
                + "\\Modpacks\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + name.toStdString()
                + ".txt";
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

void QtGeneralBackend::updateMod(uint64_t id){
//    Utility objUtility;
//    objUtility.showSimpleInfoBox("Downloading mod with id: " + QString::fromStdString(std::to_string(id)));

    SteamApiAccess steamApi;
    steamApi.updateMod(id);
}

void QtGeneralBackend::addMod(uint64_t id){
//    Utility objUtility;
//    objUtility.showSimpleInfoBox("Downloading mod with id: " + QString::fromStdString(std::to_string(id)));
//
//    SteamApiAccess SteamAPI;
//    SteamAPI.subscribeMod(id);
//
//    SteamUGCDetails_t modDetails = SteamAPI.getModDetails(id);
//
//    // Download the item
//    SteamAPICall_t hDownloadItemResult = SteamUGC()->DownloadItem(id, true);
//    SteamAPI_RunCallbacks();
//
//
//    SteamAPI.waitUntilCallNotFinished(&hDownloadItemResult);
//
//    // Insert item into launcher
//    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount++;
//
//
//    SharedGlobalDataObj->Global_ModsDataObj.emplace_back();
//    int modPosition = SharedGlobalDataObj->Global_ModsDataObj.size() - 1;
//
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].laucherId = modPosition;
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].done = false;
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].color = {255, 255, 255};
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamModName = modDetails.m_rgchTitle;
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamDataInSeconds = modDetails.m_rtimeUpdated;
//    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gamePath.toStdString()
//            + "\\steamapps\\workshop\\content\\"
//            + std::to_string(SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gameId)
//            + "\\"
//            + std::to_string(id);
//    int count = 0;
//    while(1){
//        if(count >= 3600)
//        {
//            break;
//        }
//        if(std::filesystem::exists(path)){
//            for (auto const& dir_entry : std::filesystem::directory_iterator{path})
//            {
//                std::string temp{dir_entry.path().string()};
//                std::string s2 = temp.substr(temp.size() - 4, 4);
//                if(s2 == "pack"){
//                    temp = temp.erase(0, path.size() + 1);
//                    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamPackname = temp;
//                }
//            }
//            break;
//        }
//        else
//        {
//            Sleep(100);
//            count++;
//        }
//    }
//
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamModGameId = id;
//    SharedGlobalDataObj->Global_ModsDataObj[modPosition].steamAuthor = modDetails.m_ulSteamIDOwner;
}

void QtGeneralBackend::removeMod(uint64_t id){
    for(int i = 0; i < GlobalDataObj->ModsDataObj.size(); ++i){
        if(GlobalDataObj->ModsDataObj[i].steamModGameId == id)
        {
            GlobalDataObj->ModsDataObj.erase(GlobalDataObj->ModsDataObj.begin() + i);
        }
    }
    GlobalDataObj->LocalSettingsObj.modsAmount--;

    SteamApiAccess steamApi;

    if(steamApi.unsubscribeMod(id)){
        std::string path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
                + "\\steamapps\\workshop\\content\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + std::to_string(id);
        if(std::filesystem::exists(path)){
            std::filesystem::remove_all(path);
        }
    }
}

void QtGeneralBackend::openLocalFiles(uint64_t id){
    if(GlobalDataObj->getModById(id)->steamModGameId != 0){
        std::string path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
                + "\\steamapps\\workshop\\content\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + std::to_string(GlobalDataObj->getModById(id)->steamModGameId);
        if(std::filesystem::exists(path)){
            QUrl folderUrl = QUrl::fromLocalFile(QString::fromStdString(path));
            QDesktopServices::openUrl(folderUrl);
        }
    }
    else
    {
        std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
                + "\\LocalMods"
                + "\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId);
        if(std::filesystem::exists(path)){
            QUrl folderUrl = QUrl::fromLocalFile(QString::fromStdString(path));
            QDesktopServices::openUrl(folderUrl);
        }
    }
}

void QtGeneralBackend::makeLocalCopy(uint64_t id)
{
    std::string pathFrom = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
            + "\\steamapps\\workshop\\content\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            + "\\"
            + std::to_string(id)
            + "\\"
            + GlobalDataObj->getModBySteamId(id)->steamPackname.toStdString();
    std::string pathTo = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\LocalMods\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            + "\\"
            + GlobalDataObj->getModBySteamId(id)->steamPackname.toStdString();
    if(std::filesystem::exists(pathFrom))
    {
        if(!std::filesystem::exists(pathTo))
        {
            QFile::copy(QString::fromStdString(pathFrom),
                        QString::fromStdString(pathTo));


            LocalMods objLocalMods;
            objLocalMods.loadSingleMod(std::filesystem::directory_entry(pathTo), pathTo);
        }
        else
        {
            LoggingSystem::saveLog("qtgeneralbackend.cpp: makeLocalCopy: Failed to copy mod to a local version");
        }
    }
    else
    {
        LoggingSystem::saveLog("qtgeneralbackend.cpp: makeLocalCopy: Failed to copy mod from steam folder");
    }
}

void QtGeneralBackend::closeSteamAPIIfOn(){
    SteamApiAccess steamApi;
    steamApi.closeGameSteamAPI();
}

void QtGeneralBackend::closeApp(){
    exit(EXIT_FAILURE);
}
