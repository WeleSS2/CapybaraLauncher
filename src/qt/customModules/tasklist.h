#pragma once

#include <QObject>
#include <QAbstractListModel>

struct TaskListData{
    QString taskDescription;
    QString taskID;
};

class TaskListList;

class TaskList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TaskListList *list READ list WRITE setList)
public:
    explicit TaskList(QObject* parent = nullptr);

    enum {
        taskDescriptionRole,
        taskIdRole
    };

    int rowCount (const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    TaskListList *list() const;
    void setList(TaskListList *list);

    Q_INVOKABLE void refreshList();

private:
    TaskListList *mList;
};


//---------------------------------------------------------------
//
//                  List for model
//
//--------------------------------------------------------------

class TaskListList : public QObject
{
    Q_OBJECT
public:
    explicit TaskListList(QObject* parent = nullptr);

    const QVector<TaskListData> *getTaskListData(){return &vTaskListData; };

    bool setItemAt(qint32 index, const TaskListData &item);

signals:
    void preItemAppened();
    void postItemAppened();

    void preItemRemoved(qint32 index);
    void postItemRemoved();

public slots:
    void appendAndRunTask(std::function<void()> task, QString taskId, QString taskDescription);
    void removeTask(qint32 index);

    uint64_t getListSize(){return vTaskListData.size(); };

private:
    QVector<TaskListData> vTaskListData;
};
