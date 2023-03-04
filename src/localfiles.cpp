#include "localfiles.h"
#include "globaldata.h"
#include <fstream>
#include <filesystem>
#include <algorithm>


// Depraceted due to using now .js files to save/load data


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
        file << "\"gamepath\" " << SharedGlobalDataObj->Global_LocalSettingsObj.gamepath << "\n";
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
                else if(text == "\"gamepath\"")
                {
                    std::string show;
                    getline(file, show);
                    show.erase(0, 1);
                    SharedGlobalDataObj->Global_LocalSettingsObj.gamepath = show;
                }
            }
        }
        file.close();
    }
}

void localFiles::loadLocalModlist()
{

}

