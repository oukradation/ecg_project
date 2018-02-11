QT += charts qml quick

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
