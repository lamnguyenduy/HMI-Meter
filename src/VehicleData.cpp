#include "VehicleData.h"
#include <QFile>
#include <QTextStream>
#include <random>
#include <ctime>

#include <QDebug>

void VehicleData::updateData(bool useCsv, const QString& csvPath) {
    if (useCsv && !csvPath.isEmpty()) {
        QFile file(csvPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            static QTextStream in(&file); // keep as static varible to save current line => change to next line data
            // Skip header if exists
            if (!in.atEnd()) {
                in.readLine(); // Assume first line is header
            }
            // Read one line of data
            if (!in.atEnd()) {
                QString line = in.readLine();
                QStringList fields = line.split(" ");
                if (fields.size() >= 4) {
                    speed = fields[0].toFloat();
                    fuelLevel = fields[1].toFloat();
                    engineTemp = fields[2].toFloat();
                    engineFault = (fields[3].toInt() != 0);
                }
            }
            file.close();
        } else {
            // Fallback to random if file fails
            useCsv = false;
        }
    }

    if (!useCsv) {
        // Generate random data
        static std::mt19937 rng(static_cast<unsigned>(time(nullptr))); // MISRA: Seed random
        std::uniform_real_distribution<float> speedDist(0.0f, 200.0f);
        std::uniform_real_distribution<float> fuelDist(0.0f, 100.0f);
        std::uniform_real_distribution<float> tempDist(0.0f, 150.0f);
        std::uniform_int_distribution<int> faultDist(0, 1);

        speed = speedDist(rng);
        fuelLevel = fuelDist(rng);
        engineTemp = tempDist(rng);
        engineFault = (faultDist(rng) == 1);
    }

    validateData(); // Validate after updating
}

void VehicleData::validateData() {
    // Ensure data within valid ranges (ISO 26262: Handle abnormal data)
    speed = std::max(0.0f, std::min(200.0f, speed));
    fuelLevel = std::max(0.0f, std::min(100.0f, fuelLevel));
    engineTemp = std::max(0.0f, std::min(150.0f, engineTemp));

    // Process warnings
    lowFuelWarning = (fuelLevel < 10.0f);
    highTempWarning = (engineTemp > 120.0f);

    qDebug() << "HARRY speed:"<<speed;
    qDebug() << "HARRY fuelLevel:"<<fuelLevel;
    qDebug() << "HARRY engineTemp:"<<engineTemp;
    qDebug() << "HARRY engineFault:"<<engineFault;
    qDebug() << "HARRY lowFuelWarning:"<<lowFuelWarning;
    qDebug() << "HARRY highTempWarning:"<<highTempWarning;
}

float VehicleData::getSpeed() const {
    return speed;
}

float VehicleData::getFuelLevel() const {
    return fuelLevel;
}

float VehicleData::getEngineTemp() const {
    return engineTemp;
}

std::array<bool, 3> VehicleData::getWarnings() const {
    return {engineFault, lowFuelWarning, highTempWarning};
}
