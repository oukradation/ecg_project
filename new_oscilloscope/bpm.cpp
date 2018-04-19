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
    _buffer(8000),
    _buffer_idx(0)
{

}
bpm::~bpm()
{

}

float bpm::calculateBpm(float signal)
{
    _buffer[_buffer_idx] = signal;
    _buffer_idx++;

    if (_buffer_idx == 8000)
    {
        cout << "full buffer!" << endl;
        _buffer_idx = 0;
    }

    return signal;
}



