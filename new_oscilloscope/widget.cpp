#include "widget.h"
QT_CHARTS_USE_NAMESPACE

#define SAMPLE_FREQ 8000

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    // graph section
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
    m_inputVolume = new QSlider();
    m_inputVolume->setRange(0,100);
    m_inputVolume->setValue(20);
    connect(m_inputVolume, SIGNAL(valueChanged(int)),
            this, SLOT(changeVolume(int)));


    QHBoxLayout *graphLayout = new QHBoxLayout();
    graphLayout->addWidget(chartView);
    graphLayout->addWidget(m_inputVolume);


    // filter section
    QHBoxLayout *newFilterLayout = new QHBoxLayout();
    m_newFilter = new QPushButton(tr("Add filter"), this);
    connect(m_newFilter, SIGNAL(clicked(bool)), this, SLOT(addFilter()));
    m_delFilter = new QPushButton(tr("delete"),this);
    connect(m_delFilter, SIGNAL(clicked(bool)), this, SLOT(delFilter()));
    m_whichFilter = new QComboBox(this);
    for ( auto&& filt : filterGui::filter_names )
        m_whichFilter->addItem(QString(filt));
    m_order = new QSpinBox();
    m_order->setSingleStep(1);
    m_order->setRange(1,16);
    m_f1 = new QSpinBox();
    m_f1->setSingleStep(1);
    m_f1->setRange(1, 400);
    m_f2 = new QSpinBox();
    m_f2->setSingleStep(1);
    m_f2->setRange(1, 400);
    newFilterLayout->addWidget(m_newFilter);
    newFilterLayout->addWidget(m_whichFilter);
    newFilterLayout->addWidget(m_order);
    newFilterLayout->addWidget(m_f1);
    newFilterLayout->addWidget(m_f2);

    m_filter_list = new QListWidget(this);

    QVBoxLayout *filterBoxLayout = new QVBoxLayout();
    filterBoxLayout->addLayout(newFilterLayout);
    filterBoxLayout->addWidget(m_filter_list);
    filterBoxLayout->addWidget(m_delFilter);

    // main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(graphLayout);
    mainLayout->addLayout(filterBoxLayout);
    this->setLayout(mainLayout);
    this->resize(mainLayout->sizeHint());
    this->show();

    // audio setup
    QAudioFormat formatAudio;
    formatAudio.setSampleRate(SAMPLE_FREQ);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    // init audio device
    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);
    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly);
    m_audioInput->start(m_device);

    connect(m_filter_list, SIGNAL(currentRowChanged(int)),
            m_device->sig, SLOT(changeAttr(int)));
}

void Widget::addFilter()
{
    // add gui on the list
    QListWidgetItem *item = new QListWidgetItem(m_filter_list);
    m_filter_list->addItem(item);
    filterGui *filt  = new filterGui(this, (filterType)m_whichFilter->currentIndex(),
                                     m_f1->value(),
                                     m_f2->value(),
                                     m_order->value());
    item->setSizeHint(filt->sizeHint());
    m_filter_list->setItemWidget(item, filt);

    // add filter in signal processing
    m_device->sig->addFilter(filter((filterType)m_whichFilter->currentIndex(),
                                     SAMPLE_FREQ,
                                     m_f1->value(),
                                     m_f2->value(),
                                     m_order->value()));
}

void Widget::delFilter()
{
    // delete filter from signalprocessing
    m_device->sig->removeFilter(m_filter_list->currentIndex().row());

    // delete filterGui from filter list
    delete m_filter_list->currentItem();
}

void Widget::changeVolume(int value)
{
    qreal linearVolume = QAudio::convertVolume( value/qreal(100),
                                                QAudio::LogarithmicVolumeScale,
                                                QAudio::LinearVolumeScale);
    m_audioInput->setVolume(linearVolume);
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
}

