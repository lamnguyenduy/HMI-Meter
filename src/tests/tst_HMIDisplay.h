#ifndef TST_HMIDISPLAY_H
#define TST_HMIDISPLAY_H

#include <QTest>
#include "HMIDisplay.h"
#include <array>

class TestHMIDisplay : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testUpdateDisplayValid();
    void testUpdateDisplayBoundary();
    void testUpdateDisplayWarnings();

private:
    HMIDisplay* display{nullptr};
};

#endif // TST_HMIDISPLAY_H
