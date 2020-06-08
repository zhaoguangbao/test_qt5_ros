#ifndef QNODE_H
#define QNODE_H

#include <ros/ros.h>
#include "threadcontroller.h"
#include <QDebug>
#include <geometry_msgs/Twist.h>


template <typename F> QString qDebugStr(F& f){
    QString ret;
    QDebug(&ret) << f;
    return ret;
}

class QNode: public thread_obj_interface
{
    Q_OBJECT
public:
    void setTwist(double vx, double angular);
public:
    QNode();
    ~QNode();

    bool init();

    void run();
    /*********************
    ** Logging
    **********************/
    enum LogLevel {
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    void log( const LogLevel &level, const std::string &msg);

signals:
    void loggingUpdated();
    void rosShutdown();
public:
    void work_func()
    {
        run();
    }

private:
    //int init_argc;
    //char** init_argv;
    ros::Publisher chatter_publisher;
    geometry_msgs::Twist msg;
};





#endif
