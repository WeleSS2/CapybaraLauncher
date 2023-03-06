#include "loggingsystem.h"
#include "../globaldata.h"
#include <QFile>

LoggingSystem::LoggingSystem()
{

}

void LoggingSystem::saveLog(QString log)
{
    QString path = "C:\\logs.txt";
    if(SharedGlobalDataObj->Global_LocalSettingsObj.localPath != "")
    {
        path = QString::fromStdString(SharedGlobalDataObj->Global_LocalSettingsObj.localPath) + "\\logs.txt";
    }

    QFile file(path);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    {
        qDebug() << log;
        in << log << "\n";
        file.close();
    }
}

void LoggingSystem::clearLogs(){
    QString path = "C:\\logs.txt";
    if(SharedGlobalDataObj->Global_LocalSettingsObj.localPath != "")
    {
        path = QString::fromStdString(SharedGlobalDataObj->Global_LocalSettingsObj.localPath) + "\\logs.txt";
    }

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "";
        file.close();
    }
}
