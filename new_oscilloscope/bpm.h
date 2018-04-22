#ifndef BPM_H
#define BPM_H
#include "filtergui.h"

#include <QObject>
/*
* Author : Oda Olsen Nedrejord
*
* This file contains a bpm calculator, code has not been testet with
* ecg-signal yet. It probably needs minor modifications after testing
*/

class Bpm
    :public QObject
{
    public:
        Bpm();
        ~Bpm();
        void calculateBpm(float signal);
    private:
        std::vector<float> _bpmBuffer;
        std::size_t _bpmBuffer_idx;
        std::size_t _bpm_idx;
        float _prev_max_val;
        float _current_max_val;
        std::size_t _timer;
        bool _nextPeak;

};

#endif // BPM_H
