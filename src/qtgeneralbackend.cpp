#include "qDebug.h"
#include "qguiapplication.h"
#include <Windows.h>
#include <cstdlib>
#include <filesystem>
#include <fstream>

#include <QClipboard>
#include <QDesktopServices>
#include <QFile>
#include <QThread>

#include "qqmlcontext.h"
#include "qtgeneralbackend.h"
#include "steamapi/steamapiaccess.h"
#include "globaldata.h"
#include "github/githubupdater.h"
#include "qt/customModules/infobox.h"
#include "utility/utility.h"
#include "localfiles/localmods.h"
#include "utility/loggingsystem.h"

QtGeneralBackend::QtGeneralBackend(QObject *parent, TaskListList *taskList)
    : QObject{parent}
    , taskListPtr{taskList}
{

}

void QtGeneralBackend::startGame()
{
    std::string run = "";

    run += "start \"\" \"" + GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
            + "\\steamapps\\common\\"
            + [&](){
        std::string gamePath;
        std::string path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString() + "\\steamapps\\appmanifest_" + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId) + ".acf";
        if(std::filesystem::exists(path))
        {
            std::fstream file(path);
            std::string line;
            while(file>>line){
                if(line == "\"installdir\""){
                    std::getline(file, gamePath);
                    gamePath.erase(0, 3);
                    gamePath.erase(gamePath.size() - 1, 1);
                }
            }
        }
        switch(GlobalDataObj->LocalSettingsObj.currentGame.gameId){
        case 364360: {
            gamePath += "\\Warhammer.exe";
            break;
        };
        case 594570: {
            gamePath += "\\Warhammer2.exe";
            break;
        };
        case 1142710: {
            gamePath += "\\Warhammer3.exe";
            break;
        };
        case 779340: {
            gamePath += "\\Three_Kingdoms.exe";
            break;
        };
        case 1099410: {
            gamePath += "\\Troy.exe";
            break;
        };
        case 885970: {
            gamePath += "\\Rome.exe";
            break;
        };
        case 214950: {
            gamePath += "\\Rome2.exe";
            break;
        };
        case 4700: {
            gamePath += "\\medieval2.exe";
            break;
        };
        case 34330: {
            gamePath += "\\Shogun2.exe";
            break;
        };
        case 325610: {
            gamePath += "\\Atilla.exe";
            break;
        };
        }

        return gamePath;
    }()
    + "\"";

    QVector<sModsData> localModsList = GlobalDataObj->ModsDataObj;

    if(!GlobalDataObj->LocalSettingsObj.unsafeMode){
        std::sort(localModsList.begin(),
                  localModsList.end(),
                  [](const sModsData& first, const sModsData& second) -> bool
        {
            return first.steamPackname < second.steamPackname;
        });
    }

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
              addTask(mods[i].first, "addMod");
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
    Utility objUtility;
    objUtility.showSimpleInfoBox("Downloading mod with id: " + QString::fromStdString(std::to_string(id)));
    SteamApiAccess SteamAPI;
    SteamAPI.subscribeMod(id);
    if(SteamAPI.updateMod(id))
    {
        // Insert item into launcher
        sModsData data = SteamAPI.getModData(id);
        data.done = true;
        data.laucherId = GlobalDataObj->ModsDataObj.size();
        SteamAPI.setModPackname(data);
        GlobalDataObj->ModsDataObj.emplaceBack(data);
    }
    else{
        SteamAPI.unsubscribeMod(id);
        LoggingSystem::saveLog("qtgeneralbackend.cpp: addMod: Failed to download mod from steam");
    }
}

