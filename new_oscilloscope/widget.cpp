#include "widget.h"
#include <QCoreApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <iostream>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_chart(0),
      m_series(0)
{

    horizontalGroupBox = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < NumButtons; ++i) {
        buttons[i] = new QPushButton(tr("Filter %1").arg(i + 1));
        connect(buttons[i], SIGNAL (released()), this, SLOT (handleButton()));
        layout->addWidget(buttons[i]);
    }
    horizontalGroupBox->setLayout(layout);


    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(850, 500);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 10);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Seconds");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setTitleText("mV");
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("ECG Signal");



    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}


void Widget::handleButton()
{
    std::cout << "button pressed!!!" << std::endl;
}
Widget::~Widget()
{

}
