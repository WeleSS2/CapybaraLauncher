#pragma once
#include <QObject>
#include <QVector>
#include <QQUickItem>
#include <QColor>
#include <QAbstractListModel>

class ModsList;

class Mods : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ModsList *list READ list WRITE setList)
public:
    explicit Mods(QObject *parent = nullptr);

    ~Mods();

    enum {
        ColorRole,
        IdRole,
        DoneRole = Qt::UserRole,
        ModIdRole,
        NameRole,
        AuthorRole,
        DateRole,
        PacknameRole,
        GameModIdRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ModsList *list() const;
    void setList(ModsList *list);
    Q_INVOKABLE bool move(uint64_t sourceRow, uint64_t destinationRow);

    Q_INVOKABLE void refreshList();
private:
    ModsList *mList;
};
inline ModsList *mListGlobalPtr = nullptr;

/* ---------------------------------------------------------
 *
 *
 *
 * MODLIST MODULE
 *
 *
 *
 * ---------------------------------------------------------
 */

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

class ModsList : public QObject
{
    Q_OBJECT
public:
    explicit ModsList(QObject *parent = nullptr);

    QVector<ItemsData> *Vs_ItemsData();

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
    void pushItem(uint16_t id);

    QQuickItem *mListView;
};
