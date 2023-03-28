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

// Get universal and game specific news
const void GithubNews::getAllNews(QVector<NewsItem> &vector, uint64_t gameId){
    getUniversalNews(vector);
    getNewsForGame(vector, gameId);
}

// Main function which iterate inside a selected folder
const void GithubNews::getNewsForGame(QVector<NewsItem> &vector, uint64_t gameId)
{
    QUrl url("https://api.github.com/repos/WeleSS2/WeleSS2.github.io/contents/" + QString::fromStdString(std::to_string(gameId)));
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
            QJsonArray files = json.array();
            // Loop to iterate through every folder inside
            for (const auto& file : files) {
                if (file.isObject()) {
                    vector.emplace_back();
                    QJsonObject obj = file.toObject();

                    // Get data from .txt file
                    std::tie(vector[vector.size() - 1].title, vector[vector.size() - 1].description) = getInfoFromTxt(manager, obj);

                    // Get html adress of website
                    vector[vector.size() - 1].article = getHtmlAdress(manager, obj);

                    // Get image as icon
                    vector[vector.size() - 1].imageUrl = getIcon(manager, obj);

                    if(vector[vector.size() - 1].article.toString().size() > 2)
                    {
                    }
                    else{
                        vector.erase(std::prev(vector.end()));
                        LoggingSystem::saveLog("githubnews.cpp: getNewsForGame: News removed, index.html not found");
                    }
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

const void GithubNews::getUniversalNews(QVector<NewsItem> &vector){
    QUrl url("https://api.github.com/repos/WeleSS2/WeleSS2.github.io/contents/uni");
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
            QJsonArray files = json.array();
            // Loop to iterate through every folder inside
            for (const auto& file : files) {
                if (file.isObject()) {
                    vector.emplace_back();
                    QJsonObject obj = file.toObject();

                    // Get data from .txt file
                    std::tie(vector[vector.size() - 1].title, vector[vector.size() - 1].description) = getInfoFromTxt(manager, obj);

                    // Get html adress of website
                    vector[vector.size() - 1].article = getHtmlAdress(manager, obj);

                    // Get image as icon
                    vector[vector.size() - 1].imageUrl = getIcon(manager, obj);

                    if(vector[vector.size() - 1].article.toString().size() > 2)
                    {
                    }
                    else{
                        vector.erase(std::prev(vector.end()));
                        LoggingSystem::saveLog("githubnews.cpp: getUniversalNews: News removed, index.html not found");
                    }
                }
                else
                    LoggingSystem::saveLog("githubnews.cpp: getUniversalNews: No objects!");
            }
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getUniversalNews: Data not array!");
    }
    else
        LoggingSystem::saveLog("githubnews.cpp: getUniversalNews: Can't connect to github! " + url.toString());

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

// Get adress from repo to files
const QUrl GithubNews::getHtmlAdress(QNetworkAccessManager &manager, const QJsonObject &obj){
    for (const auto& subfolderFile : returnSubfolderFiles(manager, obj)) {
        if (subfolderFile.isObject()) {
            QJsonObject subfolderObj = subfolderFile.toObject();
            QString subfolderName = subfolderObj.value("name").toString();
            QString subfolderDownloadUrl = subfolderObj.value("download_url").toString();

            if (subfolderName.endsWith(".html")) {
                QString str = subfolderDownloadUrl;
                str.erase(str.begin() + 8, str.begin() + 42);
                str.erase(str.begin() + 25, str.begin() + 30);
                str.erase(str.end() - 10, str.end());
                return QUrl(str + "index.html");
            }
            else
                LoggingSystem::saveLog("githubnews.cpp: getHtmlAdress: index.html not found!");
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getHtmlAdress: Not an object!");
    }
    return QUrl();
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
                return fileUrl;
            }
            else
                LoggingSystem::saveLog("githubnews.cpp: getIcon: No png file in directory!");
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getIcon: Not an object!");
    }
    return QUrl();
}
