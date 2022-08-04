#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app

SOURCES += main.cpp\
        window.cpp \
    draw.cpp \
    sender.cpp \
    dataqueue.cpp \
    receiver.cpp

HEADERS  += window.h \
    draw.h \
    sender.h \
    dataqueue.h \
    receiver.h

FORMS    += window.ui

LIBS += -L/usr/local/lib -lwiringPi -lpthread
