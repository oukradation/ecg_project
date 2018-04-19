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

bpm::bpm()
{

}
bpm::~bpm()
{

}

float bpm::calculateBpm(float signal)
{
    float testSignal = signal*8;
    return testSignal;
}



