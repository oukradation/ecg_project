#ifndef FREQUENCY_PLOTTER_H
#define FREQUENCY_PLOTTER_H
#include "headers/QFFT/qfouriertransformer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <numeric>
#include <QObject>
#include "filtergui.h"
/*
* Author : Oda Olsen Nedrejord
*
* This file contains a frequency plotter which is receiving a signal buffer
* from xyseriesiodevice class, calculates fft from the signal and plotting
* the frequency spectrum in gui. In addition, this class is calculating current frequency
* which can be useful to show current frequency value or to verify while testing
*/

class Frequency_plotter
    :public QObject
{
    const size_t FFT_SIZE = 4096*2;
    public:
        Frequency_plotter();
        ~Frequency_plotter();
        std::vector<float>& fftData() { return _fft_mag; };
        void calculateFFT(float);
        size_t max_index() { return _max_index; };
        float calculateFrequency() { return float(_max_index)/FFT_SIZE*SAMPLE_FREQ; };

    public slots:
    private:
        std::vector<float> _buffer;
        size_t _buffer_idx;
        std::vector<float> _fft;
        std::vector<float> _fft_mag;
        size_t _max_index;
        QFourierTransformer _transformer;


};

#endif // FREQUENCY_PLOTTER_H
