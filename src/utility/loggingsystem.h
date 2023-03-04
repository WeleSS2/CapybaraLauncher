#ifndef LOGGINGSYSTEM_H
#define LOGGINGSYSTEM_H

#include <QObject>


// Class to save logs into local folder or if he isn;t builded yet to save them directly on C
class LoggingSystem
{
public:
    LoggingSystem();

    // Save log in logs.txt
    static void saveLog(QString log);
};

#endif // LOGGINGSYSTEM_H
