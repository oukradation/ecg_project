#ifndef FILTER_H_
#define FILTER_H_

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
 * Base irr filter class
 *
 * 1. set up filter
 *    - get requirements (fc, fs, order, etc)
 *    - calculate coefficient
 * 2. start sending values to filter method
 * 3. by changing cut-off frequency, 
 *    - calculate coefficient again
 * 4. continue to 2
 *
 */

class Iirfilter{

	public:

		Iirfilter(int order)
			: _order(order)
		{};

		~Iirfilter();

		virtual void calc_coef(float, float, float) = 0;
		virtual void calc_coef(float, float) = 0;

		float filter(float xn);

	protected:

		int _order;
		vector<float> _b;
		vector<float> _a;
		vector<float> _v_prev;

};

/*
 * inherit base class and overwrite virtual function to calculate coefficients
 */
class Notchfilter
	: public Iirfilter{
	
	public:
		void calc_coef(float target_freq, float sampling_freq, float degree);

};

// fc, fs, order
class Lowpassfilter
	: public Iirfilter{
	
	public:
		void calc_coef(float cutoff_freq, float sampling_freq);

};

class Highpassfilter
	: public Iirfilter{

	public:
		void calc_coef(float cutoff_freq, float sampling_freq);

};

#endif
