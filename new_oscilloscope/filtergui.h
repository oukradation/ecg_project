#ifndef FILTERGUI_H
#define FILTERGUI_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QGroupBox>
#include <vector>

#include "filter.h"

/*
 * Graphic interface for a filter instance
 *
 * Author : Wonho Lee, Oda Nedrejord
 *
 */


class filterGui
        : public QWidget
{
    Q_OBJECT
public:
    filterGui(QWidget *parent = 0, filterType type = LP,
              int f1 = 0, int f2 = 0, int order = 0);
    ~filterGui(){};

    filterType getType(){
        return _type;
    }
    bool getButtonState(){
        return !_onOff->isChecked();
    }


    static const char* filter_names[5];

    QSlider *_filterSlider_lower;
    QSlider *_filterSlider_upper;

private:
    filterType _type;
    int _order;

    QString filt_info;
    QLabel *_filterLabel;
    QLabel *_filterFrequency_lower;
    QLabel *_filterFrequency_upper;
    QPushButton *_onOff;

};

#endif // FILTERGUI_H
