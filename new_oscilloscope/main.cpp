#include "widget.h"
#include <QApplication>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include <QtCharts/QValueAxis>


int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   Widget w;
   //w.resize(1250, 600);
   w.show();

   return app.exec();
}
