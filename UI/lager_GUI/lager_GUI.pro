#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T14:25:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lager_GUI
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


SOURCES += \
        main.cpp \
        main_window.cpp \
        ../../lib/network/interthreadcom.cpp \
        ../../lib/network/network_socket.cpp \
        ../client_socket.cpp \
        ../command_handler.cpp \
        ../text_file_handler.cpp \
        state_handler.cpp


HEADERS += \
        main_window.h \
        ../../lib/network/interthreadcom.h \
        ../../lib/network/network_socket.h \
        ../client_socket.h \
        ../command_handler.h \
        ../text_file_handler.h \
        state_handler.h

FORMS += \
        main_window.ui


CONFIG += c++11

unix:!macx {
    QMAKE_CXXFLAGS += -pthread
    LIBS += -pthread
}

macx: {
    LIBS += -stdlib=libc++
}

RESOURCES += \
    imgs.qrc
