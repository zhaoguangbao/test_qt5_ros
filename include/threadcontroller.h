#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QMutex>


/**
* @class thread_obj_interface
* @brief thread_obj接口，为使用QThread提供的一个简单接口
* @author zhaoguangbao
*/
//typedef void (*thread_func_ptr)();
class thread_obj_interface : public QObject
{
    Q_OBJECT
public:
    thread_obj_interface(QObject* parent = nullptr);
    virtual ~thread_obj_interface(){}
signals:
    void finished_thread_work();

public slots:
    void thread_work();
public:
    /** @brief 需要在线程中执行的耗时操作 */
    virtual void work_func()=0;
};


/**
* @class ThreadController
* @brief 实现QThread与worker类的代理1
* @note 需要调用setThreadObj设置thread obj对象。
* 适应情形：thread obj对象不需要在新线程结束时自动删除，
* 由于在多线程编程中，在任一线程中调用delete均可能会导致程序崩溃，
* 所以，一般该类的使用情形为（设thread_obj为thread_obj_interface的一个子类）：
*   thread_obj threadObj;//分配在栈上，不会引起内存泄漏
*   ThreadController* thread_controller_ptr=new ThreadController(this);//this指定父对象，使得该对象会被自动回收
*   thread_controller_ptr->setThreadObj(&threadObj);
*   ...
* @author zhaoguangbao
*/
class ThreadController : public QObject
{
    Q_OBJECT
public:
    explicit ThreadController(QObject *parent = nullptr);
    ~ThreadController();
public:
    void setThreadObj(thread_obj_interface* thread_obj_ptr);
signals:
    void signalStartThreadWork();
    void signalFinishThreadWork();
public slots:
    void start();
    void start(bool flag);
private:
    void startThreadWork();
    void initConnect();
private:
    QThread* m_threadPtr;
    thread_obj_interface* m_threadObjPtr;
    bool m_bNewThreadObj;
};

//实现QThread与worker类的代理2
//适应情形：thread obj对象需要在新线程结束时自动删除
/*class ThreadCotrollerDel : public QObject
{
};*/

#endif // THREADCONTROLLER_H

