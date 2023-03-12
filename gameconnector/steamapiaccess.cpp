#include "steamapiaccess.h"


SteamAPIAccess::SteamAPIAccess(QObject *parent)
{

}

const SteamAPICall_t SteamAPIAccess::getSteamAPICall(){
    return hSteamAPiCall;
}

void SteamAPIAccess::loadModsFromSteam(){

}

void SteamAPIAccess::subscribeMod()
{

}

void SteamAPIAccess::unsubscribeMod()
{

}

void SteamAPIAccess::getModDetails()
{

}

template<class T>
void SteamAPIAccess::setDataToSharedMemory(T& data){

}

template<class T>
void SteamAPIAccess::readDataFromSharedMemory(T& data){

}

void SteamAPIAccess::setActionStatus(bool& status){

}

void SteamAPIAccess::modCallback(SteamUGCQueryCompleted_t *result, bool fail)
{

}

bool SteamAPIAccess::waitUntilCallNotFInished(SteamAPICall_t *call)
{
    return false;
}
