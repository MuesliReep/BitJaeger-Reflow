#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T00:06:10
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = BitJaeger-Reflow
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        qcustomplot.cpp \
    profile.cpp \
    program.cpp \
    config.cpp \
    pid.cpp \
    updatepacket.cpp \
    ovencontroller.cpp \
    logging.cpp \
    options.cpp

HEADERS  += mainwindow.h\
            qcustomplot.h \
    profile.h \
    program.h \
    config.h \
    pid.h \
    updatepacket.h \
    ovencontroller.h \
    logging.h \
    options.h


FORMS    += mainwindow.ui \
    options.ui
