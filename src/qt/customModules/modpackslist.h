#pragma once
#include <QAbstractListModel>


class ModpacksContent;

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
/* ----------------------------------------------------
 *
 *                ModpackList(Content)
 *
 * ----------------------------------------------------
 */

struct ModpacksData
{
    QString modpackName;
    QVector<uint32_t> modsId;
    QVector<QString> modFileName;
};

class ModpacksContent : public QObject
{
    Q_OBJECT
public:
    explicit ModpacksContent(QObject *parent = nullptr);

    QVector<ModpacksData> Vs_ModpacksData() const;

    bool setItemAt(int index, const ModpacksData &item);

    uint64_t getModpacksNumber(){return mModpacksData.size(); };

signals:
    void preItemAppened();
    void postItemAppened();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    bool appendItem(QString name);
    void removeItem(qint32 index);

    void saveModlist(QString name);
    void loadModlist(uint64_t index);

    Q_INVOKABLE QString getModlistName(uint64_t index);
    void modlistAmount();
private:
    QVector<ModpacksData> mModpacksData;
};
