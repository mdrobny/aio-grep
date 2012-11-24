TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/filereader.cpp \
    src/asynchronousfilereader.cpp \
    src/synchronousfilereader.cpp \
    src/main.cpp \
    src/resultline.cpp \
    src/regexfinder.cpp \
    src/dummyregexfinder.cpp

HEADERS += \
    src/ResultLine.h \
    src/filereader.h \
    src/asynchronousfilereader.h \
    src/synchronousfilereader.h \
    src/resultline.h \
    src/regexfinder.h \
    src/dummyregexfinder.h
