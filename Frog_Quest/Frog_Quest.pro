QT       += core gui widgets opengl openglwidgets
#QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = MYGL
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LevelStorage.cpp \
    MusicPlayer.cpp \
    animationcontroller.cpp \
    #level1.cpp \
    #level_1.cpp \
    main.cpp \
    mainwindow.cpp \
    my_gl.cpp \
    timer.cpp \
    Scene1.cpp

HEADERS += \
    animationcontroller.h \
    #level1.h \
    #level_1.h \
    mainwindow.h \
    #/opt/homebrew/Cellar/glfw/3.3.6/include/GLFW \
    my_gl.h \
    timer.h \
    Scene1.h

FORMS += \
    mainwindow.ui \
    Scene1.ui
    #level_1.ui \
    #level1.ui

# Default rules for deployment.

LIBS    +=  -lopengl32
LIBS    += -lglu32
LIBS    += -lgdi32
#LIBS    += -lglfw3
#LIBS    += -LC:/LIBS/glfw/
#LIBS += -LC:/LIBS/glfw/ -lglfw3 -lopengl32

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
