#include "globaldata.h"

ModsData::ModsData()
{

}

GlobalData::GlobalData() : data(new GlobalDataData)
{

}

GlobalData::GlobalData(const GlobalData &rhs)
    : data{rhs.data}
{

}

GlobalData &GlobalData::operator=(const GlobalData &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

GlobalData::~GlobalData()
{

}

GlobalModpacksData::GlobalModpacksData()
{

}

sGamesData& GlobalDataData::getGameById(uint64_t id){
    for(auto& i : SharedGlobalDataObj->Global_LocalSettingsObj.installedGames){
        if(i.gameId == id)
        {
            return i;
        }
    }
}
