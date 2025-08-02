#include "tst_HMIDisplay.h"
#include "ui_HMIDisplay.h"

void TestHMIDisplay::initTestCase() {
    display = new HMIDisplay();
}

void TestHMIDisplay::cleanupTestCase() {
    delete display;
    display = nullptr;
}

void TestHMIDisplay::testUpdateDisplayValid() {
    display->updateDisplay(100.5f, 75.0f, 90.0f, {false, true, false});
    display->show(); // if not show, all child widgets are always invisible
    QCOMPARE(display->ui->speedLabel->text(), QString("100.5 km/h"));
    QCOMPARE(display->ui->fuelBar->value(), 75);
    QCOMPARE(display->ui->tempLabel->text(), QString("90 ℃"));
    QVERIFY(!display->ui->engineFaultIcon->isVisible());
    QVERIFY(display->ui->lowFuelIcon->isVisible());
    QVERIFY(!display->ui->highTempIcon->isVisible());
}

void TestHMIDisplay::testUpdateDisplayBoundary() {
    // Kiểm tra giá trị biên
    display->updateDisplay(250.0f, 150.0f, 200.0f, {true, true, true});
    display->show(); // if not show, all child widgets are always invisible
    QCOMPARE(display->ui->speedLabel->text(), QString("200.0 km/h")); // Cắt bớt tại 200
    QCOMPARE(display->ui->fuelBar->value(), 100); // Cắt bớt tại 100
    QCOMPARE(display->ui->tempLabel->text(), QString("150 ℃")); // Cắt bớt tại 150
    QVERIFY(display->ui->engineFaultIcon->isVisible());
    QVERIFY(display->ui->lowFuelIcon->isVisible());
    QVERIFY(display->ui->highTempIcon->isVisible());
}

void TestHMIDisplay::testUpdateDisplayWarnings() {
    // Kiểm tra thay đổi màu thanh nhiên liệu và nhiệt độ
    display->updateDisplay(50.0f, 5.0f, 130.0f, {false, false, false});
    QString fuelStyle = display->ui->fuelBar->styleSheet();
    QString tempStyle = display->ui->tempLabel->styleSheet();
    QVERIFY(fuelStyle.contains("#FFCA28")); // Vàng khi nhiên liệu <10%
    QVERIFY(tempStyle.contains("#F44336")); // Đỏ khi nhiệt độ >120°C
}

void TestHMIDisplay::testResponseTime() {
    QElapsedTimer timer;
    timer.start();
    display->updateDisplay(100.5f, 75.0f, 90.0f, {false, true, false});
    qint64 elapsed = timer.elapsed();
    qDebug() << "HARRY testResponseTime:"<<elapsed;
    QVERIFY2(elapsed < 100, QString("Thời gian phản hồi của updateDisplay: %1ms, vượt quá 100ms").arg(elapsed).toUtf8().constData());
}

QTEST_MAIN(TestHMIDisplay)
