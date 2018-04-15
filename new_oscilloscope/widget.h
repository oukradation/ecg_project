#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QtCharts/QChartGlobal>


QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

namespace Ui {
   class Widget;
}

class Widget : public QWidget
{
   Q_OBJECT
public:
   Widget(QWidget *parent = 0);
    ~Widget();

private slots:
   void handleButton();
private:

   enum { NumButtons = 4 };

   QPushButton *a_button;
   QPushButton *b_button;
   QPushButton *c_button;
   QPushButton *d_button;
   QPushButton *e_button;
   QGroupBox *horizontalGroupBox;
   QPushButton *buttons[NumButtons];
   QChart *m_chart;
   QLineSeries *m_series;

};



#endif // WIDGET_H
