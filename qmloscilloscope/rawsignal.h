#ifndef RAWSIGNAL_H
#define RAWSIGNAL_H

#include <iostream>
#include "portaudio.h"

#define SAMPLING_RATE 8000
#define FRAME_PER_BUFFER 100
#define NUM_SEC 1
#define BUFSIZE SAMPLING_RATE*NUM_SEC

using namespace std;

typedef struct{
   int frameNr;
   int maxFrame;
   float *buffer;
}rawData;


class rawsignal
{
public:
    rawsignal();
    ~rawsignal(){};
    bool open();
    bool close();
    bool start();
    bool stop();
    float* getData();

private:
    // Instance callback
    int paCallbackMethod(const void *inputbuffer,
                         void *outputbuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags);
    // Callback for portaudio engine
    static int paCallback( const void *inputbuffer,
                           void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData);
    // routine for when is done
    void paStreamFinishedMethod();
    static void paStreamFinished(void* userdata);

    PaStream *stream;
    rawData data;
    float buf[BUFSIZE];

};

#endif // RAWSIGNAL_H
