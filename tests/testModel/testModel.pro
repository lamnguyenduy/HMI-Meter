QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ./bin
OBJECTS_DIR = ./out/obj
MOC_DIR = ./out/moc
RCC_DIR = ./out/rcc
UI_DIR = ./out/ui

INCLUDEPATH += $${PWD}/../../src/model

SOURCES += \
    ../../src/model/VehicleData.cpp \
    tst_VehicleData.cpp \

HEADERS += \
    ../../srcmodel\VehicleData.h \
    tst_VehicleData.h \
