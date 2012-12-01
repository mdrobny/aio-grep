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
    src/dummyregexfinder.cpp \
    src/fileinfo.cpp \
    src/cpp11regexfinder.cpp \
    src/boostregexfinder.cpp \
    output.cpp \
    src/output.cpp

HEADERS += \
    src/ResultLine.h \
    src/filereader.h \
    src/asynchronousfilereader.h \
    src/synchronousfilereader.h \
    src/resultline.h \
    src/regexfinder.h \
    src/dummyregexfinder.h \
    src/fileinfo.h \
    src/cpp11regexfinder.h \
    src/boostregexfinder.h \
    output.h \
    src/output.h

