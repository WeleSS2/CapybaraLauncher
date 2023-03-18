#include "gamechanger.h"
#include <filesystem>
#include <fstream>
#include <Windows.h>

#include "../../utility/loggingsystem.h"
#include "../../localfiles/localmods.h"
#include "modslistfile.h"

//#include "../../steamtools.h"

GameChanger::GameChanger(QObject* parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int GameChanger::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return GlobalDataObj->LocalSettingsObj.installedGames.size();
}

QVariant GameChanger::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
    {
        return QVariant();
    };

    const sGamesData item = mList->vsGamesData().at(index.row());
    switch(role)
    {
        case NameRole:
        {
            return QVariant(item.gameName);
        }
    }

    return QVariant();
}

bool GameChanger::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    sGamesData item = mList->vsGamesData().at(index.row());
    switch(role)
    {
        case NameRole:
        {
            item.gameName = value.toString();
            break;
        }
    }
    if(mList->setItemAt(index.row(), item)){
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags GameChanger::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

cGameChangerList *GameChanger::list() const
{
    return mList;
}

QHash<int, QByteArray> GameChanger::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "gameName";
    return names;
}

void GameChanger::setList(cGameChangerList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &cGameChangerList::preItemAppened, this, [=](){
            const int index = mList->vsGamesData().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &cGameChangerList::postItemAppened, this, [=](){
            endInsertRows();
        });
        connect(mList, &cGameChangerList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &cGameChangerList::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}

void GameChanger::setCurrentGame(uint64_t index) const {
    // Set game and clear data form previous
    GlobalDataObj->LocalSettingsObj.currentGame = GlobalDataObj->LocalSettingsObj.installedGames[index];
    GlobalDataObj->ModsDataObj.clear();

    if(std::filesystem::exists("steam_appid.txt"))
    {
        //std::filesystem::remove("steam_appid.txt");

        std::fstream file;
        file.open("steam_appid.txt", std::ios::out);
        if(file.is_open())
        {
            file << std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId);
            //file << "281990";
        }
        else
        {
            LoggingSystem::saveLog("gamechanger.cpp: setCurrentGame: Error while creating new steamapp.");
        }
    }
    else
    {
        LoggingSystem::saveLog("gamechanger.cpp: setCurrentGame: Error while removing steamapp.");
    }

    // Guard did file is saved already
    if(!std::filesystem::exists("steam_appid.txt"))
    {
        bool status = false;
        while(!status)
        {
            status = std::filesystem::exists("steam_appid.txt");

        }
    }


    // SteamAPI Initialization
    SteamApiAccess objSteamApiAccess;
    objSteamApiAccess.closeGameSteamAPI();

    if(objSteamApiAccess.runGameSteamAPI())
    {
        objSteamApiAccess.loadModsDataSteam();
        objSteamApiAccess.getModsData();
        objSteamApiAccess.setModsPackname();
    }

    // Local mods segment
    LocalMods objLocalMods;
    if(objLocalMods.gameFolderCheck())
    {
        if(!objLocalMods.loadLocalMods())
        {
            LoggingSystem::saveLog("main.cpp: Failed to load local mods folder");
        }
    }
    else
    {
        LoggingSystem::saveLog("main.cpp: Failed to open local mods folder");
    }
}

int GameChanger::getCurrentGameId() const {
    return GlobalDataObj->LocalSettingsObj.currentGame.gameId;
}




// ------------------------------- cGameChangerList ----------------------------------

cGameChangerList::cGameChangerList(QObject *parent)
    : QObject(parent)
{
}

QVector<sGamesData> cGameChangerList::vsGamesData() const
{
    return GlobalDataObj->LocalSettingsObj.installedGames;
}

bool cGameChangerList::setItemAt(int index, const sGamesData &item)
{
    if(index < 0 || index >= GlobalDataObj->LocalSettingsObj.installedGames.size())
        return false;

    const sGamesData &oldItemData = GlobalDataObj->LocalSettingsObj.installedGames.at(index);
    if(item.gameId == oldItemData.gameId)
        return false;

    GlobalDataObj->LocalSettingsObj.installedGames[index] = item;
    return true;
}

bool cGameChangerList::appendItem(QString name)
{
    emit preItemAppened();

    sGamesData item;

    GlobalDataObj->LocalSettingsObj.installedGames.append(item);
    emit postItemAppened();
    return true;
}

void cGameChangerList::removeItem(qint32 index)
{
    for(auto& i: GlobalDataObj->LocalSettingsObj.installedGames){
        emit preItemRemoved(index);

        GlobalDataObj->LocalSettingsObj.installedGames.removeAt(index);

        emit postItemRemoved();
        break;
    }
}

uint64_t cGameChangerList::getGameId(uint64_t index)
{
    return GlobalDataObj->LocalSettingsObj.installedGames[index].gameId;
}
