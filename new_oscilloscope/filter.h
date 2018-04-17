#include <vector>
#include "Biquad.h"

using namespace std;

/*
 * Author : Wonho Lee
 *
 * This class implements a list of Biquad filters with coefficient defined in Biquad class as in take one value and spit out the result.
 * class will be using direct 2 transposed implementation
 *
 */

class filter
{
	public:
		// ctor
		filter();
		filter(int num_fil);
		~filter();

		// setter
		bool addFilter(vector<Biquad> filt);

		float process(float xn);
        vector <Biquad> _biquads;

	private:
		int _num_fil;
		vector <double> _v1;
		vector <double> _v2;

};
