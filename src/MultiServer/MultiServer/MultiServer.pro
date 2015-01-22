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
    cg_match.cpp \
    cg_server.cpp \
    cg_playerThread.cpp

HEADERS += \
    cg_match.h \
    cg_server.h \
    cg_playerThread.h
