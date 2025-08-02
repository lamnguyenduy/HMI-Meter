#include "tst_HMIController.h"
#include "HMIDisplay.h"
#include "ui_HMIDisplay.h"

void TestHMIController::initTestCase() {
    display = new HMIDisplay();
    vehicleData = new MockVehicleData();
    controller = new MockHMIController(display, vehicleData);
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
    QTest::qWait(150);

    display->show();

    // Kiểm tra giao diện được cập nhật từ MockVehicleData
    QCOMPARE(display->ui->speedLabel->text(), QString("120.0 km/h"));
    QCOMPARE(display->ui->fuelBar->value(), 60);
    QCOMPARE(display->ui->tempLabel->text(), QString("100 ℃"));
    QVERIFY(display->ui->engineFaultIcon->isVisible());
    QVERIFY(!display->ui->lowFuelIcon->isVisible());
    QVERIFY(display->ui->highTempIcon->isVisible());
}

void TestHMIController::testUpdateInterfaceTimer()
{
    QTest::qWait(300);
    MockHMIController *mockHMIController = static_cast<MockHMIController *>(controller); // sure the type is MockHMIController *, don't neeed to use dynamic_cast
    qDebug() << "HARRY testUpdateInterfaceTimer callCount:"<<mockHMIController->callCount;
    qDebug() << "HARRY testUpdateInterfaceTimer elapsed:"<<mockHMIController->elapsed;

    QCOMPARE(mockHMIController->callCount, 5);
    QVERIFY2(mockHMIController->elapsed >= 500 && mockHMIController->elapsed <= 550, "The elapsed time should be from 500 to 550 ms");
}

QTEST_MAIN(TestHMIController)
