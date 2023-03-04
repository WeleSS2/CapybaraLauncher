#include "windowsfunctions.h"
#include "globaldata.h"

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
    std::fstream file;
    file.open(path);

    if(file.is_open())
    {
        while(file >> text)
        {
            if(text == "\"path\"")
            {
                getline(file, pathline);
            }
            if(text == "\"1142710\"")
            {
                pathline.erase(0, 3);
                pathline.erase(2, 1);
                pathline.erase(pathline.size() - 1, 1);
                break;
            }
        }
    }
    else
    {
        std::cout << "Error while opening libraryfolder.vdf" << std::endl;
        return false;
    }
    SharedGlobalDataObj->Global_LocalSettingsObj.steampath = steampath;
    SharedGlobalDataObj->Global_LocalSettingsObj.gamepath = pathline;

    return true;
}

bool WindowsFunctions::getGamePathFromSteam()
{
    return true;
}
