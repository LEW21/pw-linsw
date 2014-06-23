TEMPLATE = lib
CONFIG += qt plugin
QT += qml concurrent
CONFIG += c++11

DESTDIR = imports/Hipsta
TARGET = qmlhipstamouse

HEADERS += HipstaMouse.h
SOURCES += HipstaMouse.cpp
