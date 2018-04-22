#include "frequency_plotter.h"
#include "xyseriesiodevice.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <numeric>

using namespace std;

Frequency_plotter::Frequency_plotter() :
    _buffer(FFT_SIZE),
    _buffer_idx(0),
    _fft(FFT_SIZE),
    _fft_mag(FFT_SIZE/2),
    _transformer(FFT_SIZE)
{
    _transformer.setWindowFunction("Hamming");
}
Frequency_plotter::~Frequency_plotter()
{

}

void Frequency_plotter::calculateFFT(float signal)
{
    _buffer[_buffer_idx] = signal;

    //update plot every 200 sample
    if ( _buffer_idx % 200 == 0 )
    {
        if(_transformer.setSize(FFT_SIZE) == QFourierTransformer::VariableSize)
        {
            cout << "This size is not a default fixed size of QRealFourier. Using a variable size instead.\n" << endl;
        }

        else if(_transformer.setSize(FFT_SIZE) == QFourierTransformer::InvalidSize)
        {
            cout << "Invalid FFT size.\n" << endl;
        }

        //calculating FFT on signal buffer
        _transformer.forwardTransform(_buffer.data(), _fft.data());
        //calculating each value from fft signal buffer to complex values
        const QVector<QComplexFloat> &complex = _transformer.toComplex(_fft.data());

        //calculating absolute value from each value in complex value buffer
        //then scaling to dB
        size_t idx = 0;
        for ( const QComplexFloat& c : complex )
        {
            const float realPart = c.real();
            const float imaginaryPart = c.imaginary();
            _fft_mag[idx] = 20.0*std::log10(std::sqrt( realPart*realPart + imaginaryPart*imaginaryPart ));
            idx++;
        }

        _max_index = std::distance(_fft_mag.begin(), std::max_element(_fft_mag.begin(), _fft_mag.end()) );
    }

    _buffer_idx = (_buffer_idx + 1) % FFT_SIZE;
}



