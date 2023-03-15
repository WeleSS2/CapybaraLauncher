#include "modslistfile.h"
#include "qqml.h"
#include "../../globaldata.h"

Mods::Mods(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int Mods::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    // FIXME: Implement me!
    return GlobalDataObj->ModsDataObj.size();
}

QVariant Mods::data(const QModelIndex &index, int role) const
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

bool Mods::setData(const QModelIndex &index, const QVariant &value, int role)
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
            GlobalDataObj->ModsDataObj[index.row()].done = true;
        }
        else
            GlobalDataObj->ModsDataObj[index.row()].done = false;

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

Qt::ItemFlags Mods::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> Mods::roleNames() const
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

ModsList *Mods::list() const
{
    return mList;
}

void Mods::setList(ModsList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &ModsList::preItemAppened, this, [=](){
            const int index = mList->Vs_ItemsData().size();
            beginInsertRows(QModelIndex(), index, index);
        } );
        connect(mList, &ModsList::postItemAppened, this, [=](){
            endInsertRows();
        } );
        connect(mList, &ModsList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        } );
        connect(mList, &ModsList::postItemRemoved, this, [=](){
            endRemoveRows();
        } );
    }
    mListGlobalPtr = mList;
    endResetModel();
}

void Mods::refreshList()
{    
    QQuickItem* listView = mList->getListPointer();
    QModelIndex currentIndex = listView->property("currentIndex").value<QModelIndex>();

    beginResetModel();
    for(auto& i: GlobalDataObj->ModsDataObj)
    {
        if(i.done){
            mList->mItemsData[i.laucherId].done = true;
        }
    }
    endResetModel();
    listView->setProperty("currentIndex", QVariant::fromValue(currentIndex));
    listView->setProperty("positionViewAtIndex", QVariant::fromValue(currentIndex.row()));
}


/* ----------------------------------------------------------------------------
 *
 *
 * MODLIST MODULE
 *
 *
 * ----------------------------------------------------------------------------
 */

ModsList::ModsList(QObject *parent)
    : QObject{parent}
{
    std::sort(GlobalDataObj->ModsDataObj.begin(), GlobalDataObj->ModsDataObj.end(), [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });
    for(int i = 0; i < GlobalDataObj->ModsDataObj.size(); ++i)
    {
        pushItem(i);
    }
}

QVector<ItemsData> ModsList::Vs_ItemsData() const
{
    return mItemsData;
}

bool ModsList::setItemAt(int index, const ItemsData &item)
{
    if(index < 0 || index >= mItemsData.size())
        return false;

    const ItemsData &oldItemData = mItemsData.at(index);
    if(item.done == oldItemData.done && item.name == oldItemData.name)
        return false;

    mItemsData[index] = item;
    return true;
}

void ModsList::appendItem()
{
    emit preItemAppened();

    ItemsData item;
    item.done = false;
    mItemsData.append(item);

    emit postItemAppened();
}

void ModsList::removeItem(int position)
{
    for(int i = 0; i < mItemsData.size(); ++i)
    {
        emit preItemRemoved(position);

        mItemsData.removeAt(position);

        emit postItemRemoved();
    }
}

void ModsList::sortByActive()
{
    std::sort(GlobalDataObj->ModsDataObj.begin(), GlobalDataObj->ModsDataObj.end(), [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.done > second.done;
    });

    refreshModlistVector();
}

void ModsList::sortByDate()
{
    std::sort(GlobalDataObj->ModsDataObj.begin(), GlobalDataObj->ModsDataObj.end(), [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.steamDataInSeconds > second.steamDataInSeconds;
    });

    refreshModlistVector();
}

void ModsList::sortByName()
{
    std::sort(GlobalDataObj->ModsDataObj.begin(), GlobalDataObj->ModsDataObj.end(), [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.steamModName < second.steamModName;
    });

    refreshModlistVector();
}

void ModsList::sortByPackname()
{
    std::sort(GlobalDataObj->ModsDataObj.begin(), GlobalDataObj->ModsDataObj.end(), [](const sModsData& first, const sModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });

    refreshModlistVector();
}

void ModsList::refreshModlistVector(){
    mItemsData.clear();
    for(int i = 0; i < GlobalDataObj->ModsDataObj.size(); ++i)
    {
        pushItem(i);
    }
}

void ModsList::setListViewPointer(QQuickItem* list)
{
    mListView = list;
}

QQuickItem* ModsList::getListPointer(){
    return mListView;
}

void ModsList::pushItem(uint16_t id){
    using namespace std;
    using namespace std::chrono;
    duration<long> dur(GlobalDataObj->ModsDataObj[id].steamDataInSeconds);
    GlobalDataObj->ModsDataObj[id].laucherId = id;
    string steamData = format("{:%Y.%m.%d}", sys_seconds{ dur });

    // Temporary object of mod to inject
    ItemsData modData;
    modData.done = GlobalDataObj->ModsDataObj[id].done;
    modData.color = GlobalDataObj->ModsDataObj[id].color;
    modData.id = QString::fromUtf8(to_string(id).c_str());
    modData.name = GlobalDataObj->ModsDataObj[id].steamModName;
    modData.date = QString::fromUtf8(steamData.c_str());
    modData.packname = GlobalDataObj->ModsDataObj[id].steamPackname;
    modData.modgameid = GlobalDataObj->ModsDataObj[id].steamModGameId;
    modData.author = QString::fromUtf8(to_string(GlobalDataObj->ModsDataObj[id].steamAuthor).c_str());


    mItemsData.append(modData);
}
