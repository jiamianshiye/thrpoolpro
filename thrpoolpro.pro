TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread
SOURCES += main.c \
    thrpoolPriv.c

HEADERS += \
    thrpoolPriv.h \
    thrpoolPro.h

