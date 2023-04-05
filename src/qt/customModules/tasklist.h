#pragma once

#include <QObject>
#include <QAbstractListModel>

struct TaskListData{
    QString taskDescription;
    QString taskID;
};

class TaskListModel;

class TaskList : public QAbstractListModel
{
    Q_OBJECT
    //Q_PROPERTY(TaskListModel *list READ list WRITE setList)
public:
    explicit TaskList(QObject* parent = nullptr);

    enum {
        taskRole
    };
};

class TaskListModel : public QObject
{
    Q_OBJECT
public:
    explicit TaskListModel(QObject* parent = nullptr);
};
