#include "cmodslistfilling.h"
#include "steamtools.h"
#include "globaldata.h"

cmodslistfilling::cmodslistfilling(QObject *parent)
    : QObject{parent}
{
    std::sort(SharedGlobalDataObj->Global_ModsDataObj.begin(), SharedGlobalDataObj->Global_ModsDataObj.end(), [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });
    for(int i = 0; i < SharedGlobalDataObj->Global_ModsDataObj.size(); ++i)
    {
        using namespace std;
        using namespace std::chrono;

        duration<long> dur(SharedGlobalDataObj->Global_ModsDataObj[i].steamDataInSeconds);
        SharedGlobalDataObj->Global_ModsDataObj[i].laucherId = i;
        string steamData = format("{:%Y.%m.%d}", sys_seconds{ dur });
        mItemsData.append( {
                               SharedGlobalDataObj->Global_ModsDataObj[i].done,
                               SharedGlobalDataObj->Global_ModsDataObj[i].color,
                               QString::fromUtf8(to_string(i).c_str()),
                               QString::fromUtf8(SharedGlobalDataObj->Global_ModsDataObj[i].steamModName.c_str()),
                               QString::fromUtf8(steamData.c_str()),
                               QString::fromUtf8(SharedGlobalDataObj->Global_ModsDataObj[i].steamPackname.c_str()),
                               SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId,
                               QString::fromUtf8(to_string(SharedGlobalDataObj->Global_ModsDataObj[i].steamAuthor).c_str())
                           });
    }
}

QVector<ItemsData> cmodslistfilling::Vs_ItemsData() const
{
    return mItemsData;
}

bool cmodslistfilling::setItemAt(int index, const ItemsData &item)
{
    if(index < 0 || index >= mItemsData.size())
        return false;

    const ItemsData &oldItemData = mItemsData.at(index);
    if(item.done == oldItemData.done && item.name == oldItemData.name)
        return false;

    mItemsData[index] = item;
    return true;
}

void cmodslistfilling::appendItem()
{
    emit preItemAppened();

    ItemsData item;
    item.done = false;
    mItemsData.append(item);

    emit postItemAppened();
}

void cmodslistfilling::removeItem(int position)
{
    for(int i = 0; i < mItemsData.size(); ++i)
    {
        emit preItemRemoved(position);

        mItemsData.removeAt(position);

        emit postItemRemoved();
    }
}

void cmodslistfilling::sortByActive()
{
    std::sort(SharedGlobalDataObj->Global_ModsDataObj.begin(), SharedGlobalDataObj->Global_ModsDataObj.end(), [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.done > second.done;
    });

    refreshModlistVector();
}

void cmodslistfilling::sortByDate()
{
    std::sort(SharedGlobalDataObj->Global_ModsDataObj.begin(), SharedGlobalDataObj->Global_ModsDataObj.end(), [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.steamDataInSeconds > second.steamDataInSeconds;
    });

    refreshModlistVector();
}

void cmodslistfilling::sortByName()
{
    std::sort(SharedGlobalDataObj->Global_ModsDataObj.begin(), SharedGlobalDataObj->Global_ModsDataObj.end(), [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.steamModName < second.steamModName;
    });

    refreshModlistVector();
}

void cmodslistfilling::sortByPackname()
{
    std::sort(SharedGlobalDataObj->Global_ModsDataObj.begin(), SharedGlobalDataObj->Global_ModsDataObj.end(), [](const ModsData& first, const ModsData& second) -> bool
    {
        return first.steamPackname < second.steamPackname;
    });

    refreshModlistVector();
}

void cmodslistfilling::refreshModlistVector(){
    mItemsData.clear();
    for(int i = 0; i < SharedGlobalDataObj->Global_ModsDataObj.size(); ++i)
    {
        using namespace std;
        using namespace std::chrono;
        duration<long> dur(SharedGlobalDataObj->Global_ModsDataObj[i].steamDataInSeconds);
        SharedGlobalDataObj->Global_ModsDataObj[i].laucherId = i;
        string steamData = format("{:%Y.%m.%d}", sys_seconds{ dur });
        mItemsData.append({
                               SharedGlobalDataObj->Global_ModsDataObj[i].done,
                               SharedGlobalDataObj->Global_ModsDataObj[i].color,
                               QString::fromUtf8(to_string(i).c_str()),
                               QString::fromUtf8(SharedGlobalDataObj->Global_ModsDataObj[i].steamModName.c_str()),
                               QString::fromUtf8(steamData.c_str()),
                               QString::fromUtf8(SharedGlobalDataObj->Global_ModsDataObj[i].steamPackname.c_str()),
                               SharedGlobalDataObj->Global_ModsDataObj[i].steamModGameId,
                               QString::fromUtf8(to_string(SharedGlobalDataObj->Global_ModsDataObj[i].steamAuthor).c_str())
                           });
    }
}
