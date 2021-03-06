#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T18:29:41
# for Chessgames Services LLC
#
#-------------------------------------------------

TEMPLATE = app

QT += qml quick widgets
QT += sql
QT += multimedia

CONFIG += resources_big

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

include(deployment.pri)

android {
folder_01.source = database
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

#For Android
deployment.path = /assets
}

ios {
#For iOS
deployment.path =
QMAKE_BUNDLE_DATA += deployment
}

deployment.files += chessgames.db

INSTALLS += deployment

TARGET = Chessgames


SOURCES += main.cpp\
    CG_validator.cpp \
    CG_dbManager.cpp \
    CG_user.cpp \
    CG_board.cpp \
    CG_square.cpp \
    CG_pawn.cpp \
    CG_bishop.cpp \
    CG_knight.cpp \
    CG_rook.cpp \
    CG_queen.cpp \
    CG_piece.cpp \
    CG_king.cpp \
    CG_history.cpp \
    CG_serverConnection.cpp \
    CG_pieceImage.cpp

HEADERS  += \
    CG_validator.h \
    CG_dbManager.h \
    CG_user.h \
    CG_piece.h \
    CG_square.h \
    CG_board.h \
    CG_rook.h \
    CG_bishop.h \
    CG_queen.h \
    CG_pawn.h \
    CG_knight.h \
    CG_king.h \
    CG_history.h \
    CG_serverConnection.h \
    CG_pieceImage.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    android/AndroidManifest.xml \
    images/Flags.svg \
    images/cg_flag_turkey.jpg \
    Sounds/gameStarted.mp3 \
    Sounds/resign.mp3

DISTFILES +=
