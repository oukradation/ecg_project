#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QtCharts/QChartGlobal>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QListWidgetItem>
#include <QListWidget>

#include <vector>
#include <iostream>

#include "xyseriesiodevice.h"
#include "filtergui.h"

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
   void valueChanged(int);

private:

   QListWidget *m_filter_list;
   XYSeriesIODevice *m_device;
   QChart *m_chart;
   QLineSeries *m_series;
   QAudioInput *m_audioInput;

};



#endif // WIDGET_H
