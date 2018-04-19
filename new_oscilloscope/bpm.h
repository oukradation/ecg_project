#ifndef BPM_H
#define BPM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <numeric>
#include <QObject>


class bpm
    :public QObject
{

    public:
        bpm();
        ~bpm();

        float calculateBpm(float);

    public slots:
    private:

};



#endif // BPM_H
