#ifndef ADVQCHART_H
#define ADVQCHART_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QChart>
//#include <QSpinBox>

class advqchart : public QtCharts::QChartView
{
    Q_OBJECT
signals:
    void mousePressed (const QPoint &p);
    void mouseMoved(const QPoint &m);
    void mouseReleased(const QPoint &r);
public:
    //advqchart(QGraphicsView *parent =0);
    advqchart(QtCharts::QChart *);
public slots:
    void add_point();

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *releaseEvent);

    void mouseMoveEvent(QMouseEvent *moveEvent);
};

#endif // ADVQCHART_H
