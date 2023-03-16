#include "steamapiaccess.h"
#include <QtNetwork/QLocalSocket>
#include <QThread>
#include <QProcess>
#include <QFileInfo>
#include <QDateTime>


#include <Windows.h>
#include <filesystem>

#include "src/utility/loggingsystem.h"

SteamApiAccess::SteamApiAccess(QObject *parent)
    : QObject{parent}
{
    //m_remoteHost = new QRemoteObjectHost(QUrl(QStringLiteral("local:gameConnectorService")));
    //m_connectorService = m_remoteHost->acquire<GameConnectorService>();
}
// Run GameConnector to get access to steamapi service
bool SteamApiAccess::runGameSteamAPI(){
    //QProcess process;
    //process.start("GameConnector.exe");
    //process.waitForFinished();
    //return true;

    std::string run = "start \"\" \"GameConnector.exe\"";
    int result = system(run.c_str());
    if(result)
    {
        return true;
    }
    else
    {
        int limit = 0;
        QProcess process;
        process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq GameConnector.exe");
        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        while(limit < 200)
        {
            if(output.contains("GameConnector.exe"))
            {
                qDebug() << "GameChanger is on";
                return true;
            }
            limit++;
            Sleep(10);
        }
    }
    LoggingSystem::saveLog("steamapiaccess.cpp: closeGameSteamAPI: Running GameConnector in Capybara Launcher failed!");
    return false;
}

// Check did any GameConnector with is running, if yes kill it.
bool SteamApiAccess::closeGameSteamAPI(){
    QProcess process;
    process.start("tasklist", QStringList() << "/FI" << "IMAGENAME eq GameConnector.exe");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    if(output.contains("GameConnector.exe")){
        QProcess::execute("taskkill", QStringList() << "/F" << "/IM" << "GameConnector.exe");
        return true;
    }
    else
    {
        LoggingSystem::saveLog("steamapiaccess.cpp: closeGameSteamAPI: Closing GameConnector when closing a Capybara Launcher failed!");
        return true;
    }
}

void SteamApiAccess::loadModsDataSteam(){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if(!socket.waitForConnected(2000))
    {
        LoggingSystem::saveLog("SteamApiAccess: loadModsDataSteam: Failed to load steam data");
    }
    else
    {
        QString message = "loadModsFromSteam";
        socket.write(message.toUtf8());
        socket.flush();
        if(socket.waitForReadyRead(1000)){

        }
    }
}

void SteamApiAccess::getModsData(){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if (!socket.waitForConnected(2000)) {
        LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to connect to server");
    }
    else
    {
        QString message = "getModsData";
        socket.write(message.toUtf8());
        socket.flush();

        if(socket.waitForReadyRead(30000)){
            QByteArray data = socket.readAll();
            QDataStream in(data);
            in >> GlobalDataObj->ModsDataObj;
        }
        else
        {
            LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to load data from server");
        }
    }
}

    void SteamApiAccess::setModsPackname(){
        for(auto& i : GlobalDataObj->ModsDataObj)
        {
            setModPackname(i);
        }
    }

void SteamApiAccess::setModPackname(sModsData& mod){
    std::string path = GlobalDataObj->LocalSettingsObj.currentGame.gamePath.toStdString()
            + "\\steamapps\\workshop\\content"
            + "\\"
            + std::to_string(GlobalDataObj->LocalSettingsObj.currentGame.gameId)
            + "\\"
            + std::to_string(mod.steamModGameId);
    if(std::filesystem::exists(path)){
        for(auto const& dir_entry : std::filesystem::directory_iterator{path}){
            std::string temp{dir_entry.path().string()};
            std::string s2 = temp.substr(temp.size() - 4, 4);
            if(s2 == "pack")
            {
                temp.erase(0, path.size() + 1);
                mod.steamPackname = QString::fromStdString(temp);
            }
        }

        // Check for update
        QFileInfo fileInfo(QString::fromStdString(path));
        if(fileInfo.exists()){
            QDateTime lastModified = fileInfo.lastModified();
            if(mod.steamDataInSeconds > lastModified.toMSecsSinceEpoch() / 1000)
            {
                mod.color = {225, 225, 0};
            }
        }
    }
    else
    {
        mod.color = {255, 55, 55};
        mod.steamModName = "Mod not available locally";
    }
}

