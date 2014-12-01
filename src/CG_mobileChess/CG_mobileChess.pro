#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
# for Chessgames Services LLC
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_mobileChess
TEMPLATE = app

SOURCES += main.cpp\
    CG_login.cpp \
    CG_validator.cpp \
    CG_dbManager.cpp

HEADERS  += \
    CG_login.h \
    CG_validator.h \
    CG_dbManager.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    ../../bin/chessgames.db \
    ../../img/cg_logo_hires_app.png

RESOURCES += \
    resources.qrc
