#include "githubnews.h"

#include "QEventLoop"
#include "QObject"
#include "QNetworkReply"
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "QFile"
#include <openssl/ssl.h>

#include "../utility/loggingsystem.h"

GithubNews::GithubNews()
{

}

// Get universal and game specific news
const void GithubNews::getAllNews(QVector<NewsItem> &vector, uint64_t gameId, QString mainFolder){
    qDebug() << "Loading NEWS         " + mainFolder;
    getUniversalNews(vector, mainFolder);
    getNewsForGame(vector, gameId, mainFolder);
    if(vector.size() > 1)
    {
        std::sort(vector.begin(), vector.end(), [](const NewsItem& first, const NewsItem& second) -> bool{
            return first.date > second.date;
        });
    }
    if(vector.size() > 10)
    {
        vector.resize(10);
    }
}

// Main function which iterate inside a selected folder
const void GithubNews::getNewsForGame(QVector<NewsItem> &vector, uint64_t gameId, const QString mainFolder)
{
    QUrl url("https://api.github.com/repos/WeleSS2/WeleSS2.github.io/contents/" + mainFolder + "/" + QString::fromStdString(std::to_string(gameId)));
    getNews(vector, url);
}

const void GithubNews::getUniversalNews(QVector<NewsItem> &vector, const QString mainFolder){
    QUrl url("https://api.github.com/repos/WeleSS2/WeleSS2.github.io/contents/" + mainFolder + "/uni");
    getNews(vector, url);
}

const void GithubNews::getNews(QVector<NewsItem> &vector, const QUrl &url){
    QNetworkAccessManager manager;
    QNetworkRequest request(url);

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

                    // Set time when news have been uploaded
                    QString date = obj.value("name").toString().left(10);
                    QDateTime time = QDateTime::fromString(date, "dd.MM.yyyy");
                    vector[vector.size() - 1].date = static_cast<uint64_t>(time.toSecsSinceEpoch());
                    qDebug() << time << "    " <<  obj.value("name").toString();

                    // Set path for downloads
                    QString currentPath = obj.value("html_url").toString();
                    currentPath.erase(currentPath.begin(), currentPath.begin() + 55);
                    QString rawPath = "https://raw.githubusercontent.com/WeleSS2/WeleSS2.github.io/main/";
                    QString txtPath = rawPath + currentPath + "/info.txt";
                    QString pngPath = rawPath + currentPath + "/icon.png";
                    QString htmlPath = "https://weless2.github.io/" + currentPath + "/index.html";

                    getInfoFromTxt(vector, manager, QUrl(txtPath));


                    if (vector[vector.size() - 1].article.toString().size() < 2) {
                        QNetworkRequest requestHtml(htmlPath);
                        QNetworkReply* htmlReply = manager.head(requestHtml);

                        QEventLoop loopH;
                        QObject::connect(htmlReply, SIGNAL(finished()), &loopH, SLOT(quit()));
                        loopH.exec();
                        if(htmlReply->error() == QNetworkReply::NoError){
                            vector[vector.size() - 1].article = QUrl(htmlPath);
                        }
                    }
                    // Get image as icon
                    vector[vector.size() - 1].imageUrl = QUrl(pngPath);

                    if(vector[vector.size() - 1].article.toString().size() < 2)
                    {
                        vector.erase(std::prev(vector.end()));
                        LoggingSystem::saveLog("githubnews.cpp: getNews: News removed, index.html not found  " + htmlPath);
                    }
                }
                else
                    LoggingSystem::saveLog("githubnews.cpp: getNews: No objects!  " + url.toString());
            }
        }
        else
            LoggingSystem::saveLog("githubnews.cpp: getNews: Data not array!  " + url.toString());
    }
    else
        LoggingSystem::saveLog("githubnews.cpp: getNews: Can't connect to github!  " + url.toString());

}

// Get Title and Description from .txt file
const void GithubNews::getInfoFromTxt(QVector<NewsItem> &vector, QNetworkAccessManager &manager, const QUrl &path)
{
    QUrl fileUrl(path);
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
                vector[vector.size() - 1].title = line;
            }
            else if(line.contains("\"description\""))
            {
                line.erase(line.begin(), line.begin() + 13);
                vector[vector.size() - 1].description = line;
            }
            else if(line.contains("\"urlLink\""))
            {
                line.erase(line.begin(), line.begin() + 10);
                vector[vector.size() - 1].article = QUrl(line);
            }
        }

    }
    else
        LoggingSystem::saveLog("githubnews.cpp: getInfoFromTxt: FileReply error!");

    fileReply->deleteLater();
}
