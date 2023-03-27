#pragma once
#include "QNetworkAccessManager"
#include "QJsonObject"
#include <QPair>

#include "../qt/customModules/news.h"

class GithubNews
{
public:
    GithubNews();

    const void getNewsForGame(QVector<NewsItem> &vector, const uint64_t gameId);
    const QPair<QString, QString> getInfoFromTxt(QNetworkAccessManager &manager, const QJsonObject &obj);
    const QJsonArray returnSubfolderFiles(QNetworkAccessManager &manager, const QJsonObject &obj);
    const QUrl getIcon(QNetworkAccessManager &manager, const QJsonObject &obj);
    const QUrl getHtmlAdress(QNetworkAccessManager &manager, const QJsonObject &obj);
};
