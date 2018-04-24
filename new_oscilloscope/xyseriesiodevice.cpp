/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "xyseriesiodevice.h"
#include <QtCharts/QXYSeries>
#include <iostream>

using namespace std;

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QXYSeries * freq_series, QObject *parent) :
    QIODevice(parent),
    m_series(series),
    m_freq_series(freq_series)
{
    sig = new signalProcessing();
    sigFrequency = new Frequency_plotter();
    sigBpm = new Bpm();
    _recording = false;
}


qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    qint64 range = SAMPLE_FREQ;
    QVector<QPointF> oldPoints = m_series->pointsVector();
    QVector<QPointF> points;
    QVector<QPointF> freq_points;
    int resolution = 1;


    if (oldPoints.count() < range) {
        points = m_series->pointsVector();
    } else {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
    {
        float next = ((quint8)data[k] - 128)/128.0;
        next = sig->process(next);
        sigFrequency->calculateFFT(next);
        sigBpm->findPeak(next);
        points.append(QPointF(k + size, next));

        //adding each sample from signal to write to file
        if ( _recording ) sigFile.addSample(next);
    }
    m_series->replace(points);

    freq_points.clear();
    std::vector<float> &tmp = sigFrequency->fftData();
    for (size_t k = 0; k < tmp.size(); k++)
    {
       freq_points.append(QPointF(float(k)/tmp.size()*SAMPLE_FREQ/2,tmp[k]));
    }
    m_freq_series->replace(freq_points);

    emit newBpm((int)sigBpm->getBpm());

    return maxSize;
}

void XYSeriesIODevice::recording()
{
    _recording = !_recording;
}
