#pragma once
#include "QNetworkAccessManager"
#include "QJsonObject"

#include "../qt/customModules/news.h"

class GithubNews
{
public:
    GithubNews();

    const void getNewsForGame(QVector<NewsItem> &vector, const uint64_t gameId);
    const void getInfoFromTxt(QNetworkAccessManager &manager, const QJsonObject &obj);
};
