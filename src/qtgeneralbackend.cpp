#include "qtgeneralbackend.h"
#include "iostream"
#include "globaldata.h"
#include "fstream"

QtGeneralBackend::QtGeneralBackend(QObject *parent)
    : QObject{parent}
{

}

void QtGeneralBackend::startGame()
{
    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.gamepath +
            "\\steamapps\\common\\Total War WARHAMMER III";
    //std::cout << SharedGlobalDataObj->Global_LocalSettingsObj.gamepath << std::endl;
    std::fstream file;
    file.open(path + "\\used_mods.txt", std::ios::out);

    std::string modsPath = "add_working_directory \"" + SharedGlobalDataObj->Global_LocalSettingsObj.gamepath
            + "/steamapps/workshop/content/1142710/";
    modsPath.replace(modsPath.begin() + 25, modsPath.begin() + 26, "/");

    //std::cout << modsPath << std::endl;
    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        if(SharedGlobalDataObj->Global_ModsDataObj[i].done)
        {
            file << modsPath + std::to_string(SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId) + "\";" << std::endl;
        }
    }
    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        if(SharedGlobalDataObj->Global_ModsDataObj[i].done)
        {
            file << "mod \"" + SharedGlobalDataObj->Global_ModsDataObj[i].steamPackname + "\";" << std::endl;
        }
    }

        SteamAPI_Shutdown();
        //std::fstream file2;
        //file2.open("steam_appid.txt", std::ios::out);
        //file2 << std::endl;
        //file2.close();
        //SteamAPI_Init();
        SteamAPI_RestartAppIfNecessary(1142710);
    {
        std::cout << "Api disabled" << std::endl;
    }
}
