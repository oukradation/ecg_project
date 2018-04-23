#ifndef BPM_H
#define BPM_H
#include "filtergui.h"

#include <QObject>
#include <queue>
/*
* Author : Oda Olsen Nedrejord
*
* This file contains a state machine which is used to calculate bpm. It's searching
* for high peaks in signal buffer and calculates bpm. In addition it gives the
* time of each peak found. Code has not been testet with a real ecg-signal yet.
* Gain probably needs to be adjusted when testing.
*/

class Bpm
    :public QObject
{
    public:
        Bpm();
        ~Bpm();
        void findPeak(float signal);
    private:

        enum peakState { IDLE, SEARCHING_FOR_MAX };
        void calculateBpm();
        void addToQueue(std::size_t time);
        std::vector<float> _bpmBuffer;
        std::size_t _bpmBuffer_idx;
        float _prev_max_val;
        float _current_max_val;
        float _gain;
        float _number_of_seconds;
        peakState _state;
        std::size_t _sample_counter;
        std::queue<std::size_t> _beats_queue;
};

#endif // BPM_H
