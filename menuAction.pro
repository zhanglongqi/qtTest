#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T15:52:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = menuAction
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myQWi.cpp \
    application.cpp \
    statesMachine.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    myQWi.h \
    application.h \
    test.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc

OTHER_FILES +=
