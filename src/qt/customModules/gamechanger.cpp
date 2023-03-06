#include "gamechanger.h"


//GameChanger::GameChanger(QObject* parent)
//    : QAbstractListModel(parent)
//    , mList(nullptr)
//{
//}
//
//int GameChanger::rowCount(const QModelIndex &parent) const
//{
//    if(parent.isValid() || !mList)
//        return 0;
//
//    return SharedGlobalDataObj->Global_LocalSettingsObj.numInstalledGames;
//}
//
//QVariant GameChanger::data(const QModelIndex &index, int role) const
//{
//    if(!index.isValid() || !mList)
//    {
//        return QVariant();
//    };
//
//}
//
//bool GameChanger::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    return false;
//}
//
//Qt::ItemFlags GameChanger::flags(const QModelIndex &index) const
//{
//    return Qt::NoItemFlags;
//}
//
//QHash<int, QByteArray> GameChanger::roleNames() const
//{
//    QHash<int, QByteArray> names;
//    names[NameRole] = "modpackName";
//    return names;
//}






// ------------------------------- cGameChangerList ----------------------------------

cGameChangerList::cGameChangerList(QObject *parent)
    : QObject(parent)
{
}

QVector<sGamesData> cGameChangerList::vsGamesData() const
{
    return mGamesData;
}

bool cGameChangerList::setItemAt(int index, const sGamesData &item)
{
    if(index < 0 || index >= mGamesData.size())
        return false;

    const sGamesData &oldItemData = mGamesData.at(index);
    if(item.gameId == oldItemData.gameId)
        return false;

    mGamesData[index] = item;
    return true;
}

bool cGameChangerList::appendItem(QString name)
{
    emit preItemAppened();

    sGamesData item;

    mGamesData.append(item);
    emit postItemAppened();
    return true;
}

void cGameChangerList::removeItem(qint32 index)
{
    for(auto& i: mGamesData){
        emit preItemRemoved(index);

        mGamesData.removeAt(index);

        emit postItemRemoved();
        break;
    }
}

uint64_t cGameChangerList::getGameId(uint64_t index)
{
    return mGamesData[index].gameId;
}
