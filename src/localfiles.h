#ifndef LOCALFILES_H
#define LOCALFILES_H

#include <QObject>
#include <iostream>
#include <string>
#include <cstdlib>

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
};

#endif // LOCALFILES_H
