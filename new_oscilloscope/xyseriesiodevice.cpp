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

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    _m_series(series)
{
    sigBpm = new bpm();
    sig = new signalProcessing();
    on = false;
}

void XYSeriesIODevice::notchOn()
{
}

qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    qint64 range = 8000;
    QVector<QPointF> oldPoints = _m_series->pointsVector();
    QVector<QPointF> points;
    int resolution = 1;


    if (oldPoints.count() < range) {
        points = _m_series->pointsVector();
    } else {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
    {
        float next = ((quint8)data[k] - 128)/128.0;
        next = sig->process(next);
        sigBpm->calculateBpm(next);

        points.append(QPointF(k + size, next));

    }

    /* Uncomment to show FFT */
    //points.clear();
    //float *tmp = sigBpm->fftData();
    //for (int k = 0; k < 8192/2; k++)
    //{
     //  points.append(QPointF(k,tmp[k]));
    //}

    _m_series->replace(points);
    return maxSize;
}
