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
    CG_playerConnection.cpp \
    CG_server.cpp \
    CG_match.cpp

HEADERS += \
    CG_match.h \
    CG_playerConnection.h \
    CG_server.h
