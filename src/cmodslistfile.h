#ifndef CMODSLISTFILE_H
#define CMODSLISTFILE_H

#include <QAbstractListModel>
#include "steamtools.h"
#include "cmodslistfilling.h"

class CModsListFile : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(cmodslistfilling *list READ list WRITE setList)
public:
    explicit CModsListFile(QObject *parent = nullptr);

    enum {
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

    cmodslistfilling *list() const;
    void setList(cmodslistfilling *list);

    Q_INVOKABLE void refreshList();
private:
    cmodslistfilling *mList;
};
inline cmodslistfilling *mListGlobalPtr = nullptr;
#endif // CMODSLISTFILE_H
