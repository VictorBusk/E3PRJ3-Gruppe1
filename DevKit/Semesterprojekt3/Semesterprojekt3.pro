#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T12:44:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Semesterprojekt3
TEMPLATE = app


SOURCES += main.cpp\
        position.cpp \
    light.cpp \
    plannerdialog.cpp \
    planner.cpp \
    spiapi.cpp \
    QVirtualKeyboard.cpp

HEADERS  += position.h \
    light.h \
    plannerdialog.h \
    planner.h \
    spiapi.h \
    QVirtualKeyboard.h

FORMS    += \
    plannerdialog.ui \
    display.ui

DISTFILES +=
