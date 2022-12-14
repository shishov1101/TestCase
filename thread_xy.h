#ifndef THREAD_XY_H
#define THREAD_XY_H

#include <QThread>
#include <QPair>
#include <QVector>

#define MAX_POINTS 30
#define MIN_POINTS 1
#define MAX_VALUE 100.0
#define MIN_VALUE -100.0
#define TIME_SLEEP 500 //msecs
#define TICK_COUNT 11

class ThreadXY : public QThread
{
    Q_OBJECT
public:
    explicit ThreadXY(QString threadName);
    void run() override;
    void setFlag(bool flag);

signals:
    void sendXY(QVector<QPair<double, double>> data);

private:
    int randInt(int low, int high);
    double randDouble(double low, double high);
    QString name;
    QVector<QPair<double, double>> valuesXY;
    std::atomic<bool> stopThread;
};

#endif // THREAD_XY_H
