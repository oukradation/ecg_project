#ifndef BPM_H
#define BPM_H
#include "filtergui.h"

#include <QObject>
#include <queue>
/*
* Author : Oda Olsen Nedrejord
*
*The bpm class contains a state machine which has an active state and a passive state.
* When state is active, it is searching for local maximum in signal buffer and calculates bpm.
* Furthermore it gives the time of each peak found. When state is passive,
* it does nothing else than check if amplitude is high enough to
* switch back to active state
*/

class Bpm
    :public QObject
{
    public:
        Bpm();
        ~Bpm();
        float getBpm(){
            return _bpm;
        }
        void findPeak(float signal);

    private:

        enum peakState { IDLE, SEARCHING_FOR_MAX };
        void addToQueue(std::size_t time);
        void calculateBpm();
        std::vector<float> _bpmBuffer;
        std::vector<std::size_t> _sampleCounterBuffer;

        std::size_t _bpmBuffer_idx;
        float _bpm;
        float _prev_max_val;
        float _current_max_val;
        float _amplitude;
        float _number_of_seconds;
        peakState _state;
        std::size_t _sample_counter;
        std::queue<std::size_t> _beats_queue;
};

#endif // BPM_H
