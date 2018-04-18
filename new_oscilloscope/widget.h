#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QtCharts/QChartGlobal>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <vector>

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
   void valueChanged(int);

private:

   enum { NumButtons = 4 };
   QGroupBox *_horizontalGroupBox;
   QSlider *_filterSlider[NumButtons];
   QLabel *_filterLabel[NumButtons];
   QLabel *_filterFrequency[NumButtons];
   QPushButton *_buttons[NumButtons];
   XYSeriesIODevice *_m_device;
   QChart *_m_chart;
   QLineSeries *_m_series;
   QAudioInput *_m_audioInput;

};



#endif // WIDGET_H