void QtGeneralBackend::addTask(uint64_t modId, QString taskName){
    std::string str = std::to_string(modId);
    QString StringModId = QString::fromStdString(str);
    if(taskName == "addMod"){
        taskListPtr->appendAndRunTask([=](){
            SteamApiAccess SteamAPI;
            SteamAPI.subscribeMod(modId);
            if(SteamAPI.updateMod(modId))
            {
                // Insert item into launcher
                sModsData data = SteamAPI.getModData(modId);
                data.done = true;
                data.laucherId = GlobalDataObj->ModsDataObj.size();
                SteamAPI.setModPackname(data);
                GlobalDataObj->ModsDataObj.emplaceBack(data);
            }
            else{
                SteamAPI.unsubscribeMod(modId);
                LoggingSystem::saveLog("qtgeneralbackend.cpp: addMod: Failed to download mod from steam");
            }
        }, ("addMod" + StringModId) , ("Downloading mod with id " + StringModId));
    }
    else if(taskName == "updateMod")
    {
        taskListPtr->appendAndRunTask([=](){
            SteamApiAccess steamApi;
            steamApi.updateMod(modId);
        }, ("updateMod" + StringModId) , ("Updating mod with id " + StringModId));
    }
    else if(taskName == "testTask")
    {
        auto task = [this](){
            for(int i = 0; i < 200; ++i){
                QThread::msleep(100);
                qDebug() << "From test task";
            };
        };
        taskListPtr->appendAndRunTask(task, "testTask", "Just a test task");
    }
}

void QtGeneralBackend::removeMod(uint64_t id){
    for(int i = 0; i < GlobalDataObj->ModsDataObj.size(); ++i){
        if(GlobalDataObj->ModsDataObj[i].steamModGameId == id)
        {
            GlobalDataObj->ModsDataObj.erase(GlobalDataObj->ModsDataObj.begin() + i);
        }
    }
    SteamApiAccess steamApi;

    if(steamApi.unsubscribeMod(id)){
        std::string path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
                + "\\steamapps\\workshop\\content\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + std::to_string(id);
        if(std::filesystem::exists(path)){
            qDebug() << "Path exist?";
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

void QtGeneralBackend::removeLocalCopy(uint64_t id){
    std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\LocalMods\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            + "\\"
            + GlobalDataObj->getModById(id)->steamPackname.toStdString();
    if(std::filesystem::exists(path)){
        std::filesystem::remove(path);
        GlobalDataObj->ModsDataObj.erase(GlobalDataObj->ModsDataObj.begin() + id);
    }
    else
        LoggingSystem::saveLog("qtgeneralbackend.cpp: removeLocalCopy: Failed to remove local copy");
}

void QtGeneralBackend::openInRPFM(uint64_t id){
    std::string path = "";
    if(GlobalDataObj->getModById(id)->steamModGameId == 0){
        path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
                + "\\LocalMods\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + GlobalDataObj->getModById(id)->steamPackname.toStdString();
    }
    else
    {
        path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
                + "\\steamapps\\workshop\\content\\"
                + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
                + "\\"
                + std::to_string(GlobalDataObj->getModById(id)->steamModGameId)
                + "\\"
                + GlobalDataObj->getModById(id)->steamPackname.toStdString();
    }

    if(std::filesystem::exists(path)){
        QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(path)));
    }
}

void QtGeneralBackend::closeSteamAPIIfOn(){
    SteamApiAccess steamApi;
    steamApi.closeGameSteamAPI();
}

void QtGeneralBackend::closeApp(){
    exit(EXIT_FAILURE);
}

void QtGeneralBackend::saveDefaultGame(){
    GlobalDataObj->LocalSettingsObj.defaultGame = GlobalDataObj->LocalSettingsObj.currentGame.gameId;
}

int QtGeneralBackend::getCurrentGameId() const {
    return GlobalDataObj->LocalSettingsObj.currentGame.gameId;
}

void QtGeneralBackend::setCurrentGameId(int id){
    if(GlobalDataObj->LocalSettingsObj.currentGame.gameId != m_currentGameId){
        m_currentGameId = GlobalDataObj->LocalSettingsObj.currentGame.gameId;
        emit currentGameIdChanged(m_currentGameId);
    }
}
