#ifndef SETTINGSMODULE_H
#define SETTINGSMODULE_H

#include <QObject>

class SettingsModule : public QObject
{
    Q_OBJECT
public:
    explicit SettingsModule(QObject *parent = nullptr);

signals:

};

#endif // SETTINGSMODULE_H
