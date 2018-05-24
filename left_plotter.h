#ifndef LEFT_PLOTTER_H
#define LEFT_PLOTTER_H

#include <QtCharts>
#include <QWidget>
#include <QtCore/QTimer>

class left_plotter : public QWidget
{
    Q_OBJECT
public:
    bool flag;
    left_plotter(QWidget *parent =0);

    QtCharts::QChart *leftChart;
    QtCharts::QChartView *leftChartView;
    QtCharts::QSplineSeries *leftSeries;

    QPushButton *startButton;
    QPushButton *stopButton;

    void createLeftSeries();
public slots:
    void start();
    void stop();
    void handleTimeout();
public:
    QTimer *m_timer;
    qreal m_x;
    qreal m_y;
};

#endif // LEFT_PLOTTER_H
