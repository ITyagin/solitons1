#include <QtWidgets>
#include "graphwindow.h"
#include <QDebug>

GraphWindow::GraphWindow(QWidget *parent)
    :QWidget(parent)
{
    //делаем трекинг курсора
    setMouseTracking(true);

    //создаем все к графику

    m_chart = new QtCharts::QChart();
    m_chartView = new advqchart(m_chart);

    //соединяем все имеющиеся слоты и сигналы
    connect(m_chartView, SIGNAL(mousePressed (const QPoint&)),
            this, SLOT(add_mousePoint(const QPoint&)));

    connect(m_chartView, SIGNAL(mouseMoved (const QPoint&)),
            this, SLOT(addPointBetweenTwo(const QPoint&)));

    evolution_v1 = new QPushButton("evolution_v1");
    evolution_v1_flagStart=0;
    evolution_v2 = new QPushButton("evolution_v2");
    evolution_v2_flagStart=0;
    Calculate_v1 = new QPushButton("Calculate_v1");
    Calculate_v2 = new QPushButton("Calculate_v2");

    connect (evolution_v1, SIGNAL(clicked()),
             this, SLOT(evolution_v1_handler()));
    connect (evolution_v2, SIGNAL(clicked()),
             this, SLOT(evolution_v2_handler()));
    connect (Calculate_v1, SIGNAL(clicked()),
             this, SLOT(Calculate_v1_handler()));
    connect (Calculate_v2, SIGNAL(clicked()),
             this, SLOT(Calculate_v2_handler()));

    deleteModeButton = new QPushButton("Enter delete mode");
    deleteModeButton->setMaximumWidth(200);

    connect (deleteModeButton, SIGNAL(clicked()),
             this, SLOT(enterDeleteMode()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_chartView);
    mainLayout->addWidget(deleteModeButton);
    mainLayout->addWidget(evolution_v1);
    mainLayout->addWidget(evolution_v2);
    mainLayout->addWidget(Calculate_v1);
    mainLayout->addWidget(Calculate_v2);

    setLayout(mainLayout);
    setWindowTitle(tr("Grapher"));

    createSeries();

    isDeleteMode=0;

    //флаг на запуск добавителя точки между
    del_flag=0;

    //здесь будем хранить временные данные, чтобы ограничить перемещения курсора
    number=0;

    mouse_x.append(-1);
    mouse_y.append(0);
    mouse_x.append(1);
    mouse_y.append(1);
}

void GraphWindow::createSeries()
{
    //m_series = new QtCharts::QLineSeries();
    m_series = new QtCharts::QLineSeries();
    m_seriesS = new QtCharts::QScatterSeries();

//ЗДЕСЬ НАЧАЛЬНЫЕ ДАННЫЕ
    //добавляем начальные точки
    m_series->append(-1,0);
    //m_series->append(0,0.2);
    m_series->append(1,0);

    m_seriesS->append(-1.1, 0);
    m_seriesS->append(0, 0);

    //делаем точки видимыми
    m_series->setPointsVisible(true);

    m_chart->addSeries(m_seriesS);
    m_chart->addSeries(m_series);
    m_chart->setTitle("Вид потенциала");
    m_chart->createDefaultAxes();
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    m_chart->axisY()->setRange(-1,1);
    m_chart->axisX()->setRange(-1.2,1.2);
}

//добавляет точку с координатами курсора в конец массива
//если координаты курсора попали в окрестность какой-то точки, она удаляется

//void GraphWindow::add_mousePoint(const QPoint &p)
//{
//    if (m_chart->mapToValue(p).x()<1 && m_chart->mapToValue(p).x()>-1)
//    {double dx = 0.05;
//    double dy = 0.05;
//    bool flag=0;
//    qDebug() <<" number of points: "<<m_series->count();
//    for (int i=0; i<m_series->count(); i++)
//    {
//        qreal x = m_series->points()[i].x();
//        qreal y = m_series->points()[i].y();
//        //проверяем, попадает ли новая точка с координатами курсора в какую-то из
//        //уже имеющихся точек
//        if (x-dx < m_chart->mapToValue(p).x() && m_chart->mapToValue(p).x() < x+dx
//                && y-dy < m_chart->mapToValue(p).y() && m_chart->mapToValue(p).y() < y+dy)
//        {
//             qDebug() <<"point" << m_chart->mapToValue(p) << "is in eps-circle of ";
//             qDebug() <<" x = "<< x <<", y = " << y<<"\n";
//             flag=1;

//             if (x!=1 && x!=-1)
//             {
//                 m_series->remove(x,y);
//                 emit textUpdate("point deleted: x = "+QString::number(x)+", y = "+QString::number(y));
//                 return;
//             }
//        }
//    }
//    if (!flag)
//    {
//        m_series->append(m_chart->mapToValue(p));
//        emit textUpdate("point added");
//    }}
//}

void GraphWindow::addPointBetweenTwo(const QPoint &m)
{
    if (del_flag)
    {
        qDebug()<<"func addPointBetweenTwo called. m = "<<m_chart->mapToValue(m);
        //m_series->insert(number, m_chart->mapToValue(m));
        //m_series->remove(number-1);
    }
}

void GraphWindow::add_mousePoint(const QPoint &p)
{
    qreal X,Y;
    X=m_chart->mapToValue(p).x();
    Y=m_chart->mapToValue(p).x();
    if (-1 < X && X < 1
            && !isDeleteMode)
    {
        double dx=0.05;

        int i=0;
        while (mouse_x[i]+dx<X && i<=mouse_x.length())
        {
            i++;
        }
        if(i)
        {
            i--;
        }
        emit textUpdate("i = "+QString::number(i));

        if (mouse_x[i]-dx < X && X < mouse_x[i]+dx && i)
        {
            mouse_y[i]=Y;

            //mouse_y[i]=m_chart->mapToValue(p).y();
            //mouse_y.replace(i, m_chart->mapToValue(p).y());
            //m_series->points()[i].y() = m_chart->mapToValue(p).y();
            m_series->points().replace(i, m_chart->mapToValue(p));
            emit textUpdate("\nyou are too close!\nyour x = "+QString::number(m_chart->mapToValue(p).x())+"\npoint x = "+QString::number(mouse_x[i]));
        }

        else if (i<mouse_x.length())
        {
            mouse_x.insert(i+1, X);
            mouse_y.insert(i+1, Y);

            m_series->insert(i+1, m_chart->mapToValue(p));
            emit textUpdate("new point added to mouse vector");
        }
        qDebug()<<"x: "<<mouse_x<<"y: "<<mouse_y;}

    if (-1 < m_chart->mapToValue(p).x() && m_chart->mapToValue(p).x() < 1
            && isDeleteMode)
    {
        double dx=0.05;
        double dy=0.05;
        for (int i=0; i<m_series->count(); i++)
        {
                qreal x = m_series->points()[i].x();
                qreal y = m_series->points()[i].y();
                //проверяем, попадает ли новая точка с координатами курсора в какую-то из
                //уже имеющихся точек
                if (x-dx < m_chart->mapToValue(p).x() && m_chart->mapToValue(p).x() < x+dx
                        && y-dy < m_chart->mapToValue(p).y() && m_chart->mapToValue(p).y() < y+dy)
                {
                     qDebug() <<"point" << m_chart->mapToValue(p) << "is in eps-circle of ";
                     qDebug() <<" x = "<< x <<", y = " << y<<"\n";

                     if (x!=1 && x!=-1)
                     {
                         m_series->remove(x,y);
                         mouse_x.remove(i);
                         mouse_y.remove(i);
                         emit textUpdate("point deleted: x = "+QString::number(x)+", y = "+QString::number(y));
                         return;
                     }
                }
        }
        emit textUpdate("clicked in delete mode");
    }
}

void GraphWindow::enterDeleteMode()
{
    if (isDeleteMode)
    {
        isDeleteMode=0;
        deleteModeButton->setText("Enter delete mode");
    }
    else
    {
        isDeleteMode=1;
        deleteModeButton->setText("Exit delete mode");
    }
}

void GraphWindow::evolution_v1_handler()
{
    if (evolution_v1_flagStart)
    {
        evolution_v1_flagStart=0;
        evolution_v1->setText("Evo 1 unSTARTED");
        //...если кнопка отжимается (из 1 в 0)
    }
    else
    {
        evolution_v1_flagStart=1;
        evolution_v1->setText("Evo 1 STARTED");
        //...если кнопка зажимается (из 0 в 1)
    }
}

void GraphWindow::evolution_v2_handler()
{
    if (evolution_v2_flagStart)
    {
        evolution_v2_flagStart=0;
        evolution_v2->setText("Evo 1 unSTARTED");
        //...если кнопка отжимается (из 1 в 0)
    }
    else
    {
        evolution_v2_flagStart=1;
        evolution_v2->setText("Evo 1 STARTED");
        //...если кнопка зажимается (из 0 в 1)
    }
}

void GraphWindow::Calculate_v1_handler()
{

}

void GraphWindow::Calculate_v2_handler()
{

}
