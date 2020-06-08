#include "include/widget.h"
#include "ui_widget.h"
#include <std_msgs/String.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    int argc = 0; char **argv = nullptr;
    ros::init(argc, argv, "client_plug");
    qnode.init();

    initThread();
    initConnect();
}

Widget::~Widget()
{
    delete ui;
}

//private
void Widget::initThread()
{
    //QThread数据初始化
    plannerThreadController_ptr=new ThreadController(this);
    plannerThreadController_ptr->setThreadObj(&qnode);
}

void Widget::initConnect()
{
    //采用SIGNAL-SLOT的形式，在新线程中调用qnode.run进行规划计算
    connect(this,SIGNAL(signalStartRunPlanner(bool)),plannerThreadController_ptr,SLOT(start(bool)));
    //connect(plannerThreadController_ptr,&ThreadController::signalFinishThreadWork,this,&Widget::finishRunSlot);
    signalStartRunPlanner(true);
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    ui->lineEdit->setText(QString("%1").arg(value));
    qnode.setTwist(value/100.0,1.0);
}

void Widget::finishRunSlot()
{

}
