#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <ros/ros.h>
#include "include/qnode.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void initThread();
    void initConnect();

signals:
    void signalStartRunPlanner(bool);

private slots:
    void on_verticalSlider_valueChanged(int value);
    void finishRunSlot();

private:
    Ui::Widget *ui;
    //多线程规划计算
    QNode qnode;
    ThreadController* plannerThreadController_ptr;
};

#endif // WIDGET_H
