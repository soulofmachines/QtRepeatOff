#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T04:26:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRepeatOff
TEMPLATE = app

SOURCES += main.cpp\
widget.cpp

HEADERS  += widget.h

LIBS += -lX11

RESOURCES += images.qrc

CONFIG += qxt

QXT += core gui

unix {

isEmpty(PREFIX) {
PREFIX = /usr/local
}

BINDIR = $$PREFIX/bin

target.path = $$BINDIR

INSTALLS += target

}
