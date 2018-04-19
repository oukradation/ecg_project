#include "filtergui.h"

const char* filterGui::filter_names[5] = { "Lowpass",
                                           "Highpass",
                                           "Bandpass",
                                           "Bandstop",
                                           "Notch"};


filterGui::filterGui(QWidget *parent, filterType type, int f1, int f2, int order)
    :   _type(type), _order(order)
{
    QVBoxLayout *verticalFilterInstance = new QVBoxLayout;

    // filter information
    filt_info = QString(filter_names[(int)_type]) + " filter" +
                "  Order :  " + QString::number(_order);

    _filterLabel= new QLabel(filt_info);
    _onOff = new QPushButton(tr(""));
    _onOff->setCheckable(true);

    QHBoxLayout *horizontalTitleLayout = new QHBoxLayout;
    horizontalTitleLayout->addWidget(_filterLabel);
    horizontalTitleLayout->addWidget(_onOff);
    verticalFilterInstance->addLayout(horizontalTitleLayout);

    // add slider for lower cut
    _filterSlider_lower = new QSlider(Qt::Horizontal);
    _filterSlider_lower->setRange(0,400);
    _filterSlider_lower->setTickPosition(QSlider::TicksBothSides);
    _filterSlider_lower->setTickInterval(10);
    _filterSlider_lower->setSingleStep(1);
    _filterSlider_lower->setValue((int)f1);


    _filterFrequency_lower = new QLabel(this);
    _filterFrequency_lower->setText(QString::number((int)f1));
    connect(_filterSlider_lower, SIGNAL(valueChanged(int)), _filterFrequency_lower, SLOT(setNum(int)));

    QHBoxLayout *horizontalSliderLayout = new QHBoxLayout;
    horizontalSliderLayout->addWidget(_filterSlider_lower);
    horizontalSliderLayout->addWidget(_filterFrequency_lower);

    verticalFilterInstance->addLayout(horizontalSliderLayout);

    if ( type == BP || type == BS )
    {
         // add slider for upper cut
        _filterSlider_upper = new QSlider(Qt::Horizontal);
        _filterSlider_upper->setRange(0,400);
        _filterSlider_upper->setTickPosition(QSlider::TicksBothSides);
        _filterSlider_upper->setTickInterval(10);
        _filterSlider_upper->setSingleStep(1);
        _filterSlider_upper->setValue((int)f2);

        _filterFrequency_upper= new QLabel(this);
        _filterFrequency_upper->setText(QString::number((int)f2));
        connect(_filterSlider_upper, SIGNAL(valueChanged(int)), _filterFrequency_upper, SLOT(setNum(int)));

        QHBoxLayout *horizontalSliderLayout2 = new QHBoxLayout;
        horizontalSliderLayout2->addWidget(_filterSlider_upper);
        horizontalSliderLayout2->addWidget(_filterFrequency_upper);

        verticalFilterInstance->addLayout(horizontalSliderLayout2);

    }

    setLayout(verticalFilterInstance);

}


