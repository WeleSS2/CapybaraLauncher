#include "modpackslist.h"

ModpacksList::ModpacksList(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ModpacksList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return mList->getModpacksNumber();
}

QVariant ModpacksList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();
    const ModpacksData item = mList->Vs_ModpacksData().at(index.row());
    switch(role)
    {
        case NameRole:
        {
            return QVariant(item.modpackName);
        }
    }

    // FIXME: Implement me!
    return QVariant();
}

bool ModpacksList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    ModpacksData item = mList->Vs_ModpacksData().at(index.row());
    switch (role)
    {
    case NameRole:
        {
            item.modpackName = value.toString();
            break;
        }
    }
    if (mList->setItemAt(index.row(), item)) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ModpacksList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> ModpacksList::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "modpackName";
    return names;
}

ModpacksContent *ModpacksList::list() const
{
    return mList;
}

void ModpacksList::setList(ModpacksContent *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &ModpacksContent::preItemAppened, this, [=](){
            const int index = mList->Vs_ModpacksData().size();
            beginInsertRows(QModelIndex(), index, index);
        } );
        connect(mList, &ModpacksContent::postItemAppened, this, [=](){
            endInsertRows();
        } );
        connect(mList, &ModpacksContent::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        } );
        connect(mList, &ModpacksContent::postItemRemoved, this, [=](){
            endRemoveRows();
        } );
    }

    endResetModel();
}

void ModpacksList::refreshList()
{
    beginResetModel();

    endResetModel();
}