bool SteamApiAccess::updateMod(uint64_t id){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if(!socket.waitForConnected(2000))
    {
        LoggingSystem::saveLog("SteamApiAccess: loadModsDataSteam: Failed to load steam data");
        return false;
    }
    else
    {
        QString message = "updateMod," + QString::fromStdString(std::to_string(id));
        socket.write(message.toUtf8());
        socket.flush();
        if(socket.waitForReadyRead(3600000)){
            bool check;
            QByteArray data = socket.readAll();
            QDataStream in(data);
            in >> check;
            if(check)
                return true;
            else
                return false;
        }
        else
        {
            LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to load data from server");
            return false;
        }
    }
}

bool SteamApiAccess::subscribeMod(uint64_t id){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if(!socket.waitForConnected(2000))
    {
        LoggingSystem::saveLog("SteamApiAccess: loadModsDataSteam: Failed to load steam data");
        return false;
    }
    else
    {
        QString message = "subscribeMod," + QString::fromStdString(std::to_string(id));
        socket.write(message.toUtf8());
        socket.flush();
        if(socket.waitForReadyRead(3600000)){
            bool check;
            QByteArray data = socket.readAll();
            QDataStream in(data);
            in >> check;
            if(check)
                return true;
            else
                return false;
        }
        else
        {
            LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to load data from server");
            return false;
        }
    }
}

bool SteamApiAccess::unsubscribeMod(uint64_t id){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if(!socket.waitForConnected(2000))
    {
        LoggingSystem::saveLog("SteamApiAccess: loadModsDataSteam: Failed to load steam data");
        return false;
    }
    else
    {
        QString message = "unsubscribeMod," + QString::fromStdString(std::to_string(id));
        socket.write(message.toUtf8());
        socket.flush();
        if(socket.waitForReadyRead(3600000)){
            bool check;
            QByteArray data = socket.readAll();
            QDataStream in(data);
            in >> check;
            if(check)
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to load data from server");
            return false;
        }
    }
}

sModsData SteamApiAccess::getModData(uint64_t id){
    QLocalSocket socket;
    linkToServer(&socket, 20);
    if(!socket.waitForConnected(2000))
    {
        LoggingSystem::saveLog("SteamApiAccess: loadModsDataSteam: Failed to load steam data");
    }
    else
    {
        QString message = "getModData," + QString::fromStdString(std::to_string(id));
        socket.write(message.toUtf8());
        socket.flush();
        if(socket.waitForReadyRead(3600000)){
            sModsData retObj;
            QByteArray data = socket.readAll();
            QDataStream in(data);
            in >> retObj;
            qDebug() << retObj.steamModName;
            return retObj;
        }
        else
        {
            LoggingSystem::saveLog("SteamApiAccess: getSaveModsData: Failed to load data from server");
        }
    }
}

// socket to connect and maxAttemps to connect, delay between attemps is 250ms
void SteamApiAccess::linkToServer(QLocalSocket* socket, int maxAttemps){
    for(int i = 0; i < maxAttemps; ++i){
        socket->connectToServer("CapybaraWHGameConnector");
        if(socket->waitForConnected()){
            break;
        }
        else
        {
            QThread::msleep(250);
        }
    }
}


QString SteamApiAccess::callTestFunction(){
    // Create the local socket to connect to the server
    QLocalSocket socket;
    socket.connectToServer("CapybaraWHGameConnector");
    if (!socket.waitForConnected(2000)) {
        qDebug() << "SteamApiAccess: callTestFunction: Failed to connect to server: " << socket.errorString();
        return "Error";
    }
    else
    {
        // Send a message containing the function name and arguments
        QString message = "myFunction,arg1,42";
        qDebug() << socket.isValid() << socket.isOpen() << message.toUtf8();
        socket.write(message.toUtf8());
        socket.flush();

        // Wait for a response from the server
        if (socket.waitForReadyRead(2000)) {
            // Read the response and use it as desired
            QString result = QString(socket.readAll());
            return result;
        }
        else
        {
            qDebug() << "SteamApiAccess: callTestFunction: Failed to get server ready." << socket.errorString();
            return "Error";
        }
    }
}
