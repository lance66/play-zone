#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
# for Chessgames Services LLC
#
#-------------------------------------------------

TEMPLATE = app

QT += qml quick widgets svg
QT += sql

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(deployment.pri)

android {
folder_01.source = database
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01
}

deployment.files += chessgames.db
deployment.path = /assets
INSTALLS += deployment

TARGET = MobileChess


SOURCES += main.cpp\
    CG_validator.cpp \
    CG_dbManager.cpp \
    CG_user.cpp \
    CG_board.cpp \
    CG_square.cpp

HEADERS  += \
    CG_validator.h \
    CG_dbManager.h \
    CG_user.h \
    CG_piece.h \
    CG_square.h \
    CG_board.h \
    CG_define.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    android/AndroidManifest.xml \
    images/Flags.svg \
    images/cg_flag_turkey.jpg
