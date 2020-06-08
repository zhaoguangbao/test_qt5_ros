#include <QDebug>
#include "include/threadcontroller.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


//* ------------ class thread_obj_interface begin------------*//
thread_obj_interface::thread_obj_interface(QObject *parent):QObject (parent)
{

}

void thread_obj_interface::thread_work()
{
#ifdef DEBUG_OUT
    qDebug()<<QThread::currentThreadId();
#endif
    this->work_func();
    emit finished_thread_work();
}
//* ------------ class thread_obj_interface end------------*//





//* ------------ class ThreadController begin------------*//
ThreadController::ThreadController(QObject *parent) : QObject(parent)
{
    m_threadPtr=nullptr;
    m_threadObjPtr=nullptr;
    m_bNewThreadObj=false;
}

ThreadController::~ThreadController()
{
    /*if(m_threadPtr)
    {
        m_threadPtr->quit();
        m_threadPtr->wait();
    }*/
}
/** @brief 设置继承thread_obj_interface的子类，作为新线程中的工作类 */
void ThreadController::setThreadObj(thread_obj_interface *thread_obj_ptr)
{
    m_threadObjPtr=thread_obj_ptr;
    m_bNewThreadObj=true;
}
/** @brief 主线程通过信号换起子线程的槽函数 */
void ThreadController::start()
{
    startThreadWork();
    emit signalStartThreadWork();
}

void ThreadController::start(bool flag)
{
    if(flag)
    {
        startThreadWork();
        emit signalStartThreadWork();
    }
    else {
        qDebug()<<"new thread flag is false";
    }
}


void ThreadController::startThreadWork()
{
    if(m_threadPtr)
        return;
    if(m_threadObjPtr==nullptr)
    {
        qDebug()<<"warning: thread obj is null, please call setThreadObj() firstly.";
        return;
    }
    m_threadPtr= new QThread();
    m_threadObjPtr->moveToThread(m_threadPtr);
    initConnect();
    m_threadPtr->start();
}

void ThreadController::initConnect()
{
    connect(m_threadPtr,&QThread::finished,m_threadPtr,&QObject::deleteLater);
    if(m_bNewThreadObj)
    {
        connect(this,&ThreadController::signalStartThreadWork,m_threadObjPtr,&thread_obj_interface::thread_work);
        connect(m_threadObjPtr,&thread_obj_interface::finished_thread_work,this,&ThreadController::signalFinishThreadWork);
        m_bNewThreadObj=false;
    }
}
//* ------------ class ThreadCotroller end------------*//


