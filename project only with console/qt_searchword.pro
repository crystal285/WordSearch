#-------------------------------------------------
#
# Project created by QtCreator 2013-12-02T22:47:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_searchword
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trieTree.cpp \
    searchWordAlgorithm.cpp \
    node.cpp \
    concretesearch.cpp \
    abstractsearch.cpp

HEADERS  += mainwindow.h \
    searchWordAlgorithm.h \
    trieTree.h \
    node.h \
    concretesearch.h \
    abstractsearch.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    dict.txt
