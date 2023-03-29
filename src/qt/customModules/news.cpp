#include "news.h"

#include "../../github/githubnews.h"
#include "../../globaldata.h"

News::News(QObject* parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int News::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return mList->get_vArticles()->size();
}

QVariant News::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
        return QVariant();

    if(index.row() >= mList->get_vArticles()->size())
        return QVariant();

    switch(role)
    {
    case dateRole:
    { return mList->get_vArticles()->at(index.row()).date; }
    case imageRole:
    { return mList->get_vArticles()->at(index.row()).imageUrl; }
    case titleRole:
    { return mList->get_vArticles()->at(index.row()).title; }
    case descriptionRole:
    { return mList->get_vArticles()->at(index.row()).description; }
    case articleRole:
    { return mList->get_vArticles()->at(index.row()).article; }
    }

    return QVariant();
}

bool News::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    if(index.row() >= mList->get_vArticles()->size())
        return false;

    NewsItem item = mList->get_vArticles()->at(index.row());
    switch(role)
    {
    case dateRole:
    { item.date = value.toULongLong(); break; }
    case imageRole:
    { item.imageUrl = value.toString(); break; }
    case titleRole:
    { item.title = value.toString(); break; }
    case descriptionRole:
    { item.description = value.toString(); break; }
    case articleRole:
    { item.article = value.toString(); break; }
    }

    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags News::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> News::roleNames() const
{
    QHash<int, QByteArray> names;
    names[dateRole] = "Ndate";
    names[imageRole] = "Nimage";
    names[titleRole] = "Ntitle";
    names[descriptionRole] = "Ndescription";
    names[articleRole] = "Narticle";
    return names;
}

NewsList *News::list() const
{
    return mList;
}

void News::setList(NewsList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &NewsList::preItemAppened, this, [=]() {
            beginResetModel();
        });
        connect(mList, &NewsList::postItemAppened, this, [=]() {
            endResetModel();
        });
    }

    endResetModel();
}

void News::refreshList()
{
    beginResetModel();

    endResetModel();
}

/*--------------------------------------------------------------------------
 *
 *                     CA, Dev and other important News
 *
 *--------------------------------------------------------------------------
 */


DevNewsList::DevNewsList(QObject* parent)
    : NewsList{parent}
{

}

bool DevNewsList::setItemAt(int index, const NewsItem &item)
{
    if(index < 0 || index >= mNews.size())
        return false;

    const NewsItem &oldItemData = mNews.at(index);
    if(item.date == oldItemData.date)
        return false;

    mNews[index] = item;
    return true;
}

void DevNewsList::appendItem()
{
    emit preItemAppened();

    NewsItem item;
    mNews.append(item);

    emit postItemAppened();
}

void DevNewsList::removeItem(uint64_t position)
{
    for(int i = 0; i < mNews.size(); ++i)
    {
        emit preItemRemoved(position);

        mNews.removeAt(position);

        emit postItemRemoved();
    }
}

void DevNewsList::clearNewsVector()
{
    mNews.clear();
}

void DevNewsList::loadNews(uint64_t gameId){
    // Create a new thread to load the news items
    NewsLoader* loader = new NewsLoader(this, gameId, "dev_ca");
    connect(loader, &NewsLoader::finished, loader, &NewsLoader::deleteLater);
    loader->start();
}

void DevNewsList::setNews(const QVector<NewsItem>& news) {
    mNews = news;

    // Emit the newsLoaded signal
    emit newsLoaded();
}

/*--------------------------------------------------------------------------
 *
 *                              Community News
 *
 *--------------------------------------------------------------------------
 */


CommunityNewsList::CommunityNewsList(QObject *parent)
    : NewsList{parent}
{

}

bool CommunityNewsList::setItemAt(int index, const NewsItem &item)
{
    if(index < 0 || index >= mNews.size())
        return false;

    const NewsItem &oldItemData = mNews.at(index);
    if(item.date == oldItemData.date)
        return false;

    mNews[index] = item;
    return true;
}

void CommunityNewsList::appendItem()
{
    emit preItemAppened();

    NewsItem item;
    mNews.append(item);

    emit postItemAppened();
}

void CommunityNewsList::removeItem(uint64_t position)
{
    for(int i = 0; i < mNews.size(); ++i)
    {
        emit preItemRemoved(position);

        mNews.removeAt(position);

        emit postItemRemoved();
    }
}

void CommunityNewsList::clearNewsVector()
{
    mNews.clear();
}

void CommunityNewsList::loadNews(uint64_t gameId){
    // Create a new thread to load the news items
    NewsLoader* loader = new NewsLoader(this, gameId, "community");
    connect(loader, &NewsLoader::finished, loader, &NewsLoader::deleteLater);
    loader->start();
}

void CommunityNewsList::setNews(const QVector<NewsItem>& news) {
    mNews = news;

    // Emit the newsLoaded signal
    emit newsLoaded();
}
//-------------------------------------------------------------------------
//
//                              News Loader
//
//-------------------------------------------------------------------------


void NewsLoader::run()
{
    QVector<NewsItem> news;
    GithubNews objGithubNews;
    objGithubNews.getAllNews(news, mGameId, mFolder);

    // Move the news items to the main thread's event loop
    QMetaObject::invokeMethod(mList, "setNews",
                              Qt::QueuedConnection,
                              Q_ARG(QVector<NewsItem>, news));
}
