#-------------------------------------------------
#
# Project created by QtCreator 2024-11-29T14:10:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoplayer_lsx
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
LIBS += -L$$PWD/lib/SDL2/lib/x86 \
    -L$$PWD/lib/ffmpeg-4.2.1-win32-dev/lib \
    -lSDL2 \
    -lavcodec \
    -lavdevice \
    -lavfilter \
    -lavformat \
    -lavutil \
    -lswresample \
    -lswscale

INCLUDEPATH += src \
    lib/SDL2/include \
    lib/ffmpeg-4.2.1-win32-dev/include
}

SOURCES += \
        main.cpp \
        mainwid.cpp \
    ctrlbar.cpp \
    show.cpp \
    title.cpp \
    playlist.cpp \
    ffmsg_queue.cpp

HEADERS += \
        mainwid.h \
    ctrlbar.h \
    show.h \
    title.h \
    playlist.h \
    ffmsg_queue.h \
    ff_ffmsg.h

FORMS += \
        mainwid.ui \
    ctrlbar.ui \
    show.ui \
    title.ui \
    playlist.ui

RESOURCES += \
    icon.qrc
