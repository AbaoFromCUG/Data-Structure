#-------------------------------------------------
#
# Project created by QtCreator 2017-09-17T12:08:38
#
#-------------------------------------------------

QT       += core gui

#预编译处理文件
PRECOMPILED_HEADER = stable.h

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FareyList
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lib/framlessHelper/qwidget/framelesshelper.cpp \
    list/FareyList.cpp

HEADERS  += mainwindow.h \
    lib/framlessHelper/qwidget/framelesshelper.h \
    list/FareyList.h \
    list/SuperList.h \
    stable.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    fareylist.qrc

