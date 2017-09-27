#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T23:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTSSL_Handshake
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
        mainwindow.cpp \
    ssl.cpp

HEADERS += \
        mainwindow.h \
    ssl.h

FORMS += \
        mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lssl -lcrypto

macx: LIBS += -L$$PWD/../../../../../usr/local/Cellar/openssl/1.0.2l/lib/ -lcrypto

INCLUDEPATH += $$PWD/../../../../../usr/local/Cellar/openssl/1.0.2l/include/openssl
DEPENDPATH += $$PWD/../../../../../usr/local/Cellar/openssl/1.0.2l/include/openssl

macx: PRE_TARGETDEPS += $$PWD/../../../../../usr/local/Cellar/openssl/1.0.2l/lib/libcrypto.a

unix:!macx: LIBS += -lssl.1.0.0

unix|win32: LIBS += -lssl.1.0.0
