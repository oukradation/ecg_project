#ifndef BPM_H
#define BPM_H
#include "headers/QFFT/qfouriertransformer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <numeric>
#include <QObject>
/*
* Author : Oda Nedrejord
*
*/

class bpm
    :public QObject
{
    const size_t FFT_SIZE = 8192*2;
    public:
        bpm();
        ~bpm();
        std::vector<float>& fftData() { return _fft_mag; };
        float calculateFFT(float);
        size_t max_index() { return _max_index; };
        float calculateBpm() { return float(_max_index)/FFT_SIZE*8000; };

    public slots:
    private:
        std::vector<float> _buffer;
        std::vector<float> _fft;
        std::vector<float> _fft_mag;
        size_t _max_index;
        size_t _buffer_idx;
        QFourierTransformer _transformer;


};



#endif // BPM_H
