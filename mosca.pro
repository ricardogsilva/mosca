#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T20:17:09
#
#-------------------------------------------------

QT       += core
QT       += network


QT       -= gui

TARGET = mosca
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mosca.cpp \
    oscmessage.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += liblo

HEADERS += \
    mosca.h \
    oscmessage.h
