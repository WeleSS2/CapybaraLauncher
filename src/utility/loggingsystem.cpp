#include "loggingsystem.h"
#include "../globaldata.h"
#include <QFile>

LoggingSystem::LoggingSystem()
{

}

void LoggingSystem::saveLog(QString log)
{
    QString path = "C:";
    if(SharedGlobalDataObj->Global_LocalSettingsObj.localPath != "")
    {
        path = QString::fromStdString(SharedGlobalDataObj->Global_LocalSettingsObj.localPath) + "\\logs.txt";
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream in(&file);
    {
        in << "\n" << log;
        file.close();
    }
}
