#include "gamechanger.h"


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
