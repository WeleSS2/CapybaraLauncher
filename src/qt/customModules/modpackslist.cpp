#include "modpackslist.h"

#include <filesystem>
#include <fstream>

#include "modslistfile.h"

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

/* -------------------------------------------------------------------------------
 *
 *                        ModpacksList(Content)
 *
 * -------------------------------------------------------------------------------
 */

ModpacksContent::ModpacksContent(QObject *parent)
    : QObject{parent}
{
}

QVector<ModpacksData> ModpacksContent::Vs_ModpacksData() const
{
    return mModpacksData;
}

bool ModpacksContent::setItemAt(int index, const ModpacksData &item)
{
    if(index < 0 || index >= mModpacksData.size())
        return false;

    const ModpacksData &oldItemData = mModpacksData.at(index);
    if(item.modpackName == oldItemData.modpackName)
        return false;

    mModpacksData[index] = item;
    return true;
}

bool ModpacksContent::appendItem(QString name)
{
    emit preItemAppened();

    ModpacksData item;

    //for(auto& i : mModpacksData)
    //{
    //    if(i.modpackName == name)
    //    {
    //        return false;
    //    }
    //}
    //item.modpackName = name;
    mModpacksData.append(item);

    emit postItemAppened();
    return true;
}

void ModpacksContent::removeItem(qint32 index)
{
    for(int i = 0; i < mModpacksData.size(); ++i)
    {
        emit preItemRemoved(index);

        mModpacksData.removeAt(index);

        emit postItemRemoved();
        break;
    }
}

void ModpacksContent::saveModlist(QString name)
{
    std::string stringName = name.toStdString();
    std::string modFolderPath = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\Modpacks\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            ;
    std::string path = modFolderPath
            + "\\"
            + name.toStdString() + ".txt";

    // Check did folder exist
    if(!std::filesystem::exists(modFolderPath))
    {
        std::filesystem::create_directory(modFolderPath);
    }


    std::fstream file;
    QVector<uint32_t> localModsId;
    QVector<QString> modFileName;

    bool exist = false;
    if(std::filesystem::exists(path))
    {
        exist = true;
        std::filesystem::remove(path);

    }

    file.open(path, std::ios::out);

    for(int i = 0; i < GlobalDataObj->ModsDataObj.size(); ++i)
    {
        if(mListGlobalPtr->mItemsData[i].done)
        {
            if(mListGlobalPtr->mItemsData[i].modgameid != 0)
            {
                localModsId.emplaceBack(mListGlobalPtr->mItemsData[i].modgameid);
                modFileName.emplaceBack("");
                file << "S " << mListGlobalPtr->mItemsData[i].modgameid << std::endl;
            }
            else
            {
                localModsId.emplaceBack(0);
                modFileName.emplaceBack(mListGlobalPtr->mItemsData[i].packname);
                file << "L " << mListGlobalPtr->mItemsData[i].packname.toStdString() << std::endl;
            }
        }
    }
    file.close();
    if(!exist){
        mModpacksData.append({name, localModsId, modFileName});
    }
    else
    {
        for(auto &i: mModpacksData){
            if(i.modpackName == name){
                i.modsId.clear();
                i.modFileName.clear();
                i.modsId = localModsId;
                i.modFileName = modFileName;
            }
        }
    }
}

void ModpacksContent::loadModlist(uint64_t index)
{
    // Set all to false
    for(int k = 0; k < mListGlobalPtr->mItemsData.size(); ++k)
    {
        mListGlobalPtr->mItemsData[k].done = false;
        GlobalDataObj->ModsDataObj[k].done = false;
    }

    // Check if imported if yes enable
    for(int j = 0; j < mModpacksData[index].modsId.size(); ++j)
    {
        for(int k = 0; k < mListGlobalPtr->mItemsData.size(); ++k)
        {
            if(mModpacksData[index].modsId[j] != 0){
                if(mModpacksData[index].modsId[j] == mListGlobalPtr->mItemsData[k].modgameid)
                {
                    mListGlobalPtr->mItemsData[k].done = true;
                    GlobalDataObj->ModsDataObj[k].done = true;
                }
            }
            else
            {
                if(mModpacksData[index].modFileName[j] == mListGlobalPtr->mItemsData[k].packname)
                {
                    mListGlobalPtr->mItemsData[k].done = true;
                    GlobalDataObj->ModsDataObj[k].done = true;
                }
            }
        }
    }
}

QString ModpacksContent::getModlistName(uint64_t index){
    return mModpacksData[index].modpackName;
}

void ModpacksContent::modlistAmount()
{
    if(mModpacksData.size() > 0)
    {
        mModpacksData.clear();
    }

    std::string path = GlobalDataObj->LocalSettingsObj.localPath.toStdString()
            + "\\Modpacks\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            ;

    if(std::filesystem::exists(path)){
        for(auto& i: std::filesystem::directory_iterator{path})
        {
            std::string name{i.path().filename().generic_string()};
            name.erase(name.size() - 4, 4);

            QVector<uint32_t> modsId;
            QVector<QString> modFileName;
            std::string text;


            std::fstream file;
            file.open(path + "\\" + name + ".txt", std::ios::in);
            while(file>>text)
            {
                if(text == "S")
                {
                    uint64_t id;
                    file>>id;
                    modFileName.emplaceBack("");
                    modsId.emplaceBack(id);
                }
                else if(text == "L")
                {
                    std::string fileName;
                    file>>fileName;
                    modFileName.emplaceBack(QString::fromStdString(fileName));
                    modsId.emplaceBack(0);
                }
            }

            mModpacksData.append({
                                     QString::fromUtf8(name),
                                     modsId,
                                     modFileName
                                 });
        };
    }
}
