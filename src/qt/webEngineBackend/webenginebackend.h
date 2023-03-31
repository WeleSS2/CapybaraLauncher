#pragma once

#include <QObject>
#include <QUrl>

class WebEngineBackend : public QObject
{
    Q_OBJECT
public:
    explicit WebEngineBackend(QObject *parent = nullptr);
    Q_INVOKABLE uint64_t downloadModFromUrl(const QString& currentUrl);
    Q_INVOKABLE QUrl fromUserInput(const QString& input);
};
