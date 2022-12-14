#include "thread_xy.h"
#include <QTime>

ThreadXY::ThreadXY(QString threadName) : name(threadName) { }

int ThreadXY::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

double ThreadXY::randDouble(double low, double high)
{
    return (double)(rand()) / RAND_MAX * (high - low) + low;
}

void ThreadXY::run()
{
    for(;;)
    {
        if(!stopThread)
        {
            QTime time = QTime::currentTime();
            qsrand(static_cast<uint>(time.msec()));
            auto sizeValue = randInt(MIN_POINTS, MAX_POINTS);
            for(int i = 0; i < sizeValue; ++i) valuesXY.append(QPair<double, double>(randDouble(MIN_VALUE, MAX_VALUE), randDouble(MIN_VALUE, MAX_VALUE)));
            emit sendXY(valuesXY);
            valuesXY.clear();
        }
        QThread::msleep(TIME_SLEEP);
    }
}

void ThreadXY::setFlag(bool flag)
{
    this->stopThread = flag;
}
