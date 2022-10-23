#ifndef MODPACKSLIST_H
#define MODPACKSLIST_H

#include <QAbstractListModel>
#include "modpackscontent.h"
#include "globaldata.h"

class ModpacksList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ModpacksContent *list READ list WRITE setList)
public:
    explicit ModpacksList(QObject *parent = nullptr);

    enum {
        NameRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ModpacksContent *list() const;
    void setList(ModpacksContent *list);

    Q_INVOKABLE void refreshList();
private:
    ModpacksContent *mList;
};

#endif // MODPACKSLIST_H
