#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T19:37:11
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notepaid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutsoftware.cpp

HEADERS  += mainwindow.h \
    aboutsoftware.h

FORMS    += mainwindow.ui \
    aboutsoftware.ui

RESOURCES += \
    res.qrc
RC_FILE = ico.rc
