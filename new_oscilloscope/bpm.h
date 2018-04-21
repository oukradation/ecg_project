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


class bpm
    :public QObject
{

    public:
        bpm();
        ~bpm();
        float* fftData() { return _fft_mag.data(); };
        float calculateBpm(float);

    public slots:
    private:
        std::vector<float> _buffer;
        std::vector<float> _fft;
        std::vector<float> _fft_mag;
        size_t _buffer_idx;
        QFourierTransformer _transformer;


};



#endif // BPM_H
