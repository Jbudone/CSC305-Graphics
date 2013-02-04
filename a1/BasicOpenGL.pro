#-------------------------------------------------
#
# Project created by QtCreator 2012-09-13T13:41:55
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = BasicOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    basicopenglview.cpp \
    geometry.cpp \
    vector.cpp \
    stream.cpp \
    tokenizer.cpp \
    shader.cpp \
    program.cpp \
    parameter.cpp \
    matrix.cpp \
    openglerror.cpp

HEADERS  += mainwindow.h \
    basicopenglview.h \
    geometry.h \
    vector.h \
    stream.h \
    tokenizer.h \
    shader.h \
    program.h \
    parameter.h \
    matrix.h \
    openglerror.h

FORMS    += mainwindow.ui

mac {
     OBJECTIVE_SOURCES  +=  core_profile_attributes.mm
     LIBS += -framework Foundation -framework Cocoa
} else {
	unix {
		LIBS += -lGLEW
	}
}

win32 {
    INCLUDEPATH += external/include
    LIBS += -lglew32 -L$$_PRO_FILE_PWD_\external\lib
}

