QT += core
QT -= gui

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_DEBUG += -O0 -std=c++11

TARGET = AVLTree
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    avltree.h

