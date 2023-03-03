#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>

class Utility
{
public:
    Utility();

    void qtWait(uint64_t _time);
    void showSimpleInfoBox(QString _text);
};

#endif // UTILITY_H
