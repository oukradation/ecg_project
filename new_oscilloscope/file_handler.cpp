#include "file_handler.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <QDir>

using namespace std;

File_handler::File_handler()
{
    _file_counter = 0;
    _counter = 0;
    //creates a buffer which is 5 seconds long
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
/*Function creates and writes to file located in directory: Audiofiles.
*If directory does not exist, it makes a new directory.
* This class creates a new file every 5 seconds when recording button
* is pushed.
*/
bool File_handler::writeWavFile()
{
    _file_counter++;

    QDir dir("Audiofiles/test_");
    if (!dir.exists()) {
        dir.mkpath("Audiofiles/test_");
        return  _audioFile.save("../new_oscilloscope/Audiofiles/test_" + to_string(_file_counter) + ".wav");
    }

    else {
        return  _audioFile.save("../new_oscilloscope/Audiofiles/test_" + to_string(_file_counter) + ".wav");

    }

}
