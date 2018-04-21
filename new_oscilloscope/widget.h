#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QtCharts/QChartGlobal>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
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
   void addFilter();
   void delFilter();
   void changeFilter(QListWidgetItem*);

private:
   void _init_graph();
   void _init_filtersection();
   void _init_audio();

   QGroupBox *newFilterBox;
   QPushButton *m_newFilter;
   QPushButton *m_delFilter;
   QComboBox *m_whichFilter;
   QSpinBox *m_order;
   QSpinBox *m_f1;
   QSpinBox *m_f2;
   QListWidget *m_filter_list;
   XYSeriesIODevice *m_device;

   QChartView *m_chartView;
   QChart *m_chart;
   QLineSeries *m_series;
   QChartView *m_freq_chartView;
   QChart *m_freq_chart;
   QLineSeries *m_freq_series;
   QAudioInput *m_audioInput;

};



#endif // WIDGET_H
