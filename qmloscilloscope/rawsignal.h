#ifndef RAWSIGNAL_H
#define RAWSIGNAL_H

typedef struct{
   int frameNr;
   int maxFrame;
   float *buffer;
}rawData;


class rawsignal
{
public:
    rawsignal();
};

#endif // RAWSIGNAL_H
