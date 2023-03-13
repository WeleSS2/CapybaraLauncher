#pragma once
#include <QObject>
#include <QtRemoteObjects/QRemoteObjectHost>

class GameConnectorService : public QObject
{
    Q_OBJECT
public:
    explicit GameConnectorService(QObject *parent = nullptr);

public slots:
    void testFunction();

signals:
    void testSignal();

};
