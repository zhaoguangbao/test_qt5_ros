#include "include/widget.h"
#include <QApplication>
#include <QDebug>
#include <QThread>

//从bash里面启动qtcreator，所以qt的环境变量里面有ros的变量环境

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"main id: "<<QThread::currentThreadId();
    Widget w;
    w.show();

    return a.exec();
}
