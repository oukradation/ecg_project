#ifndef NOTCHFILTER_HPP_
#define NOTCHFILTER_HPP_

#include <iostream>
#include <cmath>

class Notchfilter{

	public:

		Notchfilter();
		Notchfilter(float target_freq, float sample_freq, float degree);
		~Notchfilter();
		float filter(float xn);

	private:
		float _v1_prev;
		float _v2_prev;
		float _a1;
		float _a2;
		float _b1;

};

#endif

Notchfilter::Notchfilter(float target_freq, float sample_freq, float degree)
{
	// initial condition
	_y_prev = _v1_prev = _v2_prev = 0;

	// calculate coef
	_a1 = -2*degree*cos(2*M_PI*target_freq/sample_freq);
	_a2 = degree*degree;
	_b1 = -2*cos(2*M_PI*target_freq/sample_freq);
}

inline float Notchfilter::filter(float xn)
{
	float yn = _v1_prev + xn;
	float v1 = _v2_prev - _a1*yn + _b1*xn;
	float v2 = xn - _a2*yn;

	_v1_prev = v1;
	_v2_prev = v2;

	return yn;
}
