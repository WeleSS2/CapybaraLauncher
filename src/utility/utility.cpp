#include "utility.h"

#include <QTimer>
#include <QObject>
#include <QEventLoop>

#include "../globaldata.h"
#include "../qt/customModules/infobox.h"

Utility::Utility()
{

}

void Utility::qtWait(uint64_t _time){
    // Create a QTimer and start it
    QTimer timer;
    timer.setInterval(_time); // Wait for 1 second
    timer.setSingleShot(true);
    timer.start();

    // Pause the main thread until the QTimer times out
    QEventLoop loop;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    loop.exec();
}

void Utility::showSimpleInfoBox(QString _text){
    auto ObjInfoBox = std::make_shared<InfoBox>();
    ObjInfoBox->setBoxText(_text);

    ObjInfoBox->setBoxStatus(1);
    SharedGlobalDataObj->enginePtr->rootContext()->setContextProperty("ObjInfoBox", ObjInfoBox.get());

    qtWait(1000);
}
