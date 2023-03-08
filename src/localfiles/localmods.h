#ifndef LOCALMODS_H
#define LOCALMODS_H

#include <QObject>
#include <filesystem>

class LocalMods : public QObject
{
    Q_OBJECT
public:
    explicit LocalMods(QObject* parent = nullptr);

    bool gameFolderCheck();
    bool loadLocalMods();
    bool loadSingleMod(const std::filesystem::directory_entry& mod, const std::string& path);
};

#endif // LOCALMODS_H
