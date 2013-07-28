#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:36:57
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = twat_project
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x


SOURCES += src/core/main.cpp\
	src/windows/mainwindow.cpp \
    src/core/client.cpp \
    src/core/shared/config.cpp \
    src/base/system.cpp \
    src/core/shared/io_file.cpp


HEADERS  += src/windows/mainwindow.h \
    src/core/client.h \
    src/core/shared/config.h \
    src/core/shared/config_vars.h \
    src/base/app_info.h \
    src/base/sys_lookup.h \
    src/base/system.h \
    src/core/shared/io_file.h

FORMS    += src/ui_layouts/mainwindow.ui
