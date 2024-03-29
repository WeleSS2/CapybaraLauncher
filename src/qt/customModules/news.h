#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QUrl>
#include <QThread>

class NewsList;

struct NewsItem{
    uint64_t date;
    QUrl imageUrl;
    QString title;
    QString description;
    QUrl article;
};

class News : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(NewsList *list READ list WRITE setList)
public:
    explicit News(QObject* parent = nullptr);

    enum {
        dateRole,
        imageRole,
        titleRole,
        descriptionRole,
        articleRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int tole = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    NewsList *list() const;
    void setList(NewsList *list);

    Q_INVOKABLE void refreshList();
private:
    NewsList *mList;
};

//-------------------------------------------------------------------------
//
//                                NewsList
//
//-------------------------------------------------------------------------

class NewsList : public QObject
{
    Q_OBJECT
public:
    explicit NewsList(QObject* parent = nullptr) : QObject{parent} {};

    virtual const QVector<NewsItem> *get_vArticles() const = 0;
    virtual uint64_t getNewsAmount() const = 0;
    virtual bool setItemAt(int index, const NewsItem &item) = 0;

signals:
    void preItemAppened();
    void postItemAppened();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    virtual void appendItem() = 0;
    virtual void removeItem(uint64_t position) = 0;
    virtual void clearNewsVector() = 0;
};

/*--------------------------------------------------------------------------
 *
 *                     CA, Dev and other important News
 *
 *--------------------------------------------------------------------------
 */

class DevNewsList : public NewsList
{
    Q_OBJECT
public:
    explicit DevNewsList(QObject* parent = nullptr);

    const QVector<NewsItem> *get_vArticles() const override {return &mNews; };
    uint64_t getNewsAmount() const override {return 10; };

    bool setItemAt(int index, const NewsItem &item) override;
public slots:
    void appendItem() override;
    void removeItem(uint64_t position) override;
    void clearNewsVector() override;

    void loadNews(uint64_t gameId);
    void setNews(const QVector<NewsItem> &news);

signals:
    void newsLoaded();

private:
    QVector<NewsItem> mNews;
};

/*--------------------------------------------------------------------------
 *
 *                              Community News
 *
 *--------------------------------------------------------------------------
 */

class CommunityNewsList : public NewsList
{
    Q_OBJECT
public:
    explicit CommunityNewsList(QObject* parent = nullptr);

    const QVector<NewsItem> *get_vArticles() const override {return &mNews; };
    uint64_t getNewsAmount() const override {return mNews.size(); };

    bool setItemAt(int index, const NewsItem &item) override;

public slots:
    void appendItem() override;
    void removeItem(uint64_t position) override;
    void clearNewsVector() override;

    void loadNews(uint64_t id);
    void setNews(const QVector<NewsItem> &news);

signals:
    void newsLoaded();

private:
    QVector<NewsItem> mNews;

};

//-------------------------------------------------------------------------
//
//                              News Loader
//
//-------------------------------------------------------------------------

class NewsLoader : public QThread {
public:
    NewsLoader(NewsList* list, uint64_t gameId, QString folder) :
        mList(list), mGameId(gameId), mFolder(folder) {}

    void run();

private:
    NewsList* mList;
    uint64_t mGameId;
    QString mFolder;
};
