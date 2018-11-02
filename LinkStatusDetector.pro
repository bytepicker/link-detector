#-------------------------------------------------
#
# Project created by QtCreator 2018-11-02T10:01:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LinkStatusDetector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    detector.cpp

HEADERS  += mainwindow.h \
    detector.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
