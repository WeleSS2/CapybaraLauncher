#ifndef LOCALFILES_H
#define LOCALFILES_H

#include <QObject>
#include <iostream>
#include <string>
#include <cstdlib>

// Depraceted due to using now .js files to save/load data


class localFiles: public QObject
{
    Q_OBJECT
public:
    explicit localFiles(QObject *parent = nullptr){};

    std::string localWh3Path = "";
public slots:
    bool findLocalFolder();
    bool findLocalDataTxt(std::string &path);
    void loadLocalSettings();
    void loadLocalModlist();
    void saveLocalSettings();
    void saveLocalModlist();

private:
    bool saveTo(QString* target, std::string& value);
    //bool loadSetting(const std::fstream& file, const std::string& target, const std::string value);
};

#endif // LOCALFILES_H
