QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $${PWD}/../../src/view

SOURCES += \
    ../../src/view\HMIDisplay.cpp \
    tst_HMIDisplay.cpp \

HEADERS += \
    ../../src/view\HMIDisplay.h \
    tst_HMIDisplay.h \

FORMS += \
    ../../src/view/HMIDisplay.ui
