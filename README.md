# Project sketch

This project is digital processing ECG signal and classification of the siginal with machine learning algorithms. This is part of the cource "Effective C/C++ programming" at Høgskolen i Oslo og Akershus. It will be written exclusively in C++ with Qt framework. 

Qt GUI will be the skeleton of the program. Sensor for this program will be 3 lead ECG made as result of "Medical instrumentation". ECG signal will go through basic 2.order bandpass filter, then octo-coupler and will be sampled by computer thorugh 3.5mm audio jack. Qt interface will show oscilloscope like signal view and other measured parameters ( Bpm, etc ) and result of classification.

## QML documentation:
* https://doc.qt.io/qt-5.10/qmltypes.html



## process

### 3.apr
#### Log

#### TODO
* Filtrere bort EMG
* Implementere filterklasse - bl.a. notch filter
* Demonstrere objekorientering ved å endre filter ved hjelp av å arve fra base filterklasse
* Lage sykehusovervåkningsklasse - skal rapportere om unormale utslag på PQRST-kurven, rapportere om store endringer i puls(bpm) osv.
* Endre mellom 2-3 ulike filter i GUI


### 14.mar
#### Log
* Notch filter implemented (IIR direct II transposed)
* other IIR filters can just be implemented by changing some stuff from notchfilter 
#### TODO
* general base filter class which can be subclassed to usage? -> some c++ programing to get some points
* clean up qmloscilloscope -> too much garbage and unnecessary functions

### 25.feb
#### Log
* Now viewer is updated real time. 

#### TODO
* Find out how to do signal processing   
   * signal processing direct on port audio callback function? - currently 8000 samples in 1s
   * create an external buffer for signal processing then connect it to the viewer? - STL container
* Design filters
* Design interface 
   * what are we going to show? 
   * BPM

### 12.feb
#### Log
* Added rawsignal class implementing portaudio in oscilloscope qt application. compiles and runs ok.
* Buffer is created in rawsignal object and pointer to buffer can be acquired by `getData()` function. 
* Buffer size is at the moment sample rate ( 8000 ) * 1 sec. with float as data type.
* It's kind of ringbuffer. When buffer is filled, it starts overwrite from the start.
* Display is not updated automatically. - removed signal 2 and other sample sizes

#### TODO
* Find out how oscilloscope updating works and implement signal and slot to rawsignal class so that it can emit signal to update mechanism.
* Since we have buffer now, we need to look into processing the buffer.


### 11.feb
#### Log
* Created ring buffer with callbackfunction. test was written in `paex_record.c`. Compiled with `gcc paex_record.c libportaudio.a -lm -lasound -pthread -o paex_record.out` with .h file and .a file present in a same directory.
* callback function updates buffer with given length ( frames per buffer ). 

#### TODO
* Write a wrapper for Qt. Take a look at example cpp file in portaudio example folder.


### 7.feb
#### Log
* Sucessfully tested qml oscilloscope
#### TODO
* Replace generateData function with a receiveData function, which will receive realtime sampled ecg signal
* Edit qmloscilloscope graphical user interface with relevant functionality


### 1.feb
#### So far
* Have seen that ecg signal reads in through audio jack nicely.
* Have check out some sample from portaudio library. `paex_record.c` contains good example of reading signal in from audio jack for short while. 
#### TODO
* build a qt project with port audio library - it is faster to use multimedia library that is build directly on standard c++ library
* read in signal and show it as simple graph or dots in terminal - to confirm real time signal reading
* Check out some tools for oscilloscope like interface on Qt
* Check out signal processing library
* design simple filter eventually
* check out various method to classify ecg signal with ML technics.

## current plan

1. Find out if this project is do-able within given time.
2. ECG sampling feeding into data array in Qt (arduino ehealth vs ecg from last years project)
3. Qt GUI design
4. Digital signal processing - filtering, looking for suitable library, design pipeline for realtime processing
5. ECG dataset aquisition 
6. looking for suitable ML algorithm and library -> might want to test with python/scikit-learn

## some reflections

### ECG sampling

* with e-health kit, we will get easier access to the ECG, but much less sampling rate or even worse, non-constant sampling rate
* we can easily add SPO2 if we get data from ehealth kit
* with ECG circuit from the last years project, it will appear much cooler and sampling ECG with audiojack will give much richer signal with superior sampling rate compare to arduino.

### Real time Digital Signal Processing

* will need to design buffer and filter application. ( is FFT necessary? what length is ideal? etc)
* filter design - notch filter, bandpass filter
* Finding signal processing library for C++

### Qt GUI

* oscilloscope like display for ECG
* some parameters and tweaks need to be thought over

### Machine learning

* We will need to either collect dataset ourselves or find a suitable dataset for training.
* Some research needed to decide what kind of classfication is do-able and ideal.
* finding suitable ML library for C++
