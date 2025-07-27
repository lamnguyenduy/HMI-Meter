#ifndef VEHICLE_DATA_H
#define VEHICLE_DATA_H

#include <array>
#include <QString>

class VehicleData {
private:
    float speed{0.0f};         // MISRA: Initialize all variables
    float fuelLevel{0.0f};
    float engineTemp{0.0f};
    bool engineFault{false};
    bool lowFuelWarning{false};
    bool highTempWarning{false};

public:
    VehicleData() = default;   // MISRA: Explicit default constructor
    ~VehicleData() = default;  // MISRA: Explicit destructor

    void updateData(bool useCsv, const QString& csvPath = ""); // Read from CSV or random
    void validateData();       // Check ranges and set warnings
    float getSpeed() const;    // MISRA: Const getters
    float getFuelLevel() const;
    float getEngineTemp() const;
    std::array<bool, 3> getWarnings() const; // [engineFault, lowFuel, highTemp]
};

#endif // VEHICLE_DATA_H
