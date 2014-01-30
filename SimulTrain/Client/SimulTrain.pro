#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T11:43:46
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimulTrain
TEMPLATE = app


SOURCES += main.cpp\
        fenclient.cpp

HEADERS  += fenclient.h

FORMS    += fenclient.ui

CONFIG += mobility
MOBILITY = 

