QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

contains(CONFIG, debug) {
    DESTDIR = ./bin/debug
} else:contains(CONFIG, release) {
    DESTDIR = ./bin/release
}

OBJECTS_DIR = ./out/obj
MOC_DIR = ./out/moc
RCC_DIR = ./out/rcc
UI_DIR = ./out/ui

INCLUDEPATH += $${PWD}/../../src/view

SOURCES += \
    ../../src/view\HMIDisplay.cpp \
    tst_HMIDisplay.cpp \

HEADERS += \
    ../../src/view\HMIDisplay.h \
    tst_HMIDisplay.h \

FORMS += \
    ../../src/view/HMIDisplay.ui
