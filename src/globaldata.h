#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QSharedDataPointer>
#include <QQmlApplicationEngine>
#include "QColor.h"

inline int* modpacksAmount = nullptr;

struct LocalSettings {
    LocalSettings(){};
    bool settingsLoaded = false;
    uint32_t modpacksAmount;
    std::string steampath;
    std::string gamepath;
    std::string localPath;
    uint32_t modsAmount;
};

struct ModsData {
    ModsData();
    bool done;
    QColor color;
    int laucherId;
    uint64_t steamModGameId;
    int steamDataInSeconds;
    int steamAuthor;
    std::string steamModName;
    std::string steamPackname;
};

struct GlobalModpacksData {
    GlobalModpacksData();
    std::string modpackName;
    std::vector<uint32_t> modsId;
};

class GlobalDataData : public QSharedData
{
public:
    LocalSettings Global_LocalSettingsObj;
    std::vector<ModsData> Global_ModsDataObj;
    GlobalModpacksData Global_ModpackDataObj;
    QQmlApplicationEngine* enginePtr = nullptr;

};
inline auto SharedGlobalDataObj = std::make_shared<GlobalDataData>();

class GlobalData
{
public:
    GlobalData();
    GlobalData(const GlobalData &);
    GlobalData &operator=(const GlobalData &);
    ~GlobalData();
    void simpleFunction();

private:
    QSharedDataPointer<GlobalDataData> data;
};

#endif // GLOBALDATA_H
