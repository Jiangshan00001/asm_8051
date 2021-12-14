#-------------------------------------------------
#
# Project created by QtCreator 2020-06-13T22:17:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ctools
TEMPLATE = app

CONFIG += C++11

DEFINES += QT_WID


SOURCES += main.cpp\
        mainwindow.cpp \
    ./src/bison_file_io.cpp \
    ./src/split.cpp \
    ./src/replace.cpp \
    ./src/main_console.cpp \
    src/yy_file_template.cpp

HEADERS  += mainwindow.h \
    ./src/bison_file_io.h \
    ./src/split.h \
    ./src/replace.h \
    src/yy_file_template.h

INCLUDEPATH += ../../../../asm8051/src/common/  ./src/


FORMS    += mainwindow.ui

OTHER_FILES += \
    readme.txt \
    Makefile
