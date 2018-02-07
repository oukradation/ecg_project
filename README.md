# Project sketch

This project is digital processing ECG signal and classification of the siginal with machine learning algorithms. This is part of the cource "Effective C/C++ programming" at Høgskolen i Oslo og Akershus. It will be written exclusively in C++ with Qt framework. 

Qt GUI will be the skeleton of the program. Sensor for this program will be 3 lead ECG made as result of "Medical instrumentation". ECG signal will go through basic 2.order bandpass filter, then octo-coupler and will be sampled by computer thorugh 3.5mm audio jack. Qt interface will show oscilloscope like signal view and other measured parameters ( Bpm, etc ) and result of classification.

## QML documentation:
* https://doc.qt.io/qt-5.10/qmltypes.html

## process

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
