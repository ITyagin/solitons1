#include "advqchart.h"
#include <QDebug>
#include <QtWidgets>

advqchart::advqchart(QtCharts::QChart *parent) : QtCharts::QChartView(parent)
{
    setMouseTracking(true);
}

void advqchart::add_point()
{

}

void advqchart::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    emit mouseReleased(releaseEvent->pos());
}

void advqchart::mousePressEvent(QMouseEvent *event)
{
    const QPoint p = event->pos();
    emit mousePressed(p);
}

//отслеживаем координаты двигающейся точки
void advqchart::mouseMoveEvent(QMouseEvent *moveEvent)
{
    const QPoint m = moveEvent->pos();
    emit mouseMoved(m);
}
