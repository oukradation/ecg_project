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
