#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T14:30:07
#
#-------------------------------------------------

QT       += core gui network opengl
QT       += webkitwidgets webkit
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wifibot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connexion.cpp \
    communication.cpp

HEADERS  += mainwindow.h \
    connexion.h \
    communication.h

FORMS    += mainwindow.ui \
        connexion.ui


unix {
message("Using unix configuration")
LIBS += `pkg-config --libs opencv`
}

INCLUDEPATH += /usr/local/include/opencv \
               /usr/local/include

message("OpenCV path: $$OPENCV_PATH")
message("Includes path: $$INCLUDEPATH")
message("Libraries: $$LIBS")
