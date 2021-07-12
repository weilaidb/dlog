TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cdlog.cpp \
        dlog.cpp \
        main.cpp \
        pubsw.cpp

HEADERS += \
    cdlog.h \
    dlog.h \
    pubsw.h
