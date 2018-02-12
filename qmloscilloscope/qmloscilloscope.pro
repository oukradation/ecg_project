QT += charts qml quick

CONFIG += c++11

HEADERS += \
    datasource.h \
    ../portaudio/include/portaudio.h \
    rawsignal.h

SOURCES += \
    main.cpp \
    datasource.cpp \
    rawsignal.cpp

RESOURCES += \
    resources.qrc \
    resources.qrc

DISTFILES += \
    qml/qmloscilloscope/*


target.path = $$[QT_INSTALL_EXAMPLES]/charts/qmloscilloscope
INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../portaudio/lib/.libs/ -lportaudio

INCLUDEPATH += $$PWD/../portaudio/lib/.libs
DEPENDPATH += $$PWD/../portaudio/lib/.libs

unix:!macx: PRE_TARGETDEPS += $$PWD/../portaudio/lib/.libs/libportaudio.a
