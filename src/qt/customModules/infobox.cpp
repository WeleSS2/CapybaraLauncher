#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlProperty>
#include <QTimer>
#include "infobox.h"
#include "../../globaldata.h"

InfoBox::InfoBox(QObject *parent)
    : QObject(parent)
{
    SharedGlobalDataObj->enginePtr->rootContext()->setContextProperty("infoBox", nullptr);

    SharedGlobalDataObj->enginePtr->rootContext()->setContextProperty("infoBox", this);
}

void InfoBox::show() {
    QMetaObject::invokeMethod(this, "show");
}
