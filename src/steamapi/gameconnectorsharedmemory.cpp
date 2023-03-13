#include "gameconnectorsharedmemory.h"

#include "Windows.h"

GameConnectorSharedMemory::GameConnectorSharedMemory(QObject *parent)
    : QObject{parent}
{

}


bool GameConnectorSharedMemory::setWorkToDo(){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << false;

    if(!actionStatus.attach()){
        actionStatus.create(buffer.size());
    }

    actionStatus.lock();
    char *to = (char*)actionStatus.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(actionStatus.size(), buffer.size()));
    actionStatus.unlock();

    actionStatus.detach();
    return true;
}

bool GameConnectorSharedMemory::synchronizeWithGameConnector(){
    Sleep(100);
    if(!actionStatus.attach()){
        return false;
    }

    QByteArray buffer;
    buffer.resize(actionStatus.size());
    actionStatus.lock();
    const char *from = (const char*)actionStatus.constData();
    char *to = buffer.data();
    memcpy(to, from, qMin(actionStatus.size(), buffer.size()));
    actionStatus.unlock();

    bool status;
    QDataStream stream(buffer);
    stream >> status;

    if(!status)
        return false;

    actionStatus.detach();
    return true;
}
