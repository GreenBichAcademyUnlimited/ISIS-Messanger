#-------------------------------------------------
#
# Project created by QtCreator 2018-01-07T01:15:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ISIS-Messanger
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startsettings.cpp \
    sockets.cpp \
    enterwidget.cpp \
    sam.cpp

HEADERS  += mainwindow.h \
    startsettings.h \
    sockets.hpp \
    enterwidget.h \
    config.h \
    sam.h

FORMS    +=

#LIBS += 
