#include "filesoperations.h"

#include <QFile>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonDocument>


#include "loggingsystem.h"
#include "../globaldata.h"

FilesOperations::FilesOperations(QObject *parent){
    findLocalFolder();
};


bool findStringInFile(const QString& filePath, const QString searchString, const QString operation)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        LoggingSystem::saveLog(operation + " : Failed to find string in file.");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.contains(searchString))
        {
            return true;
        }
    }
    return false;
}

bool FilesOperations::saveSettings(){
    if(findLocalFolder() != ""){
        QFile file(findLocalFolder() + "\\settings.js");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "var settings = {" << Qt::endl;
            out << "  steamPath: R\""
                << QString::fromStdString(SharedGlobalDataObj->Global_LocalSettingsObj.steampath)
                << "\"," << Qt::endl;
            out << "};" << Qt::endl;


            file.close();
        }
        else
        {
            LoggingSystem::saveLog("filesoperations.cpp: saveSettings: Settings can't be saved, fileOpenError");
            return false;
        }
        return true;
    }
    else
    {
        LoggingSystem::saveLog("filesoperations.cpp: saveSettings: Settings can't be saved, localFolderError");
        return false;
    }
}

bool FilesOperations::loadSettings(){
    if(findLocalFolder() != ""){
        QFile file(findLocalFolder() + "\\settings.js");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString contents = in.readAll();
            file.close();

            // Parse contents as JavaScript object
            QJSEngine engine;
            QJSValue result = engine.evaluate(contents);

            // Get values from the object
            if (result.isObject()) {
                QJSValue steamPatchValue = result.property("steamPath");
                //SharedGlobalDataObj->Global_LocalSettingsObj.steampath = steamPatchValue.toString().toStdString();
                qDebug() << "STEAM PATCH:   " << steamPatchValue.toString() << result.toString();
            }
            else
            {
                LoggingSystem::saveLog("filesoperations.cpp: loadSettings: Settings can't be loaded, readingValuesError. Js error: " + result.toString());
                return false;
            }
        }
        else
        {
            LoggingSystem::saveLog("filesoperations.cpp: loadSettings: Settings can't be loaded, openFileError");
            return false;
        }
        return true;
    }
    else
    {
        LoggingSystem::saveLog("filesoperations.cpp: loadSettings: Settings can't be loaded, localFolderError");
        return false;
    }
}

QString FilesOperations::findLocalFolder(){
    bool success = false;
    char *pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, "APPDATA");

    if (err){
        LoggingSystem::saveLog("filesoperations.cpp: findLocalFolder(): Failed to open local settings");
        return "";
    }
    else{
        std::string path = std::string(pValue) + "\\CapybaraLaunchers";
        std::string pathWh3 = path + "\\WH3";
        if(std::filesystem::is_directory(path))
        {
            if(std::filesystem::is_directory(pathWh3))
            {
                SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
                return QString::fromStdString(pathWh3);
            }
            else
            {
                std::filesystem::create_directory(pathWh3);
                SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
                return QString::fromStdString(pathWh3);
            }
        }
        else
        {
            std::filesystem::create_directories(pathWh3);
            SharedGlobalDataObj->Global_LocalSettingsObj.localPath = pathWh3;
            return QString::fromStdString(pathWh3);
        }
    }
}
