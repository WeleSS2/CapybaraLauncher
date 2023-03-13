#pragma once

#include <QObject>
#include <QVariant>
#include <QtCore/QSharedMemory>
#include <QtCore/QBuffer>

class GameConnectorSharedMemory : public QObject
{
    Q_OBJECT
public:
    explicit GameConnectorSharedMemory(QObject *parent = nullptr);

    template<class T>
    void setDataToSharedMemory(T& data);

    template<class T>
    bool readDataFromSharedMemory(T& data);

    bool setWorkToDo();

    bool synchronizeWithGameConnector();

signals:

private:
    //Status of action did GameConnector did hes job
    QSharedMemory actionStatus{"ActionStatus"};

    //Memory to share data between apps
    QSharedMemory gameConnector{"GameConnector"};

};


// Read data from gameConnector
template<class T>
bool GameConnectorSharedMemory::readDataFromSharedMemory(T& data)
{
    // Attach to the shared memory object
    if (!gameConnector.attach()) {
        qDebug() << "Failed to attach to shared memory:" << gameConnector.errorString();
        qDebug() << gameConnector.attach();
        return false;
    }

    // Read the data from the shared memory
    QByteArray buffer;
    buffer.resize(gameConnector.size());
    gameConnector.lock();
    const char *from = (const char*)gameConnector.constData();
    char *to = buffer.data();
    memcpy(to, from, qMin(gameConnector.size(), buffer.size()));
    gameConnector.unlock();

    QDataStream stream(buffer);
    stream >> data;

    // Detach from the shared memory object
    gameConnector.detach();

    return true;
}

// Set data to gameConnector
template<class T>
void GameConnectorSharedMemory::setDataToSharedMemory(T& data){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << data;

    if(gameConnector.attach())
    {
        if(buffer.size() != gameConnector.size())
        {
            gameConnector.detach();
            gameConnector.create(buffer.size());
        }
    }
    else
        gameConnector.create(buffer.size());

    gameConnector.lock();
    char *to = (char*)gameConnector.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(gameConnector.size(), buffer.size()));
    gameConnector.unlock();

    gameConnector.detach();
}


