#include "tst_HMIController.h"
#include "HMIDisplay.h"
#include "ui_HMIDisplay.h"

void TestHMIController::initTestCase() {
    display = new HMIDisplay();
    vehicleData = new MockVehicleData();
    controller = new HMIController(display, vehicleData);
}

void TestHMIController::cleanupTestCase() {
    delete controller;
    delete vehicleData;
    delete display;
    controller = nullptr;
    vehicleData = nullptr;
    display = nullptr;
}

void TestHMIController::testUpdateInterface() {
    // Đợi 100ms để timer kích hoạt
    QTest::qWait(1050);

    display->show();

    // Kiểm tra giao diện được cập nhật từ MockVehicleData
    QCOMPARE(display->ui->speedLabel->text(), QString("120.0 km/h"));
    QCOMPARE(display->ui->fuelBar->value(), 60);
    QCOMPARE(display->ui->tempLabel->text(), QString("100 ℃"));
    QVERIFY(display->ui->engineFaultIcon->isVisible());
    QVERIFY(!display->ui->lowFuelIcon->isVisible());
    QVERIFY(display->ui->highTempIcon->isVisible());
}

QTEST_MAIN(TestHMIController)
