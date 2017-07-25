#-------------------------------------------------
#
# Project created by QtCreator 2016-12-01T16:18:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLAU
TEMPLATE = app

DEFINES += DEBUG

SOURCES += main.cpp\
        widget.cpp \
    doublespinboxdelegate.cpp \
    matrix_error.cpp

HEADERS  += widget.h \
    matrix.h \
    doublespinboxdelegate.h \
    matrix_error.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++14
