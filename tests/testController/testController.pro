QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $${PWD}/../../src/model $${PWD}/../../src/view $${PWD}/../../src/controller

DEFINES += PROJECT_DIR=\\\"$$PWD//..//..\\\"

SOURCES += \
    ../../src/model/VehicleData.cpp \
    ../../src/view/HMIDisplay.cpp \
    ../../src/controller/HMIController.cpp \
    tst_HMIController.cpp \

HEADERS += \
    ../../src/model/VehicleData.h \
    ../../src/view/HMIDisplay.h \
    ../../src/controller/HMIController.h \
    tst_HMIController.h \

FORMS += \
    ../../src/view/HMIDisplay.ui
