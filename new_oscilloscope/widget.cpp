#include "widget.h"
QT_CHARTS_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    _init_graph();
    _init_filtersection();
    _init_audio();
    _init_recordBox();

    QVBoxLayout *graphLayout = new QVBoxLayout();
    graphLayout->addWidget(m_chartView);
    graphLayout->addWidget(m_freq_chartView);

    // filter section
    QVBoxLayout *filterBoxLayout = new QVBoxLayout();
    filterBoxLayout->addWidget(m_newFilterBox);
    filterBoxLayout->addWidget(m_filter_list);
    filterBoxLayout->addWidget(m_delFilter);
    filterBoxLayout->addWidget(m_recordBox);

    // main layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(graphLayout);
    mainLayout->addLayout(filterBoxLayout);
    this->setLayout(mainLayout);
    this->resize(mainLayout->sizeHint());
    this->show();

    connect(m_filter_list, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(changeFilter(QListWidgetItem*)));
}

void Widget::addFilter()
{
    int f1, f2 = 0;
    filterType type = (filterType)m_whichFilter->currentIndex();
    f1 = m_f1->value();
    f2 = m_f2->value();

    // add filter in signal processing
    filter fit;
    try
    {
        fit = filter(type,
                     SAMPLE_FREQ,
                     f1,
                     f2,
                     m_order->value());
    }
    catch (exception& e)
    {
        std::cout << "error making filter" << std::endl;
        return;
    }

    m_device->getSig()->addFilter(fit);


    // add gui on the list
    QListWidgetItem *item = new QListWidgetItem(m_filter_list);
    m_filter_list->addItem(item);
    filterGui *filt  = new filterGui(this, type,
                                     f1,
                                     f2,
                                     m_order->value());
    item->setSizeHint(filt->sizeHint());
    m_filter_list->setItemWidget(item, filt);

}

void Widget::delFilter()
{
    // delete filter from signalprocessing
    m_device->getSig()->removeFilter(m_filter_list->currentIndex().row());

    // delete filterGui from filter list
    delete m_filter_list->currentItem();
}

void Widget::changeFilter(QListWidgetItem *item)
{
    // get values
    filterGui *filtGui = (filterGui*)m_filter_list->itemWidget(item);
    int f1, f2 = 0;
    f1 = filtGui->_filterSlider_lower->value();
    if (filtGui->getType() == BS || filtGui->getType() == BP )
        f2 = filtGui->_filterSlider_upper->value();

    // change filter
    m_device->getSig()->changeAttr(m_filter_list->row(item),
                              f1, f2, filtGui->getButtonState());
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();
}

void Widget::_init_graph()
{
    // signal section
    m_chart = new QChart;
    m_chartView = new QChartView(m_chart);
    m_chartView->setMinimumSize(1200, 250);
    m_series = new QLineSeries;
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, SAMPLE_FREQ);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Number of samples");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();
    m_chart->setTitle("ECG Signal");

    // spectrogram section
    m_freq_chart = new QChart;
    m_freq_chartView = new QChartView(m_freq_chart);
    m_freq_chartView->setMinimumSize(1200,250);
    m_freq_series = new QLineSeries;
    m_freq_chart->addSeries(m_freq_series);
    QValueAxis *freq_axisX = new QValueAxis;
    freq_axisX->setRange(0, SAMPLE_FREQ/2);
    freq_axisX->setLabelFormat("%g");
    freq_axisX->setTitleText("Hz");
    QValueAxis *freq_axisY = new QValueAxis;
    freq_axisY->setRange(-70,40);
    m_freq_chart->setAxisX(freq_axisX, m_freq_series);
    m_freq_chart->setAxisY(freq_axisY, m_freq_series);
    m_freq_chart->legend()->hide();
    m_freq_chart->setTitle("Frequency Spectrum");
}

void Widget::_init_filtersection()
{
    m_newFilter = new QPushButton(tr("Add filter"), this);
    connect(m_newFilter, SIGNAL(clicked(bool)), this, SLOT(addFilter()));
    m_delFilter = new QPushButton(tr("delete"),this);
    connect(m_delFilter, SIGNAL(clicked(bool)), this, SLOT(delFilter()));
    m_whichFilter = new QComboBox(this);
    for ( auto&& filt : filterGui::filter_names )
        m_whichFilter->addItem(QString(filt));
    m_order = new QSpinBox();
    m_order->setSingleStep(1);
    m_order->setRange(2,16);
    m_f1 = new QSpinBox();
    m_f1->setSingleStep(1);
    m_f1->setRange(1, SAMPLE_FREQ/2);
    m_f2 = new QSpinBox();
    m_f2->setSingleStep(1);
    m_f2->setRange(1, SAMPLE_FREQ/2);

    QHBoxLayout *newFilterLayout = new QHBoxLayout();
    QVBoxLayout *whichfilterLayout = new QVBoxLayout();
    QVBoxLayout *orderLayout = new QVBoxLayout();
    QVBoxLayout *f1Layout = new QVBoxLayout();
    QVBoxLayout *f2Layout = new QVBoxLayout();
    QLabel *whichfilter = new QLabel("Filter");
    QLabel *order = new QLabel("Order");
    QLabel *f1 = new QLabel("f1");
    QLabel *f2 = new QLabel("f2");
    whichfilterLayout->addWidget(whichfilter);
    whichfilterLayout->addWidget(m_whichFilter);
    orderLayout->addWidget(order);
    orderLayout->addWidget(m_order);
    f1Layout->addWidget(f1);
    f1Layout->addWidget(m_f1);
    f2Layout->addWidget(f2);
    f2Layout->addWidget(m_f2);
    m_newFilter->size();
    newFilterLayout->addWidget(m_newFilter);
    newFilterLayout->addLayout(whichfilterLayout);
    newFilterLayout->addLayout(orderLayout);
    newFilterLayout->addLayout(f1Layout);
    newFilterLayout->addLayout(f2Layout);

    m_newFilterBox = new QGroupBox("New filter", this);
    m_newFilterBox->setLayout(newFilterLayout);

    m_filter_list = new QListWidget(this);
}

void Widget::_init_audio()
{
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
    m_device = new XYSeriesIODevice(m_series, m_freq_series, this);
    m_device->open(QIODevice::WriteOnly);
    m_audioInput->start(m_device);
}

void Widget::_init_recordBox()
{

    m_recordBox = new QGroupBox(this);
    m_recordButton = new QPushButton("Record", this);
    connect(m_recordButton, SIGNAL(clicked(bool)), m_device, SLOT(recording()));
    QLabel *bpm = new QLabel("BPM : ", this);
    m_bpmDisp = new QLabel(this);
    connect(m_device, SIGNAL(newBpm(int)), m_bpmDisp, SLOT(setNum(int)));
    m_status = new QTextEdit(this);

    QHBoxLayout *recBpm = new QHBoxLayout;
    recBpm->addWidget(m_recordButton);
    recBpm->addWidget(bpm);
    recBpm->addWidget(m_bpmDisp);
    QVBoxLayout *recordLayout = new QVBoxLayout;
    recordLayout->addLayout(recBpm);
    recordLayout->addWidget(m_status);

    m_recordBox->setLayout(recordLayout);
}
