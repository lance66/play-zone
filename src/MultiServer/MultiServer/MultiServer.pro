#-------------------------------------------------
#
# Project created by QtCreator 2011-04-15T15:49:12
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = MultiServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp \
    cg_match.cpp

HEADERS += \
    myserver.h \
    mythread.h \
    cg_match.h
