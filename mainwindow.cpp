#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define ICON_SIZE 160
#define MARKER_SIZE 7.0

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qRegisterMetaType<QVector<QPair<double,double>>>("QVector<QPair<double,double>>");
    this->setStyleSheet("QMainWindow {background: 'white';}");
    ui->setupUi(this);
    setImagesForButton(ui->pushButtonStart, QIcon("://icons/icon-start.png"));
    setImagesForButton(ui->pushButtonPause, QIcon("://icons/icon-pause.png"));
    setImagesForButton(ui->pushButtonStop, QIcon("://icons/icon-stop.png"));
    ui->chartview->setStyleSheet("background: 'white';");
    threadXY = new ThreadXY("Thread XY");
    connect(threadXY, SIGNAL(sendXY(QVector<QPair<double, double>>)), this, SLOT(draw(QVector<QPair<double, double>>)), Qt::QueuedConnection);
    series0 = new QScatterSeries();
    series0->setName("Values (x;y)");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(MARKER_SIZE);
    ui->chartview->chart()->addSeries(series0);
    for(int i = 0; i < vAxis.length(); ++i){
        vAxis[i]->setTitleText(i == 0 ? tr("y") : tr("x"));
        vAxis[i]->setLabelFormat("%g");
        vAxis[i]->setTickCount(TICK_COUNT);
        vAxis[i]->setMin(i == 0 ? MIN_VALUE : MIN_VALUE);
        vAxis[i]->setMax(i == 0 ? MAX_VALUE : MAX_VALUE);
        ui->chartview->chart()->addAxis(vAxis[i], i == 0 ? Qt::AlignLeft : Qt::AlignBottom);
        series0->attachAxis(vAxis[i]);
    }
}

void MainWindow::setImagesForButton(QPushButton* button, QIcon icon)
{
    button->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
    button->setIcon(icon);
    button->setStyleSheet("background: 'white';");
    button->setFixedHeight(button->size().width());
}

MainWindow::~MainWindow()
{
    threadXY->terminate();
    threadXY->wait();
    delete ui;
    delete threadXY;
    delete series0;
    for(auto axe : vAxis) delete axe;
}

void MainWindow::setEnableButtons(bool buttonStart, bool buttonPause, bool buttonStop)
{
    ui->pushButtonStart->setEnabled(buttonStart);
    ui->pushButtonPause->setEnabled(buttonPause);
    ui->pushButtonStop->setEnabled(buttonStop);
}


void MainWindow::on_pushButtonStart_clicked()
{
    threadXY->setFlag(false);
    threadXY->start();
    ui->statusbar->showMessage("Start button pressed");
    setEnableButtons(false, true, true);
}

void MainWindow::on_pushButtonPause_clicked()
{
    threadXY->setFlag(true);
    ui->statusbar->showMessage("Pause button pressed");
    setEnableButtons(true, false, true);
}

void MainWindow::on_pushButtonStop_clicked()
{
    threadXY->setFlag(true);
    threadXY->terminate();
    threadXY->wait();
    series0->clear();
    ui->statusbar->showMessage("Stop button pressed");
    setEnableButtons(true, false, false);
}

void MainWindow::draw(QVector<QPair<double, double>> data)
{
    for(auto at : data) series0->append(at.first, at.second);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    ui->pushButtonStart->setFixedHeight(ui->pushButtonStart->size().width());
    ui->pushButtonPause->setFixedHeight(ui->pushButtonPause->size().width());
    ui->pushButtonStop->setFixedHeight(ui->pushButtonStop->size().width());
}
