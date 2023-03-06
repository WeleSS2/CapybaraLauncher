#include "localfiles.h"
#include "globaldata.h"
#include <fstream>
#include <filesystem>
#include <algorithm>


// Depraceted due to using now .js files to save/load data

// * Due to problems with .js on again... And primitively updated


bool localFiles::findLocalFolder()
{
    bool success = false;
    char *pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
    if (err) return -1;
    else
    {
        std::string path = std::string(pValue) + "\\CapybaraLaunchers";
        std::string pathWh3 = path + "\\WH3";
        std::string modpacksPath = pathWh3 + "\\Modpacks";
        if(std::filesystem::is_directory(path))
        {
            if(std::filesystem::is_directory(pathWh3))
            {
                localWh3Path = pathWh3;
                SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
                success = true;
            }
            else
            {
                std::filesystem::create_directory(pathWh3);
                localWh3Path = pathWh3;
                SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
                success = true;
            }
        }
        else
        {
            std::cout << "Local settings directory not found" << std::endl;
            std::filesystem::create_directories(pathWh3);
            localWh3Path = pathWh3;
            SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
            success = true;
        }
        if(std::filesystem::is_directory(modpacksPath))
        {
            success = true;
        }
        else
        {
            std::filesystem::create_directory(modpacksPath);
        }

        return success;
    }
    return false;
}

bool localFiles::findLocalDataTxt(std::string &path)
{
    if(std::filesystem::is_regular_file(path) && !std::filesystem::is_empty(path))
    {
        return true;
    }
    return false;
}

void localFiles::saveLocalSettings()
{
    std::cout << "In 1" << std::endl;
    if(findLocalFolder())
    {
        std::string settingsPath = localWh3Path + "\\settings.txt";
        std::fstream file;
        file.open(settingsPath, std::ios::out);

        file << "\"state\" " << "1" << "\n";
        file << "\"steampath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.steampath << "\n";
        file << "\"defaultGame\" " << SharedGlobalDataObj->Global_LocalSettingsObj.defaultGame << "\n";
        file << "\"gamepath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.gamepath << "\n";
        file << "\"wh1Path\" " << SharedGlobalDataObj->Global_LocalSettingsObj.wh1Path <<  "\n";
        file << "\"wh2Path\" " << SharedGlobalDataObj->Global_LocalSettingsObj.wh2Path << "\n";
        file << "\"wh3KingPath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.wh3KingPath << "\n";
        file << "\"whTroyPath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.whTroyPath << "\n";
        file << "\"whRomeRemPath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.whRomeRemPath << "\n";
        file.close();
    }
}

void localFiles::saveLocalModlist()
{

}

void localFiles::loadLocalSettings()
{
    if(findLocalFolder())
    {
        std::string settingsPath = localWh3Path + "\\settings.txt";
        std::string text;
        std::fstream file;
        file.open(settingsPath);

        if(file.is_open())
        {
            while(file>>text)
            {
                if(text == "\"state\"")
                {
                    file >> SharedGlobalDataObj->Global_LocalSettingsObj.settingsLoaded;
                }
                else if(text == "\"steampath\"")
                {
                    std::string show;
                    getline(file, show);
                    show.erase(0, 1);
                    SharedGlobalDataObj->Global_LocalSettingsObj.steampath = show;
                }
                else if (text == "\"defaultGame\"")
                {
                    std::string show;
                    getline(file, show);
                    SharedGlobalDataObj->Global_LocalSettingsObj.defaultGame = std::stoi(show);
                }
                else if(text == "\"gamepath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.gamepath, show);
                }
                else if(text == "\"wh1Path\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.wh1Path, show);
                }
                else if(text == "\"wh2Path\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.wh2Path, show);
                }
                else if (text == "\"wh3KingPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.wh3KingPath, show);
                }
                else if(text == "\"whTroyPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.whTroyPath, show);
                }
                else if(text == "\"whRomeRemPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(SharedGlobalDataObj->Global_LocalSettingsObj.whRomeRemPath, show);
                }
            }
        }
        file.close();
    }
}

bool localFiles::saveTo(std::string& target, std::string& value)
{
    if(value.length() > 2)
    {
        value.erase(0, 1);
        target = value;
        SharedGlobalDataObj->Global_LocalSettingsObj.numInstalledGames++;
        return true;
    }
    else
    {
        target = "";
        return false;
    }
}

//bool localFiles::loadSetting(const std::fstream file, const std::string& target, std::string value)
//{
//    std::string valueLocal;
//    getline(file, valueLocal);
//    valueLocal.erase(0, 1);
//
//}

void localFiles::loadLocalModlist()
{

}

