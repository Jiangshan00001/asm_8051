#-------------------------------------------------
#
# Project created by QtCreator 2021-03-09T16:57:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lexpp
TEMPLATE = app

DEFINES += QT_WID

INCLUDEPATH += ../../../../src/misc/util



SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/lex_file_io.cpp \
    ../../src/main_console.cpp \
    ../../src/lex_file_template.cpp

HEADERS  += mainwindow.h \
    ../../src/lex_file_io.h \
    ../../src/main_console.h \
    ../../src/lex_file_template.h

FORMS    += mainwindow.ui
