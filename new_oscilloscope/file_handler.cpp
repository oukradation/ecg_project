#include "file_handler.h"

#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

File_handler::File_handler()
{
    _file_counter = 0;
    _counter = 0;
    _buffer_size = SAMPLE_FREQ*5;
    _audioFile.setAudioBufferSize(1, _buffer_size);
    _audioFile.setSampleRate(SAMPLE_FREQ);
    _audioFile.setBitDepth(24);
}

File_handler::~File_handler()
{
}

//The following function is adding one by one sample from signal to a buffer which
//is creating a wav file with length of approx. 5 seconds,
//after 5 seconds it creates a new wav file
void File_handler::addSample(float sample)
{
    _audioFile.samples[0][_counter] = sample;

    if (_counter == _buffer_size-1)
    {
        if (writeWavFile())
        {
            cout << "write to file sucess" << endl;
        }
        else
        {
            cout << "write to file fail" << endl;
        }
    }

    _counter = (_counter + 1) % _buffer_size;
}
//Function creates and writes to file located in directory: Audiofiles.
//Creates new file every 5 seconds
bool File_handler::writeWavFile()
{
    _file_counter++;
    return  _audioFile.save("../new_oscilloscope/Audiofiles/test_" + to_string(_file_counter) + ".wav");
}
