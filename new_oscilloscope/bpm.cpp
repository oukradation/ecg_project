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
    _buffer(FFT_SIZE),
    _buffer_idx(0),
    _fft(FFT_SIZE),
    _fft_mag(FFT_SIZE/2)
{
    //_transformer.setWindowFunction("Hamming");
}
bpm::~bpm()
{

}

float bpm::calculateFFT(float signal)
{
    _buffer[_buffer_idx] = signal;

    //closest value to 8000 which is power of 2
    //checks if buffer has reached buffer window
    if ( _buffer_idx % 10 == 0 )
    {
        if(_transformer.setSize(FFT_SIZE) == QFourierTransformer::VariableSize)
        {
            cout << "This size is not a default fixed size of QRealFourier. Using a variable size instead.\n" << endl;
        }

        else if(_transformer.setSize(FFT_SIZE) == QFourierTransformer::InvalidSize)
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

        _max_index = std::distance(_fft_mag.begin(), std::max_element(_fft_mag.begin(), _fft_mag.end()) );

    }

    _buffer_idx = (_buffer_idx + 1) % FFT_SIZE;
    return signal;
}



