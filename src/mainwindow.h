#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include "thread_xy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent*) override;

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonStop_clicked();
    void draw(QVector<QPair<double, double>> data);

private:
    void setEnableButtons(bool buttonStart, bool buttonStop, bool buttonPause);
    void setImagesForButton(QPushButton* button, QIcon icon);
    Ui::MainWindow *ui;
    ThreadXY* threadXY;
    QScatterSeries *series0;
    QValueAxis *axis_y = new QValueAxis();
    QValueAxis *axis_x = new QValueAxis();
    QVector<QValueAxis*> vAxis{axis_y, axis_x};
    QChartView *chartView;
};
#endif // MAINWINDOW_H
