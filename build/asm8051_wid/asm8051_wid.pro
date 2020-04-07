#-------------------------------------------------
#
# Project created by QtCreator 2020-04-04T15:30:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = asm8051_wid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    csv_io.cpp \
    ../../src/asm8051.cpp \
    ../../src/asm_context.cpp \
    ../../src/hex_generator.cpp \
    ../../src/asm_keywords.cpp \
    ../../src/asm8051_lex.cpp \
    ../../src/text_block.cpp \
    ../../src/trim.cpp \
    ../../src/split.cpp \
    ../../src/replace.cpp \
    ../../src/dis8051.cpp \
    ../../src/asm_table.cpp \
    ../../test/asm_test_code_gen.cpp \
    codegenwid.cpp

HEADERS  += mainwindow.h \
    csv_io.h \
    ../../src/asm8051.h \
    ../../src/asm_context.h \
    ../../src/hex_generator.h \
    ../../src/asm_keywords.h \
    ../../src/asm8051_lex.h \
    ../../src/text_block.h \
    ../../src/trim.h \
    ../../src/split.h \
    ../../src/replace.h \
    ../../src/dis8051.h \
    ../../src/asm_table.h \
    ../../test/asm_test_code_gen.h \
    codegenwid.h

INCLUDEPATH +=../../src/ ../../test/

FORMS    += mainwindow.ui \
    codegenwid.ui
