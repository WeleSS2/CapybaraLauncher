#ifndef steam_on_h
#define steam_on_h

#include <QObject>
#include <QVariant>

#include "iostream"
#include "steam_api.h"
#include "vector"
#include "algorithm"

class CSteamTools : public QObject
{
    Q_OBJECT
public:
    uint32 Ui_NumberOfItems;
    QVector<uint32> laucherItemId;
    QVector<std::string> localModName;
    QVector<uint64> VUi_ItemsId;
    QVector<SteamUGCDetails_t> Vs_ItemsData;
    CCallResult<CSteamTools, SteamUGCQueryCompleted_t> sContentCall;

    UGCQueryHandle_t qHandle;

    explicit CSteamTools(QObject *parent = nullptr){};

public slots:
    void LoadItemsToQuery();
    void LoadItemsDataFromQuery();
    void ItemsCallback(SteamUGCQueryCompleted_t * result, bool fail);
};
inline auto SharedSteamToolsObj = std::make_shared<CSteamTools>();

#endif
