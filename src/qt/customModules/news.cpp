#include "news.h"

News::News(QObject* parent)
    : QAbstractTableModel(parent)
    , mList(nullptr)
{
}

int News::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return 1;
}

int News::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid() || !mList)
        return 0;

    return mList->getNewsAmount();
}

QVariant News::data(const QModelIndex &index, int role) const
{
    if(index.isValid() || !mList)
        return QVariant();

    if(index.row() == 0)
    {
        const NewsItem item = mList->get_vArticles().at(index.column() - 1);
                if (role == articleRole)
                    return QVariant(item.article);
    }
    return QVariant();
}

bool News::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    NewsItem item = mList->get_vArticles().at(index.column());

    if(mList->setItemAt(index.column(), item)){
        emit dataChanged(index, index, {role});
        return true;
    }

    return false;
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
    names[dateRole] = "date";
    names[articleRole] = "article";
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
           const int index = mList->get_vArticles().size();
           beginInsertColumns(QModelIndex(), index, index);
        });
        connect(mList, &NewsList::postItemAppened, this, [=]() {
           endInsertColumns();
        });
        connect(mList, &NewsList::preItemRemoved, this, [=](int index){
           beginRemoveColumns(QModelIndex(), index, index);
        });
        connect(mList, &NewsList::postItemRemoved, this, [=](){
           endRemoveColumns();
        });
    }
    endResetModel();
}

void News::refreshList()
{

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
    for(int i = 0; i < 10; ++i)
    {
        NewsItem item;
        item.date = i;
        item.article = "Item number " + QString::fromStdString(std::to_string(i));
        mNews.emplace_back(item);
    }
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


/*--------------------------------------------------------------------------
 *
 *                              Community News
 *
 *--------------------------------------------------------------------------
 */


CommunityNewsList::CommunityNewsList(QObject *parent)
    : NewsList{parent}
{
    for(int i = 0; i < 10; ++i)
    {
        NewsItem item;
        item.date = i;
        item.article = "Item number " + QString::fromStdString(std::to_string(i));
        mNews.emplace_back(item);
    }
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
