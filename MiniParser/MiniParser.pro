#-------------------------------------------------
#
# Project created by QtCreator 2012-06-23T12:55:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = MiniParser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    grammar.cpp \
    cppgenerator.cpp \
    test.cpp \
    grammarparser.cpp

HEADERS += \
    grammar.h \
    cppgenerator.h \
    grammarparser.h
