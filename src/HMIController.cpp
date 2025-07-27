#include "HMIController.h"
#include "HMIDisplay.h"
#include "VehicleData.h" // Giả định lớp VehicleData
#include <QTimer>

#include <QDebug>
#include <QDir>
#include <QCoreApplication>

const static QString strInputData = QString(PROJECT_DIR) + "/data/vehicle_data.txt";

HMIController::HMIController(HMIDisplay* display, VehicleData* data, QObject* parent)
    : QObject(parent), display(display), vehicleData(data) {
    // MISRA: Kiểm tra con trỏ null
    if (!display || !vehicleData) {
        return; // ISO 26262: Ngăn crash
    }

    // Khởi tạo timer cập nhật mỗi 100ms
    updateTimer = new QTimer(this);
    updateTimer->setInterval(1000); // NFUN-002: Cập nhật <100ms
    connect(updateTimer, &QTimer::timeout, this, &HMIController::updateInterface);
    updateTimer->start();
}

void HMIController::updateInterface() {
    // MISRA: Kiểm tra con trỏ null
    if (!display || !vehicleData) {
        return; // ISO 26262: Ngăn crash
    }

    vehicleData->updateData(false);
    // vehicleData->updateData(true, strInputData);

    // Lấy dữ liệu từ VehicleData
    float speed = vehicleData->getSpeed(); // km/h, 0-200
    float fuel = vehicleData->getFuelLevel(); // %, 0-100
    float temp = vehicleData->getEngineTemp(); // °C, 0-150
    std::array<bool, 3> warnings = vehicleData->getWarnings(); // [lỗi động cơ, nhiên liệu thấp, nhiệt độ cao]

    // Xác thực dữ liệu (ISO 26262: Đảm bảo an toàn)
    speed = std::max(0.0f, std::min(200.0f, speed));
    fuel = std::max(0.0f, std::min(100.0f, fuel));
    temp = std::max(0.0f, std::min(150.0f, temp));

    // Cập nhật giao diện
    display->updateDisplay(speed, fuel, temp, warnings);
}
