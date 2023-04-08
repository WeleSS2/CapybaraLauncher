#pragma once

#include <QThread>

class ThreadsOperations : public QThread
{
    Q_OBJECT

public:
    ThreadsOperations(std::function<void()> func)
        : m_func(func)
    {}

public slots:
    void runFunction()
    {
        m_func();
        emit finished();
    }

signals:
    void finished();

private:
    std::function<void()> m_func;
};
