#include "filter.h"

filter::filter(int num_fil)
	:_num_fil(num_fil)
{
    _biquads.resize(num_fil);
    _v1.resize(num_fil);
    _v2.resize(num_fil);

    fill(_v1.begin(), _v1.end(), 0);
    fill(_v2.begin(), _v2.end(), 0);

}

bool filter::addFilter(vector<Biquad> filt)
{
    //_biquads.insert(_biquads.begin(), filt.begin(), filt.end());
    _biquads = filt;

	return true;
}

float filter::process(float xn)
{
	float yn, v1, v2;
	for ( int i = 0; i < (int)_biquads.size(); i++ )
	{
		yn = _v1[i] + _biquads[i].b0*xn;
		v1 = _v2[i] -_biquads[i].a1*yn + _biquads[i].b1*xn;
		v2 = _biquads[i].b2*xn - _biquads[i].a2*yn;

		_v1[i] = v1;
		_v2[i] = v2;
		xn = yn;
	}

	return yn;
}
