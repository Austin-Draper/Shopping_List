#-------------------------------------------------
#
# Project created by QtCreator 2019-02-21T16:34:34
#
#-------------------------------------------------

QT       += core gui

QT       += sql

INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.17763.132/ucrt"
LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.132/ucrt/x64"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shopping_List
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    workingdatabase.cpp \
    dialog.cpp \
    secdialog.cpp \
    rightsecdialog.cpp \
    rightdeletedialog.cpp

HEADERS += \
        widget.h \
    workingdatabase.h \
    dialog.h \
    secdialog.h \
    rightsecdialog.h \
    rightdeletedialog.h \


FORMS += \
        widget.ui \
    dialog.ui \
    secdialog.ui \
    rightsecdialog.ui \
    rightdeletedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
