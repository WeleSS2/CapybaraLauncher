#include "modpackscontent.h"

#include <iostream>
#include <fstream>
#include <filesystem>

#include "steam_api.h"
#include "globaldata.h"

ModpacksContent::ModpacksContent(QObject *parent)
    : QObject{parent}
{
    modlistAmount();
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
    SharedGlobalDataObj->Global_LocalSettingsObj.modpacksAmount++;

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
    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.localPath + "\\Modpacks\\"
            + name.toStdString() + ".txt";
    std::fstream file;
    file.open(path, std::ios::out);

    for(int i = 0; i < SharedGlobalDataObj->Global_LocalSettingsObj.modsAmount; ++i)
    {
        if(mListGlobalPtr->mItemsData[i].done)
        {
            file << mListGlobalPtr->mItemsData[i].modgameid << std::endl;
        }
    }
    file.close();
    appendItem(name);
}

void ModpacksContent::loadModlist(uint64_t index)
{
    for(int k = 0; k < mListGlobalPtr->mItemsData.size(); ++k)
    {
        mListGlobalPtr->mItemsData[k].done = false;
        SharedGlobalDataObj->Global_ModsDataObj[k].done = false;
    }

    for(int j = 0; j < mModpacksData[index].modsId.size(); ++j)
    {
        for(int k = 0; k < mListGlobalPtr->mItemsData.size(); ++k)
        {
            if(mModpacksData[index].modsId[j] == mListGlobalPtr->mItemsData[k].modgameid)
            {
                mListGlobalPtr->mItemsData[k].done = true;
                SharedGlobalDataObj->Global_ModsDataObj[k].done = true;
            }
        }
    }
}

void ModpacksContent::modlistAmount()
{
    std::string path = SharedGlobalDataObj->Global_LocalSettingsObj.localPath + "\\Modpacks";
    for(auto& i: std::filesystem::directory_iterator{path})
    {
        std::string name{i.path().filename().generic_string()};
        name.erase(name.size() - 4, 4);


        QVector<uint32_t> modsId;
        uint32_t text;


        std::fstream file;
        file.open(path + "\\" + name + ".txt", std::ios::in);
        while(file>>text)
        {
            modsId.emplaceBack(text);
        }


        mModpacksData.append({
                                 QString::fromUtf8(name),
                                 modsId
                             });
        modpacksAmountLocal++;
    };
    SharedGlobalDataObj->Global_LocalSettingsObj.modpacksAmount = modpacksAmountLocal;
}
