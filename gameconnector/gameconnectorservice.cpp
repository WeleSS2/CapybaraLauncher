#include "gameconnectorservice.h"

GameConnectorService::GameConnectorService(QObject *parent)
    : QObject{parent}
{
    //QRemoteObjectHost host(QUrl(QStringLiteral("local:gameConnectorService")));
    //host.enableRemoting(this, "gameConnectorService");
}

void GameConnectorService::testFunction()
{
    qDebug() << "Simple message";
}
