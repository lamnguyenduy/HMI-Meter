#include "tst_VehicleData.h"

void TestVehicleData::testGetSpeed() {
    VehicleData data;
    float speed = data.getSpeed();
    QVERIFY2(speed >= 0.0f && speed <= 200.0f, "Tốc độ phải nằm trong khoảng [0, 200] km/h");
}

void TestVehicleData::testGetFuelLevel() {
    VehicleData data;
    float fuel = data.getFuelLevel();
    QVERIFY2(fuel >= 0.0f && fuel <= 100.0f, "Mức nhiên liệu phải nằm trong khoảng [0, 100]%");
}

void TestVehicleData::testGetTemperature() {
    VehicleData data;
    float temp = data.getEngineTemp();
    QVERIFY2(temp >= 0.0f && temp <= 150.0f, "Nhiệt độ phải nằm trong khoảng [0, 150]°C");
}

void TestVehicleData::testGetWarnings() {
    VehicleData data;
    std::array<bool, 3> warnings = data.getWarnings();
    QVERIFY2(warnings.size() == 3, "Mảng cảnh báo phải có 3 phần tử");
}

QTEST_MAIN(TestVehicleData)
