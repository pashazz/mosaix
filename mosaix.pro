# -------------------------------------------------
# Project created by QtCreator 2009-06-04T15:57:00
# -------------------------------------------------
QT += webkit \
    sql
TARGET = mosaix
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mxloader.cpp \
    mxcoremethods.cpp \
    mxbuttonconf.cpp \
    mxdownloadinterface.cpp \
    mxhtlprop.cpp \
    sqliteworker.cpp \
    mxinput.cpp \
    aboutdialog.cpp \
    hotlink.cpp \
    networkdiskcache.cpp \
    networkcookiejar.cpp \
    networkaccessmanager.cpp \
    authenticationdialog.cpp \
    webpage.cpp \
    webhistoryitem.cpp \
    webhistory.cpp \

HEADERS += mainwindow.h \
    mxloader.h \
    config.h \
    MXSettings.h \
    mxcoremethods.h \
    mxbuttonconf.h \
    mxdownloadinterface.h \
    mxhtlprop.h \
    sqliteworker.h \
    mxinput.h \
    aboutdialog.h \
    hotlink.h \
    networkdiskcache.h \
    networkcookiejar.h \
    networkaccessmanager.h \
    authenticationdialog.h \
    webpage.h \
    webhistoryitem.h \
    webhistory.h \
FORMS += mainwindow.ui \
    mxbuttonconf.ui \
    mxhtlprop.ui \
    mxinput.ui \
    aboutdialog.ui \
    authenticationdialog.ui
RESOURCES += icons.qrc
