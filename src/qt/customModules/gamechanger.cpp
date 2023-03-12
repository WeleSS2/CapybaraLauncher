#include "gamechanger.h"
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include "../../utility/loggingsystem.h"
#include "../../steamtools.h"
#include "../../localfiles/localmods.h"

GameChanger::GameChanger(QObject* parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int GameChanger::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return SharedGlobalDataObj->Global_LocalSettingsObj.installedGames.size();
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

void GameChanger::setCurrentGame(uint64_t index){
    if(SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gameId != 0)
    {
        SteamAPI_Shutdown();
        SteamAPI_ReleaseCurrentThreadMemory();
        HSteamPipe steamPipe = SteamAPI_GetHSteamPipe();
        ISteamClient* steamClient = SteamClient();
        if (steamClient != nullptr)
        {
            steamClient->BReleaseSteamPipe(steamPipe);
        }
    }


    // Set game and clear data form previous
    SharedGlobalDataObj->Global_LocalSettingsObj.currentGame = SharedGlobalDataObj->Global_LocalSettingsObj.installedGames[index];
    SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount = 0;
    SharedGlobalDataObj->Global_ModsDataObj.clear();

    if(std::filesystem::exists("steam_appid.txt"))
    {
        //std::filesystem::remove("steam_appid.txt");

        std::fstream file;
        file.open("steam_appid.txt", std::ios::out);
        if(file.is_open())
        {
            file << std::to_string(SharedGlobalDataObj->Global_LocalSettingsObj.currentGame.gameId);
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

    // Load data for selected game
    if(SteamAPI_Init())
    {
        CSteamTools steamOperations;
        SharedSteamToolsObj->LoadItemsToQuery();
        SharedSteamToolsObj->LoadItemsDataFromQuery();
    }


    // IN work
    SteamAPIAccess objSteam;
    objSteam.closeGameSteamAPI();
    if(objSteam.runGameSteamAPI())
    {
        // Read data from the shared memory
        QString data;
        if (!objSteam.readDataFromSharedMemory<QString>(data)) {
            int limit = 0;
            while(!objSteam.readDataFromSharedMemory<QString>(data) && limit < 10){
                limit++;
                Sleep(500);
            }
        }
    }
    else
    {
        LoggingSystem::saveLog("gamechanger.cpp: setCurrentGame: Error while loading a mods.");
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





// ------------------------------- cGameChangerList ----------------------------------

cGameChangerList::cGameChangerList(QObject *parent)
    : QObject(parent)
{
}

QVector<sGamesData> cGameChangerList::vsGamesData() const
{
    return SharedGlobalDataObj->Global_LocalSettingsObj.installedGames;
}

bool cGameChangerList::setItemAt(int index, const sGamesData &item)
{
    if(index < 0 || index >= SharedGlobalDataObj->Global_LocalSettingsObj.installedGames.size())
        return false;

    const sGamesData &oldItemData = SharedGlobalDataObj->Global_LocalSettingsObj.installedGames.at(index);
    if(item.gameId == oldItemData.gameId)
        return false;

    SharedGlobalDataObj->Global_LocalSettingsObj.installedGames[index] = item;
    return true;
}

bool cGameChangerList::appendItem(QString name)
{
    emit preItemAppened();

    sGamesData item;

    SharedGlobalDataObj->Global_LocalSettingsObj.installedGames.append(item);
    emit postItemAppened();
    return true;
}

void cGameChangerList::removeItem(qint32 index)
{
    for(auto& i: SharedGlobalDataObj->Global_LocalSettingsObj.installedGames){
        emit preItemRemoved(index);

        SharedGlobalDataObj->Global_LocalSettingsObj.installedGames.removeAt(index);

        emit postItemRemoved();
        break;
    }
}

uint64_t cGameChangerList::getGameId(uint64_t index)
{
    return SharedGlobalDataObj->Global_LocalSettingsObj.installedGames[index].gameId;
}
