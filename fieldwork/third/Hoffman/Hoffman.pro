#-------------------------------------------------
#
# Project created by QtCreator 2017-10-27T23:27:48
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hoffman
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    mainwindow.cpp \
    lib/framlessHelper/qwidget/framelesshelper.cpp \
    encoder.cpp \
    decoder.cpp \
    encodedialog.cpp \
    filecoverdialog.cpp \
    lib/logHelper/loghelper.cpp \
    decodedialog.cpp

HEADERS += \
    mainwindow.h \
    lib/framlessHelper/qwidget/framelesshelper.h \
    encoder.h \
    decoder.h \
    encodedialog.h \
    filecoverdialog.h \
    lib/logHelper/loghelper.h \
    decodedialog.h

FORMS += \
    mainwindow.ui \
    mainwindow.ui \
    encodedialog.ui \
    decodedialog.ui

RESOURCES += \
    res.qrc
