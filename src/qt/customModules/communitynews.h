#ifndef COMMUNITYNEWS_H
#define COMMUNITYNEWS_H

#include <QObject>

class CommunityNews : public QObject
{
    Q_OBJECT
public:
    explicit CommunityNews(QObject* parent = nullptr);
};

#endif // COMMUNITYNEWS_H
