#pragma once
#include "QNetworkAccessManager"
#include "QJsonObject"
#include <QJsonArray>
#include <QPair>

#include "../qt/customModules/news.h"

class GithubNews
{
public:
    GithubNews();

    const void getAllNews(QVector<NewsItem> &vector, const uint64_t gameId, const QString mainFolder);
    const void getNewsForGame(QVector<NewsItem> &vector, const uint64_t gameId, const QString mainFolder);
    const void getUniversalNews(QVector<NewsItem> &vector, const QString mainFolder);
    const void getInfoFromTxt(QVector<NewsItem> &vector, QNetworkAccessManager &manager, const QUrl &adress);

private:
    QJsonArray listedFiles;
};
