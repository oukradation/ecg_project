#include "rawsignal.h"


rawsignal::rawsignal() : stream(0)
{
    // initialize buffer
    for ( int i = 0; i < BUFSIZE; i++ ) buf[i] = 0;
    data = {0, BUFSIZE, buf};

}

bool rawsignal::open()
{
    PaError err = paNoError;
    PaStreamParameters inputParameters;

    err = Pa_Initialize();
    if ( err != paNoError ) return false;

    // get default input device and setup
    inputParameters.device = Pa_GetDefaultInputDevice();
    if ( inputParameters.device == paNoDevice ) return false;
    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency =
            Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    // open stream
    err = Pa_OpenStream( &stream,
                         &inputParameters,
                         nullptr,
                         SAMPLING_RATE,
                         FRAME_PER_BUFFER,
                         paNoFlag,
                         &rawsignal::paCallback,
                         this);
    if ( err != paNoError ) return false;

    return true;
}

bool rawsignal::close()
{
    if ( stream == 0 ) return false;

    PaError err = Pa_CloseStream( stream );
    stream = 0;

    return ( err == paNoError );
}

bool rawsignal::start()
{
    if ( stream == 0 ) return false;

    PaError err = Pa_StartStream( stream );

    return ( err == paNoError );
}

bool rawsignal::stop()
{
    if ( stream == 0 ) return false;

    PaError err = Pa_StopStream( stream );

    return ( err == paNoError );
}

float *rawsignal::getData()
{
    return buf;
}

int rawsignal::paCallbackMethod(const void *inputbuffer,
                                void *outputbuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags)
{
    const float *input = (const float*)inputbuffer;
    float *output = &buf[data.frameNr];

    unsigned long i;
    long framesToCalc = framesPerBuffer;
    unsigned long framesLeft = data.maxFrame - data.frameNr;

    // prevent unused variable warnings
    (void) outputbuffer;
    (void) timeInfo;
    (void) statusFlags;

    if ( framesLeft < framesPerBuffer )
    {
        output = &data.buffer[0];
        data.frameNr = 0;
    }

    if( input == nullptr )
        for ( i = 0; i < framesToCalc; i++ )
            *output++ = 0.0;
    else
        for ( i = 0; i < framesToCalc; i++ )
            *output++ = *input++;

    data.frameNr += framesToCalc;

    return paContinue;

}

int rawsignal::paCallback(const void *inputbuffer,
                          void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData)
{
    return ((rawsignal*)userData)->paCallbackMethod(inputbuffer,
                                                    outputBuffer,
                                                    framesPerBuffer,
                                                    timeInfo,
                                                    statusFlags);
}

void rawsignal::paStreamFinishedMethod()
{
    cout << "Stream Completed" << endl;
}

void rawsignal::paStreamFinished(void *userdata)
{
    return ((rawsignal*)userdata)->paStreamFinishedMethod();
}
