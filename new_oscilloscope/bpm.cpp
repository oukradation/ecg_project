#include "bpm.h"
#include <iostream>

Bpm::Bpm() :
    _bpmBuffer(SAMPLE_FREQ),
    _bpmBuffer_idx(0),
    _bpm_idx(0),
    _prev_max_val(0),
    _current_max_val(0),
    _timer(0),
    _nextPeak(true)
{

}

Bpm::~Bpm()
{

}

void Bpm::calculateBpm(float signal) {

     _bpmBuffer[_bpmBuffer_idx] = signal;

     if ( (_bpmBuffer_idx % SAMPLE_FREQ/4) == 0)
     {
        _current_max_val = *std::max_element(_bpmBuffer.begin(), _bpmBuffer.end());
        std::cout << _current_max_val << std::endl;

        if( _current_max_val < _prev_max_val && _nextPeak == true && _prev_max_val > 0.4 ) {
            _bpm_idx++;
            _nextPeak = false;
        }

        if( _current_max_val > _prev_max_val ) {
            _nextPeak = true;
        }

        _prev_max_val = _current_max_val;
        _timer++;
     }

     if( _timer == (4 * 60) )
     {
        std::cout << "Bpm: " << _bpm_idx << std::endl;
        _bpm_idx = 0;
        _timer = 0;
     }

     _bpmBuffer_idx = (_bpmBuffer_idx + 1) % SAMPLE_FREQ;
}
