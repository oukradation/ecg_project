#include "filter.h"

float Iirfilter::filter(float xn)
{
	vector<float> vn;
	
	

	return 0;
}

void Notchfilter::calc_coef(float target_freq, float sample_freq, float degree)
{
    // initial condition
    _v1_prev = _v2_prev = 0;

    // calculate coef
    _a1 = -2*degree*cos(2*M_PI*target_freq/sample_freq);
    _a2 = degree*degree;
    _b1 = -2*cos(2*M_PI*target_freq/sample_freq);
}

float Notchfilter::filter(float xn)
{
    float yn = _v1_prev + xn;
    float v1 = _v2_prev - _a1*yn + _b1*xn;
    float v2 = xn - _a2*yn;

    _v1_prev = v1;
    _v2_prev = v2;

    return yn;
}
