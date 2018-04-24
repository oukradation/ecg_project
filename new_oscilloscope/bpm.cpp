#include "bpm.h"
#include <iostream>

Bpm::Bpm() :
    _bpmBuffer(500,0.0),
    _sampleCounterBuffer(500),
    _bpmBuffer_idx(0),
    _prev_max_val(0),
    _current_max_val(0),
    _amplitude(0.3),
    _number_of_seconds(60.0),
    _state(peakState::IDLE),
    _sample_counter(0)
{

}

Bpm::~Bpm()
{

}


/*  The following function is adding a new time value
 *  to a FIFO queue which has maximum size of 10
 *
*/
void Bpm::addToQueue(size_t time)
{
   _beats_queue.push(time);
   if (_beats_queue.size() > 10)
      _beats_queue.pop();
}

/*
* The following function calculates Beats Per Minute using number of beats in current buffer
* divided with the time difference between first peak and last peak in current buffer which is
* multiplied with the number of seconds in a minute
*/
void Bpm::calculateBpm()
{
    float first_time = _beats_queue.front() / float(SAMPLE_FREQ);
    float last_time = _beats_queue.back() / float(SAMPLE_FREQ);
    if( _beats_queue.size() > 1 )
    {
        std::cout << "Bpm: " << int(_beats_queue.size() / float( last_time - first_time ) * _number_of_seconds) << endl;
    }
}

/*
* This function is working as a state machine. It stands idle if peak is lower than
* specified amplitude(noise in signal).
* If signal is getting higher than specified amplitude, it switches to search for peak.
* In this state it calculates Beats Per Minute in addition to the time when each
* new peak is found
*/
void Bpm::findPeak(float signal) {

     _bpmBuffer[_bpmBuffer_idx] = signal;
     _sampleCounterBuffer[_bpmBuffer_idx] = _sample_counter;

     if (_bpmBuffer_idx == 0)
     {
         auto max_elem = std::max_element(_bpmBuffer.begin(), _bpmBuffer.end());
         _current_max_val = *max_elem;
         switch (_state)
         {
            case peakState::IDLE:
                if (_current_max_val < _amplitude);
                else
                {
                    _state = peakState::SEARCHING_FOR_MAX;
                }
            break;
            case peakState::SEARCHING_FOR_MAX:
                if (_current_max_val > _prev_max_val)
                {
                }
                else if (_current_max_val <= _amplitude)
                {
                    int distance = std::distance(_bpmBuffer.begin(), max_elem);
                    float foundAtTime = (_sampleCounterBuffer[distance])/float(SAMPLE_FREQ);
                    addToQueue( _sampleCounterBuffer[distance] );
                    std::cout << "Found peak after " << foundAtTime  << " seconds" << std::endl;
                    calculateBpm();
                    _state = peakState::IDLE;
                }
            break;
         }
         _prev_max_val = _current_max_val;

     }

     _sample_counter++;
     _bpmBuffer_idx = (_bpmBuffer_idx + 1) % _bpmBuffer.size();
}

