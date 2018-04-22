#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T20:33:03
#
#-------------------------------------------------

QT       += core gui charts multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Oscilloscope
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    widget.cpp \
    Biquad.cpp \
    Butterworth.cpp \
    filter.cpp \
    xyseriesiodevice.cpp \
    filtergui.cpp \
    bpm.cpp \
    sources/QFFT/qcomplexnumber.cpp \
    sources/QFFT/qfouriercalculator.cpp \
    sources/QFFT/qfourierfixedcalculator.cpp \
    sources/QFFT/qfouriertransformer.cpp \
    sources/QFFT/qfouriervariablecalculator.cpp \
    sources/QFFT/qwindowfunction.cpp \
    file_handler.cpp \
    sources/Audio/AudioFile.cpp

HEADERS += \
    widget.h \
    Biquad.h \
    Butterworth.h \
    filter.h \
    xyseriesiodevice.h \
    filtergui.h \
    bpm.h \
    file_handler.h \
    headers/Audio/AudioFile.h \
    headers/QFFT/Array.h \
    headers/QFFT/Array.hpp \
    headers/QFFT/def.h \
    headers/QFFT/DynArray.h \
    headers/QFFT/DynArray.hpp \
    headers/QFFT/FFTReal.h \
    headers/QFFT/FFTReal.hpp \
    headers/QFFT/FFTRealFixLen.h \
    headers/QFFT/FFTRealFixLen.hpp \
    headers/QFFT/FFTRealFixLenParam.h \
    headers/QFFT/FFTRealPassDirect.h \
    headers/QFFT/FFTRealPassDirect.hpp \
    headers/QFFT/FFTRealPassInverse.h \
    headers/QFFT/FFTRealPassInverse.hpp \
    headers/QFFT/FFTRealSelect.h \
    headers/QFFT/FFTRealSelect.hpp \
    headers/QFFT/FFTRealUseTrigo.h \
    headers/QFFT/FFTRealUseTrigo.hpp \
    headers/QFFT/OscSinCos.h \
    headers/QFFT/OscSinCos.hpp \
    headers/QFFT/qcomplexnumber.h \
    headers/QFFT/qfouriercalculator.h \
    headers/QFFT/qfourierfixedcalculator.h \
    headers/QFFT/qfouriertransformer.h \
    headers/QFFT/qfouriervariablecalculator.h \
    headers/QFFT/qwindowfunction.h

FORMS +=
