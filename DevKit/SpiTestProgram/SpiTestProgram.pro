#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T15:11:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpiTestProgram
TEMPLATE = app


SOURCES += main.cpp\
        spitestprogram.cpp \
    spiapi.cpp \
    e3pjr.cpp

HEADERS  += spitestprogram.h \
    spiapi.h \
    e3pjr.h

FORMS    += spitestprogram.ui \
    e3pjr.ui

DISTFILES += \
    SpiTestProgramApp.service
