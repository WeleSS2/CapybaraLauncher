#pragma once

#include <QObject>
#include <QDataStream>
#include <QSharedDataPointer>
#include <QQmlApplicationEngine>
#include <QColor>

// wh1Id 364360
// wh2Id 594570
// wh3Id 1132710
// wh3KingId 779340
// whTroyId 1099410
// whRomeRemId 885970

/* Colors data:
 * White {232, 232, 232, 255} - default
 * Light blue {0, 226, 217, 210} - highlighted
 * Red {255, 55, 55, 255} - mod not available
 * Yellow {225, 225, 0, 255} - Can be updated
 * Orange {255, 87, 51, 255} - Warn about not updated long time/Community feedback about errors
 * Light Purple {174, 135, 205, 255} - Local mod
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


struct sGamesData {
    QString gameName;
    QString gamePath;
    QString pathName;

    uint64_t gameId = 0;
};

struct byteInterfaceModsData{
    bool done;
    QColor color;

    uint64_t laucherId;
    uint64_t steamModGameId;
    uint64_t steamDataInSeconds;
    uint64_t steamAuthor;

    QString steamModName;
    QString steamPackname;

    byteInterfaceModsData& operator=(QDataStream& in)
    {
        in >> done
           >> color
           >> laucherId
           >> steamModGameId
           >> steamDataInSeconds
           >> steamAuthor
           >> steamModName
           >> steamPackname;
        return *this;
    };
};

struct sModsData {
    bool done;
    QColor color;

    uint64_t laucherId;
    uint64_t steamModGameId;
    uint64_t steamDataInSeconds;
    uint64_t steamAuthor;

    QString steamModName;
    QString steamPackname;

    friend QDataStream& operator<<(QDataStream& out, sModsData& data){
        out << data.done
            << data.color
            << data.laucherId
            << data.steamModGameId
            << data.steamDataInSeconds
            << data.steamAuthor
            << data.steamModName
            << data.steamPackname;
        return out;
    }
    friend QDataStream& operator>>(QDataStream& in, sModsData& data) {
        in >> data.done
           >> data.color
           >> data.laucherId
           >> data.steamModGameId
           >> data.steamDataInSeconds
           >> data.steamAuthor
           >> data.steamModName
           >> data.steamPackname;
        return in;
    }
};

struct sLocalSettings {
    sLocalSettings(){};
    bool settingsLoaded = false;

    QString steampath;
    QString localPath;

    uint64_t defaultGame;
    uint64_t numInstalledGames;
    uint32_t modsAmount;

    sGamesData currentGame;
    QVector<sGamesData> installedGames;
};

class GlobalData : public QSharedData
{
public:
    sLocalSettings LocalSettingsObj;
    QVector<sModsData> ModsDataObj;

    QQmlApplicationEngine* enginePtr = nullptr;

    sGamesData* getGameById(uint64_t id);
    sModsData* getModById(uint64_t id);
    sModsData* getModBySteamId(uint64_t id);
};
inline auto GlobalDataObj = std::make_shared<GlobalData>();
