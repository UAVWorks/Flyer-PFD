#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T17:03:18
#
#-------------------------------------------------

QT       += core gui svg network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qfi_FlyerPFD
TEMPLATE = app

#-------------------------------------------------

win32: DEFINES += WIN32 _WINDOWS _USE_MATH_DEFINES

win32:CONFIG(release, debug|release):    DEFINES += NDEBUG
else:win32:CONFIG(debug, debug|release): DEFINES += _DEBUG

#-------------------------------------------------

INCLUDEPATH += ./ ./FlyerPFD

#-------------------------------------------------

HEADERS += \
    FlyerPFD/LayoutSquare.h \
    FlyerPFD/MainWindow.h \
    FlyerPFD/WidgetADI.h \
    FlyerPFD/WidgetALT.h \
    FlyerPFD/WidgetASI.h \
    FlyerPFD/WidgetHSI.h \
    FlyerPFD/WidgetNAV.h \
    FlyerPFD/WidgetPFD.h \
    FlyerPFD/WidgetTC.h \
    FlyerPFD/WidgetVSI.h \
    qfi_ADI.h \
    qfi_HSI.h \
    qfi_NAV.h \
    qfi_PFD.h \
    qfi_VSI.h \
    qfi_ASI.h \
    qfi_ALT.h \
    qfi_TC.h \
    FlyerPFD/WidgetSix.h

SOURCES += \
    FlyerPFD/LayoutSquare.cpp \
    FlyerPFD/main.cpp \
    FlyerPFD/MainWindow.cpp \
    FlyerPFD/WidgetADI.cpp \
    FlyerPFD/WidgetALT.cpp \
    FlyerPFD/WidgetASI.cpp \
    FlyerPFD/WidgetHSI.cpp \
    FlyerPFD/WidgetNAV.cpp \
    FlyerPFD/WidgetPFD.cpp \
    FlyerPFD/WidgetTC.cpp \
    FlyerPFD/WidgetVSI.cpp \
    qfi_ADI.cpp \
    qfi_HSI.cpp \
    qfi_NAV.cpp \
    qfi_PFD.cpp \
    qfi_VSI.cpp \
    qfi_ASI.cpp \
    qfi_ALT.cpp \
    qfi_TC.cpp \
    FlyerPFD/WidgetSix.cpp

FORMS += \
    FlyerPFD/MainWindow.ui \
    FlyerPFD/WidgetADI.ui \
    FlyerPFD/WidgetALT.ui \
    FlyerPFD/WidgetASI.ui \
    FlyerPFD/WidgetHSI.ui \
    FlyerPFD/WidgetNAV.ui \
    FlyerPFD/WidgetPFD.ui \
    FlyerPFD/WidgetTC.ui \
    FlyerPFD/WidgetVSI.ui \
    FlyerPFD/WidgetSix.ui

RESOURCES += \
    qfi.qrc
