#-------------------------------------------------
#
# Project created by QtCreator 2018-07-05T16:17:21
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Poke_renew
TEMPLATE = app
RC_ICONS=main.ico
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    helpchoose.cpp \
    needhelp.cpp \
    base64.cpp \
    chatscreen.cpp \
    loginscreen.cpp \
    mediaplayer.cpp \
    network.cpp \
    poke.cpp \
    helpothers.cpp \
    commandline.cpp
HEADERS += \
    helpchoose.h \
    needhelp.h \
    base64.h \
    chatscreen.h \
    loginscreen.h \
    mediaplayer.h \
    network.h \
    poke.h \
    helpothers.h \
    commandline.h
FORMS += \
    helpchoose.ui \
    needhelp.ui \
    chatscreen.ui \
    loginscreen.ui \
    mediaplayer.ui \
    network.ui \
    poke.ui \
    helpothers.ui \
    commandline.ui
