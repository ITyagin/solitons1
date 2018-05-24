#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

//включаем необходимые компоненты для работы графиков
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QlineSeries>
#include <QScatterSeries>

#include <QDialog>
#include <QWidget>
#include <QDebug>

#include <QString>

#include "advqchart.h"

class QPushButton;

class GraphWindow : public QWidget
{
    Q_OBJECT
public:

    //конструктор
    explicit GraphWindow(QWidget *parent = 0);

    QtCharts::QChart *m_chart;
    advqchart *m_chartView;

    QtCharts::QLineSeries *m_series;
    QtCharts::QScatterSeries *m_seriesS;

    void createSeries();

public slots:
    void add_mousePoint(const QPoint &);
    void addPointBetweenTwo(const QPoint &);
    void enterDeleteMode();

    void evolution_v1_handler();
    void evolution_v2_handler();
    void Calculate_v1_handler();
    void Calculate_v2_handler();

public:
    QPushButton *closeButton;
    QPushButton *addButton;
    QPushButton *updateButton;
    QPushButton *deleteModeButton;

    QPushButton *evolution_v1;
    QPushButton *evolution_v2;
    QPushButton *Calculate_v1;
    QPushButton *Calculate_v2;

    bool evolution_v1_flagStart;
    bool evolution_v2_flagStart;

    bool del_flag;
    bool isDeleteMode;
    int number;

    QVector <QPointF> mouse;

    QVector <qreal> mouse_x;
    QVector <qreal> mouse_y;

signals:
    void textUpdate(QString);
};

#endif // GRAPHWINDOW_H

