#ifndef CMODSLISTFILLING_H
#define CMODSLISTFILLING_H

#include <QObject>
#include <QVector>
#include <QQUickItem>
#include "steam_api.h"
#include "QColor.h"

struct ItemsData
{
    bool done;
    QColor color;
    QString id;
    QString name;
    QString date;
    QString packname;
    uint64_t modgameid;
    QString author;
};

class cmodslistfilling : public QObject
{
    Q_OBJECT
public:
    explicit cmodslistfilling(QObject *parent = nullptr);

    QVector<ItemsData> Vs_ItemsData() const;

    bool setItemAt(int index, const ItemsData &item);
signals:
    void preItemAppened();
    void postItemAppened();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeItem(int position);


    void sortByActive();
    void sortByDate();
    void sortByName();
    void sortByPackname();

    void refreshModlistVector();


    void setListViewPointer(QQuickItem *List);
    QQuickItem* getListPointer();
public:
    QVector<ItemsData> mItemsData;

private:
    QQuickItem *mListView;
};

#endif // CMODSLISTFILLING_H
