#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T09:46:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OS_3
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    sectionedmemoryallocator.cpp \
    sectionid.cpp \
    memorysection.cpp \
    queuetomemory.cpp \
    process.cpp

HEADERS  += mainwindow.h \
    sectionedmemoryallocator.h \
    sectionid.h \
    memorysection.h \
    queuetomemory.h \
    process.h

FORMS    += mainwindow.ui
