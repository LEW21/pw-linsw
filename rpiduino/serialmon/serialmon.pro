TEMPLATE = lib
CONFIG += qt plugin
QT += qml serialport concurrent
CONFIG += c++11

DESTDIR = imports/Synergy
TARGET = qmlsynergyplugin

HEADERS += SerialMonitor.h
SOURCES += SerialMonitor.cpp
