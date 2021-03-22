# -------------------------------------------------
# Project created by QtCreator 2014-07-03T19:37:06
# -------------------------------------------------
QT += network \
    sql
QT -= gui
TARGET = server
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app
SOURCES += main.cpp \
    pripojenie.cpp \
    klienti.cpp \
    klient.cpp
HEADERS += pripojenie.h \
    klienti.h \
    klient.h
