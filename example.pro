# Project name
TARGET = apexisocreatorgui

# Required Qt modules
QT += core gui widgets

# Source files
SOURCES += main.cpp
HEADERS += squashfs.h
HEADERS += usb.h
HEADERS += isocreator.h
HEADERS += setupscripts.h


# C++ standard
CONFIG += c++23

RESOURCES += resources.qrc
