#ifndef MODPACKSCONTENT_H
#define MODPACKSCONTENT_H

#include <QObject>
#include <vector>
#include <QVector>

#include "cmodslistfile.h"

struct ModpacksData
{
    QString modpackName;
    QVector<uint32_t> modsId;
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

#endif // MODPACKSCONTENT_H
