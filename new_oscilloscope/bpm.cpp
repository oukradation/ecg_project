#include "bpm.h"
#include "xyseriesiodevice.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <numeric>

using namespace std;

bpm::bpm() :
    _buffer(8192),
    _buffer_idx(0),
    _fft(8192),
    _fft_mag(8192/2)
{
    //_transformer.setWindowFunction("Hamming");
}
bpm::~bpm()
{

}

float bpm::calculateBpm(float signal)
{
    _buffer[_buffer_idx] = signal;

    //closest value to 8000 which is power of 2
    const int SIZE = 8192;
    //checks if buffer has reached buffer window
    if ( _buffer_idx % 10 == 0 )
    {
        if(_transformer.setSize(SIZE) == QFourierTransformer::VariableSize)
        {
            cout << "This size is not a default fixed size of QRealFourier. Using a variable size instead.\n" << endl;
        }

        else if(_transformer.setSize(SIZE) == QFourierTransformer::InvalidSize)
        {
            cout << "Invalid FFT size.\n" << endl;
            return -1;
        }

        _transformer.forwardTransform(_buffer.data(), _fft.data());
        const QVector<QComplexFloat> &complex = _transformer.toComplex(_fft.data());

        size_t idx = 0;
        for ( const QComplexFloat& c : complex )
        {
            const float a = c.real();
            const float b = c.imaginary();
            _fft_mag[idx] = 0.4*std::log10(0.01*std::sqrt( a*a + b*b ))+0.4;
            idx++;
        }

    }

    _buffer_idx = (_buffer_idx + 1) % SIZE;
    return signal;
}



