#include "widget.h"
QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    m_filter_list = new QListWidget(this);
    QListWidgetItem *item = new QListWidgetItem(m_filter_list);
    QListWidgetItem *item2 = new QListWidgetItem(m_filter_list);

    m_filter_list->addItem(item);
    m_filter_list->addItem(item2);

    filterGui *filt  = new filterGui(this, LP, 20, 0, 4);
    filterGui *filt2  = new filterGui(this, BP, 20, 100, 4);

    item->setSizeHint(filt->sizeHint());
    item2->setSizeHint(filt2->sizeHint());

    m_filter_list->setItemWidget(item, filt);
    m_filter_list->setItemWidget(item2, filt2);

    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(850, 500);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 8000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Seconds");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("mV");
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("ECG Signal");


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(chartView);
    mainLayout->addWidget(m_filter_list);
    this->setLayout(mainLayout);
    this->resize(mainLayout->sizeHint());
    this->show();

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);
    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly);
    m_audioInput->start(m_device);
}


//void Widget::handleButton()
//{
//    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
//    QString buttonText = buttonSender->text();
//    std::cout << "button " << buttonText.toStdString() << " pressed!" << std::endl;
//}

void Widget::valueChanged (int k) {
    std::cout << k << std::endl;
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
}



