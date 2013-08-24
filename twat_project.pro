#-------------------------------------------------
#
# Project created by QtCreator 2013-07-27T11:36:57
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = twat_project
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x \
                  -pthread
OBJECTS_DIR = ./obj
INCLUDEPATH += src


client{
SOURCES += $$system("find ./src -name '*.cpp'")
HEADERS += $$system("find ./src -name '*.h'")
FORMS    += $$system("find ./src -name '*.ui'")
RESOURCES += data/ressources.qrc
}
