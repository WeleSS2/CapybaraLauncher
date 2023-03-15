#include <iostream>
#include "steam_api.h"
#include "steamapiaccess.h"

#include <QObject>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>

#include <QtCore/QCoreApplication>
#include <QtCore/QSharedMemory>
#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include <QDebug>

#include "gameconnectorservice.h"

//bool sendDataToSharedMemory(QSharedMemory& sharedMemory, const QString& data)
//{
//    // Create the buffer to hold the data
//    QByteArray buffer;
//    QDataStream stream(&buffer, QIODevice::WriteOnly);
//    stream << data;
//
//    // Attach the shared memory to the process
//    if (!sharedMemory.create(buffer.size())) {
//        qWarning() << "Failed to create shared memory.";
//        return false;
//    }
//
//    // Write the data to the shared memory
//    sharedMemory.lock();
//    char *to = (char*)sharedMemory.data();
//    const char *from = buffer.constData();
//    memcpy(to, from, qMin(sharedMemory.size(), buffer.size()));
//    sharedMemory.unlock();
//
//    qDebug() << "Data sent to shared memory." << buffer.size();;
//
//    return true;
//}

template<class T>
QByteArray toByteArray(const T& data){
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << data;
    return buffer;
}

QString myFunction(QString arg1, int arg2) {
    // Perform some action
    QString result = arg1 + QString::number(arg2);
    return result;
}


int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    //Instances for server
    GameConnectorService *ptrGameConnector = new GameConnectorService;

    if(SteamAPI_Init())
    {
        QLocalServer *server = new QLocalServer;
        server->listen("CapybaraWHGameConnector");

        if(!server->isListening())
        {
            qDebug() << "GameConnector: main: Server listening error!";
        }
        else
        {
            qDebug() << server->isListening();
        }

        QObject::connect(server, &QLocalServer::newConnection, [=]() {
            QLocalSocket *socket = server->nextPendingConnection();
            qDebug() << "Server: new connection";

            QObject::connect(socket, &QLocalSocket::readyRead, [=]() {
                // Read the incoming message
                QString message = QString(socket->readAll());
                qDebug() << "Server: message received: " << message;

                // Extract the function name and arguments from the message
                QString functionName = message.section(",", 0, 0);

                // GameConnector part
                if (functionName == "loadModsFromSteam") {
                    ptrGameConnector->loadModsFromSteam();
                }
                else if(functionName == "getModsData"){
                    while(!ptrGameConnector->getStatus())
                    {
                        qDebug() << ptrGameConnector->getStatus();
                        QThread::sleep(250);
                    }
                    socket->write(toByteArray<QVector<sModsData>>(ptrGameConnector->getModsData()));

                }
                else if(functionName == "getItemsAmount"){
                    socket->write(toByteArray<uint64_t>(ptrGameConnector->getItemsAmount()));
                }
                else if(functionName == "getItemsId"){
                    socket->write(toByteArray<QVector<uint64_t>>(ptrGameConnector->getItemsId()));
                }
                else if(functionName == "updateMod"){
                    uint64_t modId = message.section(",", 1, 1).toULongLong();
                    socket->write(toByteArray<bool>(ptrGameConnector->updateMod(modId)));
                }
                else if(functionName == "subscribeMod"){
                    uint64_t modId = message.section(",", 1, 1).toULongLong();
                    socket->write(toByteArray<bool>(ptrGameConnector->subscribeMod(modId)));
                }
                else if(functionName == "unsubscribeMod"){
                    uint64_t modId = message.section(",", 1, 1).toULongLong();
                    socket->write(toByteArray<bool>(ptrGameConnector->unsubscribeMod(modId)));
                }
                else {
                    socket->write("Error: Unknown function name");
                }

                socket->flush();
            });
        });
    }


    return a.exec();
}
