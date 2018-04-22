#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <QObject>
#include "headers/Audio/AudioFile.h"
#include "filtergui.h"
/*
*
*This file contains a file handler which implements audiofile class to create .wav files.
* File_handler class receives ecg signals from xyseriesiodevice class and creates 5 seconds
* long .wav files out of the signals.
*
* Author : Oda Olsen Nedrejord
*
*/
class File_handler
    :public QObject
{

    public:
        File_handler();
        ~File_handler();
        bool writeWavFile();
        void addSample(float sample);

    private:
        AudioFile<float> _audioFile;
        size_t _counter;
        size_t _buffer_size;
        size_t _file_counter;
};



#endif // FILE_HANDLER_H

