#-------------------------------------------------
#
# Project created by QtCreator 2021-03-09T20:08:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG +=C++11

TARGET = asm_csv_to_code
TEMPLATE = app


DEFINES += QT_WID

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/csv_io.cpp \
    ../../src/main_console.cpp \
    ../../src/replace.cpp \
    ../../src/split.cpp \
    ../../src/trim.cpp \
    ../../src/csv_to_csv.cpp \
    ../../src/csv_to_dis.cpp \
    ../../src/csv_to_asmc.cpp \
    ../../src/csv_to_genasm.cpp

HEADERS  += mainwindow.h \
    ../../src/csv_io.h \
    ../../src/main_console.h \
    ../../src/replace.h \
    ../../src/split.h \
    ../../src/trim.h \
    ../../src/csv_to_csv.h \
    ../../src/csv_to_dis.h \
    ../../src/csv_to_asmc.h \
    ../../src/csv_to_genasm.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../../src/Makefile
