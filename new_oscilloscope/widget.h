#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QtCharts/QChartGlobal>


QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE

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
   QGroupBox *horizontalGroupBox;
   QPushButton *buttons[NumButtons];
   XYSeriesIODevice *m_device;
   QChart *m_chart;
   QLineSeries *m_series;
   QAudioInput *m_audioInput;

};



#endif // WIDGET_H
