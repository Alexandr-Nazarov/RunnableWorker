#include <QDebug>
#include <QThread>
#include "worker.h"

#define TIMEOUT 1000000000

int wk::COUNT = 40;
int const wk::YSTART = 100;

//-------------------------------------------------------------------
//
Worker::Worker(int *x, int y, QColor clr, QObject *parent, int count):
    QObject(parent),
    x_(x),
    y_(y),
    color_(clr),
    count_(count)
{

}

//-------------------------------------------------------------------
//
void Worker::doWork()
{
    for (int i = 0; i < count_; ++i)
    {
        MyPoint point(QPoint(*x_, y_), color_);
        emit signalAddPoint(point);
        ++(*x_);
        for (long long j = 0; j < TIMEOUT; ++j)  //имитация работы, чтобы поток не исключался из планирования (если делать sleep())
        {
            int tmp;
            tmp++;
        }
      //  qDebug() << point.point() << QThread::currentThreadId();
    }
}

//-------------------------------------------------------------------
//
