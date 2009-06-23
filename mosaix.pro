# -------------------------------------------------
# Project created by QtCreator 2009-06-04T15:57:00
# -------------------------------------------------
QT += webkit sql
TARGET = mosaix
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mxloader.cpp \
    mxcoremethods.cpp \
    mxbuttonconf.cpp \
    mxdownloadinterface.cpp \
    mxhtlprop.cpp \
    sqliteworker.cpp
HEADERS += mainwindow.h \
    mxloader.h \
    config.h \
    MXSettings.h \
    mxcoremethods.h \
    mxbuttonconf.h \
    mxdownloadinterface.h \
    mxhtlprop.h \
    sqliteworker.h
FORMS += mainwindow.ui \
    mxbuttonconf.ui \
    mxhtlprop.ui
RESOURCES += icons.qrc
