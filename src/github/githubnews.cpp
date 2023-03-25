#include "githubnews.h"

#include "QEventLoop"
#include "QObject"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"

#include "../utility/loggingsystem.h"

GithubNews::GithubNews()
{

}

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
            for (const auto& file : files) {
                vector.emplace_back();
                if (file.isObject()) {
                    QJsonObject obj = file.toObject();
                    QString name = obj.value("name").toString();
                    QString downloadUrl = obj.value("download_url").toString();


                    vector[i].article = name;
                    vector[i].description = "Test " + QString::fromStdString(std::to_string(i));
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

const void GithubNews::getInfoFromTxt(QNetworkAccessManager &manager, const QJsonObject &obj)
{
    /*
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
                for (const auto& subfolderFile : subfolderFiles) {
                    if (subfolderFile.isObject()) {
                        QJsonObject subfolderObj = subfolderFile.toObject();
                        QString subfolderName = subfolderObj.value("name").toString();
                        QString subfolderDownloadUrl = subfolderObj.value("download_url").toString();

                        // Check if the file is a .txt file
                        if (subfolderName.endsWith(".txt")) {
                            // Download the file and process its contents
                            QNetworkRequest fileRequest(QUrl(subfolderDownloadUrl));
                            QNetworkReply *fileReply = manager.get(fileRequest);

                            QEventLoop fileLoop;
                            QObject::connect(fileReply, SIGNAL(finished()), &fileLoop, SLOT(quit()));
                            fileLoop.exec();

                            if(fileReply->error() == QNetworkReply::NoError)
                            {
                                QByteArray fileData = fileReply->readAll();
                                QString fileContents(fileData);

                                // Process the file contents however you need to
                                // ...

                            } else {
                                qWarning() << "Error downloading file" << subfolderDownloadUrl << ":" << fileReply->errorString();
                            }

                            fileReply->deleteLater();
                        }
                    }
                }
            }
        } else
            LoggingSystem::saveLog("githubnews.cpp: getInfoFromTxt: Errors while taking data from .txt");
    }
    */
}
