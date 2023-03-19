#include "localfiles.h"
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "../globaldata.h"
#include "../utility/loggingsystem.h"
//#include "localfiles/localmods.h"


// Depraceted due to using now .js files to save/load data

// * Due to problems with .js on again... And primitively updated


bool localFiles::findLocalFolder()
{
    bool success = false;
    char *pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, "APPDATA");
    if (err)
    {
        LoggingSystem::saveLog("localfiles: findLocalFolder: Error can't get APPDATA");
        return success;
    }
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
                GlobalDataObj->LocalSettingsObj.localPath = QString::fromStdString(pathWh3);
                success = true;
            }
            else
            {
                std::filesystem::create_directory(pathWh3);
                localWh3Path = pathWh3;
                GlobalDataObj->LocalSettingsObj.localPath = QString::fromStdString(pathWh3);
                success = true;
            }
        }
        else
        {
            std::filesystem::create_directories(pathWh3);
            localWh3Path = pathWh3;
            GlobalDataObj->LocalSettingsObj.localPath = QString::fromStdString(pathWh3);
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
    // Add guard to check did vector size of games detected and loaded isnt 0!!!
    if(findLocalFolder())
    {
        std::string settingsPath = localWh3Path + "\\settings.txt";
        std::fstream file;
        file.open(settingsPath, std::ios::out);

        file << "\"state\" " << "1" << "\n";
        file << "\"steampath\" " << GlobalDataObj->LocalSettingsObj.steampath.toStdString() << "\n";
        file << "\"defaultGame\" " << GlobalDataObj->LocalSettingsObj.defaultGame << "\n";
        if(GlobalDataObj->getGameById(1142710) != nullptr){
            file << "\"gamepath\" " << GlobalDataObj->getGameById(1142710)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(364360) != nullptr){
            file << "\"wh1Path\" " << GlobalDataObj->getGameById(364360)->gamePath.toStdString() <<  "\n";
        }
        if(GlobalDataObj->getGameById(594570) != nullptr){
            file << "\"wh2Path\" " << GlobalDataObj->getGameById(594570)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(779340) != nullptr){
            file << "\"wh3KingPath\" " << GlobalDataObj->getGameById(779340)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(1099410) != nullptr){
            file << "\"whTroyPath\" " << GlobalDataObj->getGameById(1099410)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(885970) != nullptr){
            file << "\"whRomeRemPath\" " << GlobalDataObj->getGameById(885970)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(214950) != nullptr){
            file << "\"whRomeIIEmpPath\" " << GlobalDataObj->getGameById(214950)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(4700) != nullptr){
            file << "\"whMedIIDefPath\" " << GlobalDataObj->getGameById(4700)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(34330) != nullptr){
            file << "\"whShogunIIPath\" " << GlobalDataObj->getGameById(34330)->gamePath.toStdString() << "\n";
        }
        if(GlobalDataObj->getGameById(325610) != nullptr){
            file << "\"whAtillaPath\" " << GlobalDataObj->getGameById(325610)->gamePath.toStdString() << "\n";
        }
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
                    file >> GlobalDataObj->LocalSettingsObj.settingsLoaded;
                }
                else if(text == "\"steampath\"")
                {
                    std::string show;
                    getline(file, show);
                    show.erase(0, 1);
                    GlobalDataObj->LocalSettingsObj.steampath = QString::fromStdString(show);
                }
                else if (text == "\"defaultGame\"")
                {
                    std::string show;
                    getline(file, show);
                    if(show.length() > 2){
                        GlobalDataObj->LocalSettingsObj.defaultGame = std::stoi(show);
                        GlobalDataObj->LocalSettingsObj.currentGame = *GlobalDataObj->getGameById(std::stoi(show));
                    }
                }
                else if(text == "\"gamepath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(1142710)->gamePath, show);
                }
                else if(text == "\"wh1Path\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(364360)->gamePath, show);
                }
                else if(text == "\"wh2Path\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(594570)->gamePath, show);
                }
                else if (text == "\"wh3KingPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(779340)->gamePath, show);
                }
                else if(text == "\"whTroyPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(1099410)->gamePath, show);
                }
                else if(text == "\"whRomeRemPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(885970)->gamePath, show);
                }
                else if(text == "\"whRomeIIEmpPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(214950)->gamePath, show);
                }
                else if(text == "\"whMedIIDefPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(4700)->gamePath, show);
                }
                else if(text == "\"whShogunIIPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(34330)->gamePath, show);
                }
                else if(text == "\"whAtillaPath\"")
                {
                    std::string show;
                    getline(file, show);
                    saveTo(&GlobalDataObj->getGameById(325610)->gamePath, show);
                }
            }
        }

        file.close();
    }
}

bool localFiles::saveTo(QString* target, std::string& value)
{
    if(value.length() > 2)
    {
        value.erase(0, 1);
        *target = QString::fromStdString(value);
        GlobalDataObj->LocalSettingsObj.numInstalledGames++;
        return true;
    }
    else
    {
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

