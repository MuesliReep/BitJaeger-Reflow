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
    logging.cpp \
    options.cpp \
    ovencontroller.cpp


HEADERS  += mainwindow.h\
            qcustomplot.h \
    profile.h \
    program.h \
    config.h \
    pid.h \
    updatepacket.h \
    logging.h \
    options.h \
    ovencontroller.h



FORMS    += mainwindow.ui \
    options.ui

#-----------------------
#   Remove when done
#-----------------------
SOURCES += D:/Qt5.5/Tools/QtCreator/bin/Serial-Conole/comms.cpp
HEADERS +=D:/Qt5.5/Tools/QtCreator/bin/Serial-Conole/comms.h
INCLUDEPATH += D:/Qt5.5/Tools/QtCreator/bin/Serial-Conole/
