#include <left_plotter.h>

#include <QDebug>

left_plotter::left_plotter(QWidget *parent)
    :QWidget(parent)
{
    flag=0;
    startButton = new QPushButton("start");
    stopButton = new QPushButton("stop");

    m_timer = new QTimer(this);

    leftChart = new QtCharts::QChart();
    leftChartView = new QtCharts::QChartView(leftChart);

    connect(startButton, SIGNAL(clicked()),
            this, SLOT(start()));
    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(stop()));

    connect(m_timer, SIGNAL(timeout()),
            this, SLOT(handleTimeout()));
    m_timer->setInterval(500);
    m_timer->start();

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addSpacing(300);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(stopButton);

    QVBoxLayout *centralLayout=new QVBoxLayout;
    centralLayout->addWidget(leftChartView);
    centralLayout->addLayout(buttonsLayout);

    setLayout(centralLayout);

    createLeftSeries();
}

void left_plotter::createLeftSeries()
{
    leftSeries = new QtCharts::QSplineSeries();

//    leftSeries->append(3,3);
//    leftSeries->append(100,200);
//    leftSeries->append(50, 50);

    leftChart->addSeries(leftSeries);
    leftChart->createDefaultAxes();
    leftChart->axisX()->setRange(0,500);
    leftChart->axisY()->setRange(0,100);

    leftChart->setTitle("Динамические солитоны");
    leftChart->legend()->hide();
    leftChart->setAnimationOptions(QChart::AllAnimations);
}

void left_plotter::start()
{
    flag=1;
}

void left_plotter::stop()
{
    flag=0;
}

//эта функция обновляет график с течением времени
void left_plotter::handleTimeout()
{
    if (flag)
    {
        qDebug()<<"handleTimeout called";
        leftSeries->clear();

        for (int k=0; k<20; k++)
        {
            m_x=QRandomGenerator::global()->bounded(500) - 2.5;
            m_y=QRandomGenerator::global()->bounded(100) - 2.5;
            leftSeries->append(m_x, m_y);
        }
    }
}
