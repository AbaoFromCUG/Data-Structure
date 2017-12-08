#-------------------------------------------------
#
# Project created by QtCreator 2017-12-07T22:29:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = First
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
        lib/logHelper/loghelper.cpp \
    lib/struct/cammap.cpp

HEADERS += \
    mainwindow.h \
    lib/framlessHelper/qwidget/framelesshelper.h \
    lib/logHelper/loghelper.h \
    lib/struct/vmap.h \
    lib/struct/undir_admmap.h \
    lib/struct/undir_admap.h \
    lib/struct/sstack.h \
    lib/struct/squeque.h \
    lib/struct/slist.h \
    lib/struct/dir_admap.h \
    lib/struct/cammap.h \
    lib/struct/ammap.h \
    lib/struct/admap.h


FORMS += \
    mainwindow.ui

RESOURCES += \
    res.qrc
