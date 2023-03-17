#include "windowsfunctions.h"
#include "../globaldata.h"
#include "../utility/loggingsystem.h"

std::wstring string_to_wide_string(const std::string& string)
{
    if (string.empty())
    {
        return L"";
    }

    const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), nullptr, 0);
    if (size_needed <= 0)
    {
        throw std::runtime_error("MultiByteToWideChar() failed: " + std::to_string(size_needed));
    }

    std::wstring result(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), &result.at(0), size_needed);
    return result;
}

std::string wide_string_to_string(const std::wstring& wide_string)
{
    if (wide_string.empty())
    {
        return "";
    }

    const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
    if (size_needed <= 0)
    {
        throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
    }

    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
    return result;
}

bool WindowsFunctions::getSteamPathFromRegistry()
{
    const std::wstring& subKey = L"SOFTWARE\\Valve\\Steam";
    const std::wstring& value = L"SteamPath";
    std::wstring data;

    DWORD dataSize{};
    LONG retCode = ::RegGetValue(
      HKEY_LOCAL_MACHINE,
      subKey.c_str(),
      value.c_str(),
      RRF_RT_REG_SZ,
      nullptr,
      nullptr,
      &dataSize
    );
    if (retCode != ERROR_SUCCESS)
    {
        retCode = ::RegGetValue(
          HKEY_CURRENT_USER,
          subKey.c_str(),
          value.c_str(),
          RRF_RT_REG_SZ,
          nullptr,
          nullptr,
          &dataSize
        );
        data.resize(dataSize / sizeof(wchar_t));
        retCode = ::RegGetValue(
          HKEY_CURRENT_USER,
          subKey.c_str(),
          value.c_str(),
          RRF_RT_REG_SZ,
          nullptr,
          &data[0],
          &dataSize
        );
        if (retCode != ERROR_SUCCESS)
        {
            std::cout << "RegGetValue() failed alternative; error code = 1 " << retCode << '\n';
            return false;
        }
    }
    else
    {
        data.resize(dataSize / sizeof(wchar_t));
        retCode = ::RegGetValue(
          HKEY_LOCAL_MACHINE,
          subKey.c_str(),
          value.c_str(),
          RRF_RT_REG_SZ,
          nullptr,
          &data[0],
          &dataSize
        );
        if (retCode != ERROR_SUCCESS)
        {
        std::cout << "RegGetValue() failed; error code = 2 " << retCode << '\n';
            return false;
        }
    }
    std::string path = "";
    std::string steampath = "";
    {
        std::string path1 = wide_string_to_string(data);
        path1.erase(path1.size() - 2, 2);
        for(int i = 0; i < path1.length(); ++i)
        {
            if(path1[i] == '/')
            {
                path1.replace(i, 1, "\\");
            }
        }
        steampath = path1;
        path = path1 + "\\steamapps\\libraryfolders.vdf";

    }
    std::string text = "";
    std::string pathline = "";
    std::string pathWh1 = "";
    std::string pathWh2 = "";
    std::string pathWh3 = "";
    std::string path3King = "";
    std::string pathTroy = "";
    std::string pathRomeRem = "";
    std::fstream file;
    file.open(path);

    if(file.is_open())
    {
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Warhammer I", "", "wh1Path", 364360);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Warhammer II", "", "wh2Path", 594570);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Warhammer III", "", "gamepath", 1142710);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Three Kingdoms", "", "wh3KingPath", 779340);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Troy", "", "whTroyPath", 1099410);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Rome Remastered", "", "whRomeRemPath", 885970);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Rome II Emperor", "", "whRomeIIEmpPath", 214950);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Medieval II Definitive", "", "whMedIIDefPath", 4700);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Shogun II", "", "whShogunIIPath", 34330);
        GlobalDataObj->LocalSettingsObj.installedGames.emplaceBack("Atilla", "", "whAtillaPath", 325610);

        while(file >> text)
        {
            if(text == "\"path\"")
            {
                getline(file, pathline);
                pathline.erase(0, 3);
                pathline.erase(2, 1);
                pathline.erase(pathline.size() - 1, 1);
            }
            if(text == "\"1142710\"")
            {
                GlobalDataObj->getGameById(1142710)->gamePath = QString::fromStdString(pathline);
            }
            else if(text == "\"364360\"")
            {
                GlobalDataObj->getGameById(364360)->gamePath = QString::fromStdString(pathline);
            }
            else if(text == "\"594570\"")
            {
                GlobalDataObj->getGameById(594570)->gamePath = QString::fromStdString(pathline);
            }
            else if(text == "\"779340\"")
            {
                GlobalDataObj->getGameById(779340)->gamePath = QString::fromStdString(pathline);
            }
            else if(text == "\"1099410\"")
            {
                GlobalDataObj->getGameById(1099410)->gamePath = QString::fromStdString(pathline);
            }
            else if(text == "\"885970\"")
            {
                GlobalDataObj->getGameById(885970)->gamePath = QString::fromStdString(pathline);
            }
        }
    }
    else
    {
        std::cout << "Error while opening libraryfolder.vdf" << std::endl;
        return false;
    }

    // Remove if game not found
    for(int i = 0; i < GlobalDataObj->LocalSettingsObj.installedGames.size(); ++i){
        if(GlobalDataObj->LocalSettingsObj.installedGames[i].gamePath == "")
        {
            GlobalDataObj->LocalSettingsObj.installedGames.erase(GlobalDataObj->LocalSettingsObj.installedGames.begin() + i);
            i--;
        }
    }

    if(GlobalDataObj->LocalSettingsObj.installedGames.size() < 1)
    {
        LoggingSystem::saveLog("windowsfunctions.cpp: getSteamPathFromRegistry: Failed to load games / Do not find any games installed");
        return false;
    }

    GlobalDataObj->LocalSettingsObj.steampath = QString::fromStdString(steampath);

    return true;
}

bool WindowsFunctions::getGamePathFromSteam()
{
    return true;
}
