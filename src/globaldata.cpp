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
