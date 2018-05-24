#include "graphwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QSplitterHandle>

#include <left_plotter.h>

#include <QTextEdit>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GraphWindow *dialog = new GraphWindow;
    left_plotter *leftP = new left_plotter;

    QTextEdit *console = new QTextEdit;
    console->setReadOnly(true);
    for (int q=0;q<3;q++)
    {console->append("Grapher started");}

    QObject::connect(dialog, SIGNAL(textUpdate(QString)),
                     console, SLOT(append(QString)));

    QSplitter *splitterVer = new QSplitter(Qt::Vertical);
    splitterVer->addWidget(leftP);
    splitterVer->addWidget(console);
    QList <int> VerticalSizes;
    VerticalSizes.append(400);
    VerticalSizes.append(200);
    splitterVer->setSizes(VerticalSizes);

    QSplitter splitterHor(Qt::Horizontal);
    splitterHor.addWidget(splitterVer);
    splitterHor.addWidget(dialog);
    QList <int> HorizontalSizes;
    HorizontalSizes.append(300);
    HorizontalSizes.append(500);

    splitterHor.setSizes(HorizontalSizes);

    //делаем разделитель видимым
    app.setStyleSheet("QSplitter::handle { background-color: gray }");

    splitterHor.resize(900,600);
    splitterHor.show();

    return app.exec();
}
