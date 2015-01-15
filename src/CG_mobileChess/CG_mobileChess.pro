#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
# for Chessgames Services LLC
#
#-------------------------------------------------

TEMPLATE = app

QT += qml quick widgets
QT += sql

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(deployment.pri)

TARGET = CG_mobileChess

SOURCES += main.cpp\
    CG_validator.cpp \
    CG_dbManager.cpp \
    CG_user.cpp

HEADERS  += \
    CG_validator.h \
    CG_dbManager.h \
    CG_user.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    resources.qrc
