QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += static


TEMPLATE = app

TARGET       = tadbformatconverter
DESTDIR      = $$PWD
OBJECTS_DIR  = build/obj
MOC_DIR      = build/moc
RCC_DIR      = build/rcc

#Linux
linux-g++ | linux-g++-64 | linux-g++-32 {
    message("Configuration for Linux platforms compilation [TADBVORMATCONVERT.PRO]")
    PLATFORM  = linux
    DEFINES  += LINUX
}

#MacOs
macx-g++ | macx-clang{
    message("Configuration for MacOs platforms compilation [TADBVORMATCONVERT.PRO]")
    PLATFORM = macx
    DEFINES += MAC_OS_SYSTEM
}

#WinOs
win32 | win64 | amd64 {
    message("Configuration for Windows platforms compilation [TADBVORMATCONVERT.PRO]")
    PLATFORM = windows
    DEFINES += WIN_OS
    CONFIG += WIN_OS
}



# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    tadbformatconvert.cpp

HEADERS += \
    tadbformatconvert.h \
    tadbfacedatatypes.h
