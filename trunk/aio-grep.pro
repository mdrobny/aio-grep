TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/filereader.cpp \
    src/asynchronousfilereader.cpp \
    src/synchronousfilereader.cpp \
    src/resultline.cpp \
    src/regexfinder.cpp \
    src/dummyregexfinder.cpp \
    src/fileinfo.cpp \
    src/cpp11regexfinder.cpp \
    src/boostregexfinder.cpp \
    src/output.cpp \
    src/agrep.cpp \
    src/flags.cpp \
    src/output.cpp \
    src/timer.cpp \
    src/re2regexfinder.cpp

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
    src/output.h \
    src/agrep.h \
    src/flags.h \
    src/output.h \
    src/timer.h \
    src/re2regexfinder.h


