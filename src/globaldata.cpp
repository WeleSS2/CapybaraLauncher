#include "globaldata.h"

sGamesData* GlobalData::getGameById(uint64_t id){
    for(auto& i : LocalSettingsObj.installedGames){
        if(i.gameId == id)
        {
            return &i;
        }
    }
    return nullptr;
}
sModsData* GlobalData::getModById(uint64_t id){
    for(auto& i : ModsDataObj)
    {
        if(i.laucherId == id)
        {
            return &i;
        }
    }
    return nullptr;
}

sModsData* GlobalData::getModBySteamId(uint64_t id){
    for(auto& i : ModsDataObj)
    {
        if(i.steamModGameId == id)
        {
            return &i;
        }
    }
    return nullptr;
}
