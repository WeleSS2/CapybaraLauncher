#ifndef FILESOPERATIONS_H
#define FILESOPERATIONS_H

#include <QObject>

// Class to hold opeartions on files
class FilesOperations: public QObject
{
    Q_OBJECT
public:
    explicit FilesOperations(QObject *parent = nullptr);

    // Find option or anything in file, operation is a number to log if failed
    bool findStringInFile(const QString& filePath, const QString searchString, const QString operation);

    // Save all settings to .js
    bool saveSettings();

    // Load all settings from .js and save them in the struct
    bool loadSettings();

private:
    // Find did local folder appData exist, if not create him
    QString findLocalFolder();
};

#endif // FILESOPERATIONS_H
