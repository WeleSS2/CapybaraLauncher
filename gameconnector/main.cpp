#include <iostream>
#include "steam_api.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QSharedMemory>
#include <QtCore/QBuffer>
#include <QtCore/QDataStream>
#include <QDebug>

bool sendDataToSharedMemory(QSharedMemory& sharedMemory, const QString& data)
{
    // Create the buffer to hold the data
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);
    qDebug() << buffer.size();
    stream << data;
    qDebug() << buffer.size();
    // Attach the shared memory to the process
    //if (!sharedMemory.create(buffer.size())) {
    //    qWarning() << "Failed to create shared memory.";
    //    return false;
    //}
    qDebug() << sharedMemory.create(buffer.size());
    qDebug() << buffer.size();
    // Write the data to the shared memory
    sharedMemory.lock();
    char *to = (char*)sharedMemory.data();
    const char *from = buffer.constData();
    memcpy(to, from, qMin(sharedMemory.size(), buffer.size()));
    sharedMemory.unlock();

    qDebug() << "Data sent to shared memory." << buffer.size();;

    return true;
}

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    // Create the shared memory object
    QSharedMemory sharedMemory("MySharedMemory");

    // Send some data to the shared memory
    QString data = "GameConnector launched correctly, testing bugger size";
    sendDataToSharedMemory(sharedMemory, data);

    //while(!std::cin)
    //{

    //}

    return a.exec();
}
