#ifndef TST_VEHICLEDATA_H
#define TST_VEHICLEDATA_H

#include <QTest>
#include "VehicleData.h"
#include <array>

class TestVehicleData : public QObject {
    Q_OBJECT

private slots:
    void testGetSpeed();
    void testGetFuelLevel();
    void testGetTemperature();
    void testGetWarnings();
};

#endif // TST_VEHICLEDATA_H
