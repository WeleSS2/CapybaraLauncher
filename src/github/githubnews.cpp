#include "githubnews.h"

#include "QEventLoop"
#include "QObject"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include <openssl/ssl.h>

#include "../utility/loggingsystem.h"

GithubNews::GithubNews()
{

}


// Main function which iterate inside a selected folder
const void GithubNews::getNewsForGame(QVector<NewsItem> &vector, uint64_t gameId)
{
    QUrl url("https://api.github.com/repos/WeleSS2/CapybaraNEWS/contents/" + QString::fromStdString(std::to_string(gameId)));
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.github.v3+json");

    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(response);

        if (json.isArray()) {
            uint16_t i = 0;
            QJsonArray files = json.array();
            // Loop to iterate through every folder inside
            for (const auto& file : files) {
                vector.emplace_back();
                if (file.isObject()) {
                    QJsonObject obj = file.toObject();

                    // Get data from .txt file
                    std::tie(vector[i].title, vector[i].description) = getInfoFromTxt(manager, obj);
                    // Get image as icon
                    vector[i].imageUrl = getIcon(manager, obj);
                }
                else
                    LoggingSystem::saveLog("githubnews.cpp: getNewsForGame: No objects!");
            }
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getNewsForGame: Data not array!");
    }
    else
        LoggingSystem::saveLog("githubnews.cpp: getNewsForGame: Can't connect to github! " + url.toString());
}

const QJsonArray GithubNews::returnSubfolderFiles(QNetworkAccessManager &manager, const QJsonObject &obj){
    if (obj.value("type").toString() == "dir") {
        // Make a request to get the contents of the directory
        QNetworkRequest subfolderRequest(QUrl(obj.value("url").toString()));
        subfolderRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/vnd.github.v3+json");

        QNetworkReply *subfolderReply = manager.get(subfolderRequest);

        QEventLoop subfolderLoop;
        QObject::connect(subfolderReply, SIGNAL(finished()), &subfolderLoop, SLOT(quit()));
        subfolderLoop.exec();

        if(subfolderReply->error() == QNetworkReply::NoError)
        {
            QByteArray subfolderResponse = subfolderReply->readAll();
            QJsonDocument subfolderJson = QJsonDocument::fromJson(subfolderResponse);

            if (subfolderJson.isArray()) {
                QJsonArray subfolderFiles = subfolderJson.array();
                return subfolderFiles;
            }
            else
                LoggingSystem::saveLog("githubnews.cpp: returnSubfolderFiles: Subfolder is not a array!");
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: returnSubfolderFiles: Error while linking with folder!");
    }
    else
        LoggingSystem::saveLog("githubnews.cpp: returnSubfolderFiles: Error while looking for directory!");
    return QJsonArray();
}

// Get Title and Description from .txt file
const QPair<QString, QString> GithubNews::getInfoFromTxt(QNetworkAccessManager &manager, const QJsonObject &obj)
{
    QString title = "", desc = "";
    for (const auto& subfolderFile : returnSubfolderFiles(manager, obj)) {
        if (subfolderFile.isObject()) {
            QJsonObject subfolderObj = subfolderFile.toObject();
            QString subfolderName = subfolderObj.value("name").toString();
            QString subfolderDownloadUrl = subfolderObj.value("download_url").toString();

            // Check if the file is a .txt file
            if (subfolderName.endsWith(".txt")) {
                QUrl fileUrl(subfolderDownloadUrl);
                QNetworkRequest fileRequest(fileUrl);
                QNetworkReply *fileReply = manager.get(fileRequest);

                QEventLoop fileLoop;
                QObject::connect(fileReply, SIGNAL(finished()), &fileLoop, SLOT(quit()));
                fileLoop.exec();

                if(fileReply->error() == QNetworkReply::NoError)
                {
                    QByteArray fileData = fileReply->readAll();
                    QString fileContents(fileData);
                    QTextStream stream(&fileContents);
                    while (!stream.atEnd()) {
                        QString line = stream.readLine();
                        if (line.contains("\"title\"")) {
                            line.erase(line.begin(), line.begin() + 7);
                            title = line;
                        }
                        else if(line.contains("\"description\""))
                        {
                            line.erase(line.begin(), line.begin() + 13);
                            desc = line;
                        }
                    }

                }
                else
                    LoggingSystem::saveLog("githubnews.cpp: getInfoFromTxt: FileReply error!");

                fileReply->deleteLater();
            }
            else
                LoggingSystem::saveLog("githubnews.cpp: getInfoFromTxt: No txt file in directory!");
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getInfoFromTxt: Not an object!");
    }
    return QPair<QString, QString>(title, desc);
}

// Get icon image from .png file
const QUrl GithubNews::getIcon(QNetworkAccessManager &manager, const QJsonObject &obj){
    SSL_load_error_strings();
    SSL_library_init();
    for (const auto& subfolderFile : returnSubfolderFiles(manager, obj)) {
        if (subfolderFile.isObject()) {
            QJsonObject subfolderObj = subfolderFile.toObject();
            QString subfolderName = subfolderObj.value("name").toString();
            QString subfolderDownloadUrl = subfolderObj.value("download_url").toString();

            // Check if the file is a .png file
            if (subfolderName.endsWith(".png")) {
                QUrl fileUrl(subfolderDownloadUrl);
                QString str = fileUrl.toString();
                str.erase(str.begin() + 4, str.begin() + 5);
                qDebug() << str;
                return QUrl(str);
            }
            else
                LoggingSystem::saveLog("githubnews.cpp: getIcon: No png file in directory!");
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getIcon: Not an object!");
    }
    return QUrl();
}
