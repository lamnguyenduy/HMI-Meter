#ifndef TST_HMICONTROLLER_H
#define TST_HMICONTROLLER_H

#include <QTest>
#include "HMIController.h"
#include <array>

#include "VehicleData.h"

class MockVehicleData : public VehicleData {
public:
    float getSpeed() const override {
        qDebug() << "HARRY MockVehicleData getSpeed";
        return 120.0f;
    }
    float getFuelLevel() const override { return 60.0f; }
    float getEngineTemp() const override { return 100.0f; }
    std::array<bool, 3> getWarnings() const override { return {true, false, true}; }
};

class TestHMIController : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testUpdateInterface();

private:
    HMIDisplay* display{nullptr};
    MockVehicleData* vehicleData{nullptr};
    HMIController* controller{nullptr};
};

#endif // TST_HMICONTROLLER_H
