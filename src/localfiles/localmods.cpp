#include "localmods.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include "../utility/loggingsystem.h"
#include "../globaldata.h"

LocalMods::LocalMods(QObject* parent)
{

}

bool LocalMods::gameFolderCheck(){
    std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\LocalMods";
    if(std::filesystem::is_directory(path))
    {
        if(std::filesystem::is_directory(path + "\\" + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)))
        {
            return true;
        }
        else
        {
            std::filesystem::create_directory(path + "\\" + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId));
            return true;
        }
    }
    else
    {
        std::filesystem::create_directory(path);
        std::filesystem::create_directory(path + "\\" + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId));
        return true;
    }

    LoggingSystem::saveLog("localmods.cpp: gameFolderCheck: Error while loading local mods");
    return false;
}

bool LocalMods::loadLocalMods(){
    std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\LocalMods"
            + "\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId);

    if(std::filesystem::exists(path))
    {
        for(auto& i: std::filesystem::directory_iterator{path})
        {
            loadSingleMod(i, path);
        }
        return true;
    }
    else
    {
        LoggingSystem::saveLog("LocalMods: loadLocalMods: Folder for selected game do not exist");
        return false;
    }
}

bool LocalMods::loadSingleMod(const std::filesystem::directory_entry& mod, const std::string& path)
{
    std::string name{mod.path().filename().generic_string()};
    std::filesystem::file_time_type updateDate{mod.last_write_time()};
    auto systemTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(updateDate - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
    std::time_t time = std::chrono::system_clock::to_time_t(systemTime);
    std::string timeStr = std::ctime(&time);

    int lastPos = GlobalDataObj->ModsDataObj.size();
    GlobalDataObj->ModsDataObj.emplace_back();

    GlobalDataObj->ModsDataObj[lastPos].laucherId = lastPos;
    GlobalDataObj->ModsDataObj[lastPos].done = false;
    GlobalDataObj->ModsDataObj[lastPos].steamModName = "Local mod";
    GlobalDataObj->ModsDataObj[lastPos].steamDataInSeconds = 0;
    GlobalDataObj->ModsDataObj[lastPos].steamPackname = QString::fromStdString(name);
    GlobalDataObj->ModsDataObj[lastPos].steamModGameId = 0;
    GlobalDataObj->ModsDataObj[lastPos].steamAuthor = 0;
    GlobalDataObj->ModsDataObj[lastPos].color = {174, 135, 205, 255};
    return true;
}
