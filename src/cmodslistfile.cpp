#include "cmodslistfile.h"
#include "qqml.h"
#include "steam_api.h"
#include "globaldata.h"

CModsListFile::CModsListFile(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int CModsListFile::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return SharedGlobalDataObj->Global_ModsDataObj.size();
}

QVariant CModsListFile::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ItemsData item = mList->Vs_ItemsData().at(index.row());
    switch (role)
    {
    case ColorRole:
    { return QVariant(item.color); }
    case IdRole:
    { return QVariant(item.id); }
    case DoneRole:
    { return QVariant(item.done); }
    case NameRole:
    { return QVariant(item.name); }
    case DateRole:
    { return QVariant(item.date); }
    case PacknameRole:
    { return QVariant(item.packname); }
    case GameModIdRole:
    { return QVariant(item.modgameid); }
    case AuthorRole:
    { return QVariant(item.author); }
    }
    return QVariant();
}

bool CModsListFile::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    ItemsData item = mList->Vs_ItemsData().at(index.row());
    switch (role)
    {
    case ColorRole:
    { }
    case IdRole:
    { }
    case DoneRole:
    {
        item.done = value.toBool();
        if(item.done)
        {
            SharedGlobalDataObj->Global_ModsDataObj[index.row()].done = true;
        }
        else
            SharedGlobalDataObj->Global_ModsDataObj[index.row()].done = false;

        break;
    }
    case NameRole:
    { item.name = value.toString(); break;}
    case DateRole:
    { }
    case PacknameRole:
    { }
    case GameModIdRole:
    { }
    case AuthorRole:
    { }
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags CModsListFile::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> CModsListFile::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ColorRole] = "colorWarn";
    names[IdRole] = "id";
    names[DoneRole] = "done";
    names[NameRole] = "name";
    names[AuthorRole] = "author";
    names[DateRole] = "date";
    names[PacknameRole] = "packname";
    names[GameModIdRole] = "modgameid";
    return names;
}

cmodslistfilling *CModsListFile::list() const
{
    return mList;
}

void CModsListFile::setList(cmodslistfilling *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &cmodslistfilling::preItemAppened, this, [=](){
            const int index = mList->Vs_ItemsData().size();
            beginInsertRows(QModelIndex(), index, index);
        } );
        connect(mList, &cmodslistfilling::postItemAppened, this, [=](){
            endInsertRows();
        } );
        connect(mList, &cmodslistfilling::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        } );
        connect(mList, &cmodslistfilling::postItemRemoved, this, [=](){
            endRemoveRows();
        } );
    }
    mListGlobalPtr = mList;
    endResetModel();
}

void CModsListFile::refreshList()
{    
    qDebug() << "refresh1";
    QQuickItem* listView = mList->getListPointer();
    QModelIndex currentIndex = listView->property("currentIndex").value<QModelIndex>();

    qDebug() << "refresh2";
    beginResetModel();
    for(auto& i: SharedGlobalDataObj->Global_ModsDataObj)
    {
        if(i.done){
            mList->mItemsData[i.laucherId].done = true;
        }
    }
    endResetModel();

    listView->setProperty("currentIndex", QVariant::fromValue(currentIndex));
    listView->setProperty("positionViewAtIndex", QVariant::fromValue(currentIndex.row()));
    qDebug() << "refresh3";
}
