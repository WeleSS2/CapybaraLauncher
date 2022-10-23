#ifndef CMODSLISTFILLING_H
#define CMODSLISTFILLING_H

#include <QObject>
#include <QVector>
#include "steam_api.h"

struct ItemsData
{
    bool done;
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
    void removeItem();


    void sortByActive();
    void sortByDate();
    void sortByName();
    void sortByPackname();

public:
    QVector<ItemsData> mItemsData;
};

#endif // CMODSLISTFILLING_H
