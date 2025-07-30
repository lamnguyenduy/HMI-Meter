QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PROJECT_DIR=\\\"$$PWD\\\"

SOURCES += \
    HMIController.cpp \
    VehicleData.cpp \
    main.cpp \
    HMIDisplay.cpp \
    tests/tstHMIDisplay.cpp \
    tests/tst_HMIController.cpp \
    tests/tst_VehicleData.cpp

HEADERS += \
    HMIController.h \
    HMIDisplay.h \
    VehicleData.h \
    tests/tst_HMIController.h \
    tests/tst_HMIDisplay.h \
    tests/tst_VehicleData.h

FORMS += \
    HMIDisplay.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
