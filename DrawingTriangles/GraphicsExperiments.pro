#-------------------------------------------------
#
# Project created by QtCreator 2014-03-18T20:16:15
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = GraphicsExperiments
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += /home/dushy/eigen-3.2.1/


unix:!macx:!symbian: LIBS += -L /home/dushy/glew-1.10.0/lib/ -lGLEW

INCLUDEPATH += /home/dushy/glew-1.10.0/include
DEPENDPATH += /home/dushy/glew-1.10.0/include

unix:!macx:!symbian: PRE_TARGETDEPS += /home/dushy/glew-1.10.0/lib/libGLEW.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lglut
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lglut
else:symbian: LIBS += -lglut
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lglut

INCLUDEPATH += $$PWD/../../../../usr/include/GL
DEPENDPATH += $$PWD/../../../../usr/include/GL

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/release/glut.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/debug/glut.lib
else:unix:!symbian: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libglut.a

OTHER_FILES += \
    SampleVertexShader.glsl \
    SampleFragmentShader.glsl
