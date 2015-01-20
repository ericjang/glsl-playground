#-------------------------------------------------
#
# Project created by QtCreator 2015-01-12T13:20:03
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = glsl-playground
TEMPLATE = app

# OpenGL stuff
# this is necessary for glext to work...
DEFINES += GL_GLEXT_PROTOTYPES

SOURCES += \
    main.cpp \
    glwidget.cpp \
    infopanel.cpp \
    mainwindow.cpp \

HEADERS  += \
    glwidget.h \
    infopanel.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui
