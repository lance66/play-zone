#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = login
TEMPLATE = app


SOURCES += main.cpp\
    CG_login.cpp \
    CG_validator.cpp \
    CG_splashScreen.cpp

HEADERS  += \
    CG_login.h \
    CG_validator.h \
    CG_splashScreen.h

FORMS    += \
splashscreen.ui
