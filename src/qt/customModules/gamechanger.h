#ifndef GAMECHANGER_H
#define GAMECHANGER_H

#include <QObject>
#include <QAbstractListModel>
#include "../../steamapi/steamapiaccess.h"

class cGameChangerList;

class GameChanger : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(cGameChangerList *list READ list WRITE setList)
public:
    explicit GameChanger(QObject *parent = nullptr);

    enum {
        NameRole,
        GameIdRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    cGameChangerList *list() const;
    void setList(cGameChangerList *list);
    //
        Q_INVOKABLE void setCurrentGame(uint64_t index) const;
        void fileSaver() const;
    //

    Q_INVOKABLE int getCurrentGameId() const;
private:
    cGameChangerList *mList;
};




// ---------------- List object ------------------

class cGameChangerList : public QObject
{
    Q_OBJECT
public:
    explicit cGameChangerList(QObject *parent = nullptr);

    QVector<sGamesData> vsGamesData() const;

    bool setItemAt(int index, const sGamesData &item);

signals:
    void preItemAppened();
    void postItemAppened();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    bool appendItem(QString name);
    void removeItem(qint32 index);

    Q_INVOKABLE uint64_t getGameId(uint64_t index);
};

#endif // GAMECHANGER_H
