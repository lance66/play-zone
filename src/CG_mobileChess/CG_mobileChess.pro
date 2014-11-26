#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_mobileChess
TEMPLATE = app
ICON = cg_logo_hires_app_2.svg

SOURCES += main.cpp\
    CG_login.cpp \
    CG_validator.cpp \
    CG_splashScreen.cpp

HEADERS  += \
    CG_login.h \
    CG_validator.h \
    CG_splashScreen.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml \
    ../../bin/chessgames.db \
    ../../img/cg_logo_hires_app.png

RESOURCES += \
    resources.qrc
