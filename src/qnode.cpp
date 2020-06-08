#include <ros/ros.h>
#include <string>
#include "include/qnode.h"

QNode::QNode()
{
    msg.linear.x = 3.0;
    msg.angular.z = 1.0;
}

QNode::~QNode() {
    if(ros::isStarted()) {
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
}


bool QNode::init() {
    //ros::init(init_argc,init_argv,"test_gui");
    if ( ! ros::master::check() ) {
        std::cout<<"No master started!"<<'\n';
        return false;
    }

    ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle n;
    // Add your ros communications here.
    chatter_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    return true;
}

void QNode::run()
{
    ros::Rate loop_rate(1);
    int count = 0;
    qDebug()<<QThread::currentThreadId();
    while ( ros::ok() ) {

        chatter_publisher.publish(msg);
        log(Info, "vel_x: "+qDebugStr(msg.linear.x).toStdString());
        log(Info, "angular: "+qDebugStr(msg.angular.z).toStdString());

        ros::spinOnce();
        loop_rate.sleep();
        ++count;
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    emit rosShutdown(); // used to signal the gui for a shutdown (useful to r
}


void QNode::log( const LogLevel &level, const std::string &msg) {
    std::stringstream logging_model_msg;
    switch ( level ) {
    case(Debug) : {
        logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Info) : {
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Warn) : {
        logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Error) : {
        logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    case(Fatal) :
        logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
        break;
    }
    std::cout<<logging_model_msg.str()<<'\n';
    emit loggingUpdated(); // used to readjust the scrollbar
}

void QNode::setTwist(double vx, double angular)
{
    msg.linear.x=vx;
    msg.angular.z=angular;
}


