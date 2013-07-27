#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:36:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = twat_project
TEMPLATE = app


SOURCES += src/core/main.cpp\
	src/windows/mainwindow.cpp \
    src/core/client.cpp \
    src/core/shared/config.cpp

HEADERS  += src/windows/mainwindow.h \
    src/core/client.h \
    src/core/shared/config.h

FORMS    += src/ui_layouts/mainwindow.ui
