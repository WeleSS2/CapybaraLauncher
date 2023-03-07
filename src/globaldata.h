#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QSharedDataPointer>
#include <QQmlApplicationEngine>
#include "QColor.h"

// wh1Id 364360
// wh2Id 594570
// wh3Id 1132710
// wh4KingId 779340
// whTroyId 1099410
// whRomeRemId 885970


struct sGamesData {
    QString gameName;
    QString gamePath;
    QString pathName;
    int gameId = 0;
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

struct LocalSettings {
    LocalSettings(){};
    bool settingsLoaded = false;
    std::string steampath;
    uint64_t defaultGame;
    std::string localPath;

    int numInstalledGames;

    sGamesData currentGame;
    QVector<sGamesData> installedGames;

    uint32_t modsAmount;
};

class GlobalDataData : public QSharedData
{
public:
    LocalSettings Global_LocalSettingsObj;
    std::vector<ModsData> Global_ModsDataObj;
    QQmlApplicationEngine* enginePtr = nullptr;


    sGamesData& getGameById(uint64_t id);
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
