#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T15:35:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DB-Check
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp dbabstract.cpp \
    mydb.cpp

HEADERS  += widget.h dbabstract.h \
    mydb.h

FORMS    += widget.ui
