#include "widget.h"
#include <QApplication>
#include <QtCharts/QLineSeries>
#include <QtWidgets>
#include <QtCharts/QValueAxis>


int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QWidget window;
   window.resize(1050, 600);
   window.show();
   window.setWindowTitle(
       QApplication::translate("Parent widget", "Oscilloscope"));

   Widget mainWidget(&window);
   mainWidget.showMaximized();

   return app.exec();
}
