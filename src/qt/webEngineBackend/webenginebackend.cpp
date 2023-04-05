#include "webenginebackend.h"
#include <QDebug>

WebEngineBackend::WebEngineBackend(QObject *parent)
    : QObject{parent}
{

}

QUrl WebEngineBackend::fromUserInput(const QString& input){
    if (input.isEmpty())
        return QUrl::fromUserInput("about:blank");
    const QUrl result = QUrl::fromUserInput(input);
    return result.isValid() ? result : QUrl::fromUserInput("about:blank");
}

uint64_t WebEngineBackend::downloadModFromUrl(const QString& currentUrl){
    if(currentUrl.indexOf("=") != -1)
    {
        uint64_t num = currentUrl.mid(currentUrl.indexOf("=") + 1).toULongLong();
        return currentUrl.mid(currentUrl.indexOf("=") + 1).toULongLong();
    }
    else
    {
        return 0;
    }
}
