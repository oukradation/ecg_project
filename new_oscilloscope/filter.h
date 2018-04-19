#ifndef FILTER_H_
#define FILTER_H_

#include <QObject>
#include <vector>
#include <cmath>
#include "Butterworth.h"

using namespace std;

/*
 * Author : Wonho Lee
 *
 * This file contains filter class, signalProcessing class and Notchfilter class
 *
 * filter class implements a list of Biquad filters with coefficient defined in Biquad class as in take one value and spit out the result.
 * class will be using direct 2 transposed implementation
 *
 */

typedef enum
{
    LP = 0,  // Lowpass
    HP = 1,  // Highpass
    BP = 2,  // Bandpass
    BS = 3,  // Bandstop
    NF = 4   // Notch filter - 2.order IIR
}filterType;

class filter
{
    public:
    	// ctor
        filter(){};
        filter(filterType type, double fs, double f1, double f2, int order);
        ~filter(){};
        
        int getSize(){
            return _biquads.size();
        }
        void filterOn(bool on){
            _onoff = on;
        }
        
        bool adjustFilter(double f1, double f2);
    	float process(float xn);
    
    private:
        void _reset();
    	bool _makeFilter(double f1, double f2);
        float _normalize(float xn);

        float _max;
        int _order;
        double _fs;
        filterType _type;
        bool _onoff;

        vector <Biquad> _biquads;
        vector <double> _v1;
    	vector <double> _v2;
    
};

/*
 * Signal processing class
 *
 * this class is container for filter objects and process signal in serial
 * inherited QObject in order to receive signal from gui
 *
 */

class signalProcessing
        :public QObject
{
    public:
        signalProcessing(){};
        ~signalProcessing(){};
        
        void addFilter(filter filt){
           _filters.push_back(filt);
        }
        
        void removeFilter(int filt_num){
            _filters.erase(_filters.begin()+filt_num);
        }
        
        float process(float x);
    
    public slots:
        bool changeAttr(int filt_num);
    
    
    private:
        vector <filter> _filters;
    
};


/*
 * Notchfilter class
 * It calculates coefficients for 2.order IIR notchfilter for given
 *  fs - sampling frequency
 *  f  - target frequency
 *  r  - damping around target frequency r -> 1 damps almost only one frequency compoent
 *
 * This could have been a simple function in filter class but written as own class for
 * the sake of consistency of code, which pairs with butterworth class
 */
class Notchfilter
{
    public:
        Notchfilter(){};
        ~Notchfilter(){};

        void coefficients(double fs, double f, double r, vector<Biquad>& biquad);
};


#endif
