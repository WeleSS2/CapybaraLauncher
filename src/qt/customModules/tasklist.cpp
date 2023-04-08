#include "tasklist.h"
#include <QThread>
#include "../../utility/threadsoperations.h"

TaskList::TaskList(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

int TaskList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->getTaskListData()->size();
}

QVariant TaskList::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || !mList)
        return QVariant();

    const TaskListData item = mList->getTaskListData()->at(index.row());
    switch(role)
    {
        case taskDescriptionRole:
        {
            return QVariant(item.taskDescription);
        }
    }

    return QVariant();
}

bool TaskList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList)
        return false;

    TaskListData item = mList->getTaskListData()->at(index.row());
    switch(role)
    {
        case taskDescriptionRole:
        {
            item.taskDescription = value.toString();
            break;
        }
    }
    if(mList->setItemAt(index.row(), item)){
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TaskList::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

TaskListList *TaskList::list() const
{
    return mList;
}

QHash<int, QByteArray> TaskList::roleNames() const
{
    QHash<int, QByteArray> names;
    names[taskDescriptionRole] = "taskDescription";
    return names;
}

void TaskList::setList(TaskListList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &TaskListList::preItemAppened, this, [=](){
            const int index = mList->getTaskListData()->size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &TaskListList::postItemAppened, this, [=](){
            endInsertRows();
        });
        connect(mList, &TaskListList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &TaskListList::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }
    endResetModel();
}

void TaskList::refreshList()
{
    beginResetModel();

    endResetModel();
}

//---------------------------------------------------------------------------
//
//                               Task ListList
//
//---------------------------------------------------------------------------

TaskListList::TaskListList(QObject *parent)
    : QObject(parent)
{

}

bool TaskListList::setItemAt(qint32 index, const TaskListData &item)
{
    if(index < 0 || index >= vTaskListData.size())
        return false;

    const TaskListData &oldItemData = vTaskListData.at(index);

    vTaskListData[index] = item;
    return true;
}

void TaskListList::appendAndRunTask(std::function<void()> task, QString taskId, QString taskDescription)
{
    emit preItemAppened();

    TaskListData item;
    item.taskDescription = taskDescription;
    item.taskID = taskId;
    vTaskListData.append(item);
    emit postItemAppened();

    ThreadsOperations *runner = new ThreadsOperations(task);
    QThread *thread = new QThread();
    runner->moveToThread(thread);

    QObject::connect(thread, &QThread::started, runner, &ThreadsOperations::runFunction);
    QObject::connect(runner, &ThreadsOperations::finished, thread, &QThread::quit);
    QObject::connect(runner, &ThreadsOperations::finished, runner, &ThreadsOperations::deleteLater);
    QObject::connect(thread, &QThread::finished, [=](){
        int counter = 0;
        for(auto &i : vTaskListData)
        {
            if(i.taskID == taskId)
            {
                emit preItemRemoved(counter);
                vTaskListData.removeAt(counter);
                emit postItemRemoved();
                break;
            }
            ++counter;
        }
    });
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void TaskListList::removeTask(qint32 index)
{
    for(int i = 0; i < vTaskListData.size(); ++i)
    {
        emit preItemRemoved(index);

        vTaskListData.removeAt(index);

        emit postItemRemoved();
    }
}
