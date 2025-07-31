QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $${PWD}/../../src/model

SOURCES += \
    ../../src/model/VehicleData.cpp \
    tst_VehicleData.cpp \

HEADERS += \
    ../../srcmodel\VehicleData.h \
    tst_VehicleData.h \
