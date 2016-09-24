#-------------------------------------------------
#
# Project created by QtCreator 2012-11-13T12:04:30
#
#-------------------------------------------------

QT       += core gui network

TARGET = gametracker
TEMPLATE = lib

SOURCES += gametracker.cpp

HEADERS += gametracker.h

win32 {
    LIBS += -L$$PWD -lRoccatPowerGrid
	LIBS += "planetside_api_client.lib"
}

OTHER_FILES += \
    ../gametracker.qs \
    ../info.json \
    ../meta.json \
    ../plugin.json \
    ../gametracker.ctrlset.json

