TEMPLATE = app
CONFIG += opengl c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    world.cpp \
    block.cpp \
    highspeedblock.cpp \
    lowspeedblock.cpp \
    wallblock.cpp \
    hideoutblock.cpp
LIBS += -lglut -lGLU

DISTFILES +=

HEADERS += \
    world.h \
    block.h \
    highspeedblock.h \
    lowspeedblock.h \
    wallblock.h \
    hideoutblock.h \
    drawutils.h
