#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:36:57
#
#-------------------------------------------------

QT       += core gui \
            printsupport #qcustomplot
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = twat_project
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x
OBJECTS_DIR = ./obj
INCLUDEPATH +=  src \
                ..


client{
Q_CUSTOMPLOT_SRC += ../qcustomplot/qcustomplot.cpp
Q_CUSTOMPLOT_HDR += ../qcustomplot/qcustomplot.h

SOURCES +=  $$system("find ./src -name '*.cpp'") \
            $$Q_CUSTOMPLOT_SRC
HEADERS +=  $$system("find ./src -name '*.h'") \
            $$Q_CUSTOMPLOT_HDR
FORMS   +=  $$system("find ./src -name '*.ui'")
RESOURCES += data/ressources.qrc
}
