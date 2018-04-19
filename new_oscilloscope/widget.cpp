#include "widget.h"
#include "xyseriesiodevice.h"

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <iostream>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      _m_device(0),
      _m_chart(0),
      _m_series(0),
      _m_audioInput(0)
{

    _horizontalGroupBox = new QGroupBox;
    QVBoxLayout *verticalFilterLayout = new QVBoxLayout;
    std::vector<string> names = {"Notch","Band pass","Low pass","High pass"};
    for (int i = 0; i < NumButtons; ++i) {
        _buttons[i] = new QPushButton(tr(names[i].c_str()));
        connect(_buttons[i], SIGNAL (released()), this, SLOT (handleButton()));
        QVBoxLayout *verticalFilterInstance = new QVBoxLayout;
        verticalFilterInstance->addWidget(_buttons[i]);

        _filterLabel[i] = new QLabel(tr("Frequency"));
        _filterSlider[i] = new QSlider(Qt::Horizontal);
        connect(_filterSlider[i], SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        _filterSlider[i]->setRange(0,100);
        _filterSlider[i]->setTickPosition(QSlider::TicksBothSides);
        _filterSlider[i]->setTickInterval(10);
        _filterSlider[i]->setSingleStep(1);
        verticalFilterInstance->addWidget(_filterLabel[i]);
        QHBoxLayout *horizontalSliderLayout = new QHBoxLayout;
        horizontalSliderLayout->addWidget(_filterSlider[i]);
        _filterFrequency[i] = new QLabel(this);
        connect(_filterSlider[i], SIGNAL(valueChanged(int)), _filterFrequency[i], SLOT(setNum(int)));

        _filterFrequency[i]->setText("0");
        horizontalSliderLayout->addWidget(_filterFrequency[i]);
        verticalFilterInstance->addLayout(horizontalSliderLayout);
        verticalFilterLayout->addLayout(verticalFilterInstance);
    }

    _horizontalGroupBox->setLayout(verticalFilterLayout);

    _m_chart = new QChart;
    QChartView *chartView = new QChartView(_m_chart);
    chartView->setMinimumSize(850, 500);
    _m_series = new QLineSeries;
    _m_chart->addSeries(_m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 10);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Seconds");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setTitleText("mV");
    _m_chart->setAxisX(axisX, _m_series);
    _m_chart->setAxisY(axisY, _m_series);
    _m_chart->legend()->hide();
    _m_chart->setTitle("ECG Signal");


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(_horizontalGroupBox);
    setLayout(mainLayout);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    _m_audioInput = new QAudioInput(inputDevices,formatAudio, this);
    _m_device = new XYSeriesIODevice(_m_series, this);
    _m_device->open(QIODevice::WriteOnly);
    _m_audioInput->start(_m_device);
}


void Widget::handleButton()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    QString buttonText = buttonSender->text();
    std::cout << "button " << buttonText.toStdString() << " pressed!" << std::endl;
}

void Widget::valueChanged (int k) {
    std::cout << k << std::endl;
}

Widget::~Widget()
{
    _m_audioInput->stop();
    _m_device->close();
}



