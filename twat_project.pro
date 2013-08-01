#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:36:57
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = twat_project
OBJECTS_DIR = ./obj
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += src


SOURCES += src/core/main.cpp\
	src/windows/mainwindow.cpp \
    src/core/client.cpp \
    src/core/shared/config.cpp \
    src/base/system.cpp \
    src/core/shared/io_file.cpp \
    src/windows/ui_elements.cpp \
    src/ui/ui_elements/menubutton.cpp


HEADERS  += src/windows/mainwindow.h \
    src/core/client.h \
    src/core/shared/config.h \
    src/core/shared/config_vars.h \
    src/base/app_info.h \
    src/base/sys_lookup.h \
    src/base/system.h \
    src/core/shared/io_file.h \
    src/ui/ui_elements/menubutton.h

FORMS    += src/ui/ui_layouts/mainwindow.ui

RESOURCES += \
    data/ressources.qrc
