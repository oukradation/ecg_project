#define NORMALIZE 1

#include "filter.h"

filter::filter(filterType type, double fs, double f1, double f2, int order)
    :_type(type), _fs(fs), _order(order)
{
    if (!_makeFilter(f1, f2))
			throw runtime_error("Fail to make a filter with given specification");
    _reset();
}

bool filter::adjustFilter(double f1, double f2)
{
    // clear previous biquads filter
    _biquads.erase(_biquads.begin(), _biquads.end());

    // and make new
    bool success = _makeFilter(f1, f2);

    // zero initial state for delays
    _reset();

    return success;
}

float filter::process(float xn)
{
    // only filter if the filter is on
    if ( !_onoff ) return xn;

    // calculate output yn with direct 2 transposed
	float yn, v1, v2;
	for ( int i = 0; i < (int)_biquads.size(); i++ )
	{
		yn = _v1[i] + _biquads[i].b0*xn;
        v1 = _v2[i] +_biquads[i].a1*yn + _biquads[i].b1*xn;
        v2 = _biquads[i].b2*xn + _biquads[i].a2*yn;

		_v1[i] = v1;
		_v2[i] = v2;
		xn = yn;
	}

#if NORMALIZE
    yn = _normalize(yn);
#endif

	return yn;
}

void filter::_reset()
{
    _onoff = true;
    _max = 1.0;
    _v1.resize(getSize());
    _v2.resize(getSize());
    fill(_v1.begin(), _v1.end(), 0);
    fill(_v2.begin(), _v2.end(), 0);
}

bool filter::_makeFilter(double f1, double f2)
{
	bool success = true;
    if ( _type == NF )
    {
        Notchfilter notch;
        // for notchfilter implementation f2 is dampning factor around target frequency
        notch.coefficients(_fs, f1, f2, _biquads);
        // notchfilter is always successful
    }
    else
    {
        Butterworth butter;
        double gain = 1.0; // default as 1.0 since gain is unpredictable
        success = butter.coefficients((Butterworth::FILTER_TYPE)(10000 + (int)_type), _fs,
                            f1, f2, _order, _biquads, gain);
    }
	return success;
}

/*
 * Normalize function implemented due to unpredictable gain from butterworth filter.
 *
 * expected maximum output from every filter is 1 to -1
 * the functions simply updates maximum value and divide output by registered maximum value
 *
 * this is temporal solution, so it will only be called when flag is enabled
 */
float filter::_normalize(float xn)
{
    if ( abs(xn) > _max )
        _max = abs(xn);

    return xn/_max;
}

/*
 * process signal through filters connected in serial
 */
float signalProcessing::process(float x)
{
    for ( auto&& filter : _filters )
       x = filter.process(x);
    return x;
}
#include<iostream>
bool signalProcessing::changeAttr(int filt_num)
{
    std::cout<< "should change attr" << std::endl;

}

void Notchfilter::coefficients(double fs, double f, double r, vector <Biquad>& biquad)
{
    // notchfilter is always one biquad
    biquad.resize(1);

    // calculate coefficients for 2.order IIR notchfilter
    biquad[0].a1 = 2*r*cos(2*M_PI*f/fs);
    biquad[0].a2 = -r*r;
    biquad[0].b1 = -2*cos(2*M_PI*f/fs);
    biquad[0].b0 = biquad[0].b2 = 1.0;
}
