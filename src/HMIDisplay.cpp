#include "HMIDisplay.h"
#include "ui_HMIDisplay.h"

#include <QDebug>

HMIDisplay::HMIDisplay(QWidget* parent) : QWidget(parent), ui(new Ui::HMIDisplay) {
    ui->setupUi(this); // Tải giao diện từ HMIDisplay.ui
    setFixedSize(800, 480); // Đảm bảo kích thước 480x800 cho TFT

    QPixmap pixmapEF(":/icons/engine_fault.png");
    QPixmap pixmapLF(":/icons/low_fuel.png");
    QPixmap pixmapHT(":/icons/high_temp.png");

    ui->engineFaultIcon->setPixmap(pixmapEF.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lowFuelIcon->setPixmap(pixmapLF.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->highTempIcon->setPixmap(pixmapHT.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

HMIDisplay::~HMIDisplay() {
    delete ui; // Giải phóng đối tượng UI
}

void HMIDisplay::updateDisplay(float speed, float fuel, float temp, const std::array<bool, 3>& warnings) {
    // Cập nhật tốc độ
    ui->speedLabel->setText(QString("%1 km/h").arg(std::max(0.0f, std::min(200.0f, speed)), 0, 'f', 1));

    // Cập nhật thanh nhiên liệu và cảnh báo
    ui->fuelBar->setValue(static_cast<int>(std::max(0.0f, std::min(100.0f, fuel))));
    ui->fuelBar->setStyleSheet(fuel < 10.0f ?
                                   "QProgressBar { background-color: #B0BEC5; border: 1px solid #B0BEC5; } "
                                   "QProgressBar::chunk { background-color: #FFCA28; }" :
                                   "QProgressBar { background-color: #B0BEC5; border: 1px solid #B0BEC5; } "
                                   "QProgressBar::chunk { background-color: #00C4B4; }");

    // Cập nhật thanh nhiệt độ và cảnh báo
    ui->tempLabel->setText(QString("%1 ℃").arg(static_cast<int>(std::max(0.0f, std::min(150.0f, temp)))));

    ui->tempLabel->setStyleSheet(temp > 120.0f ? "color: #F44336;font-size: 24px;" : "color: #0288D1;font-size: 24px;");

    // Cập nhật hiển thị đèn cảnh báo
    ui->engineFaultIcon->setVisible(warnings[0]); // Lỗi động cơ
    ui->lowFuelIcon->setVisible(warnings[1]); // Nhiên liệu thấp
    ui->highTempIcon->setVisible(warnings[2]); // Nhiệt độ cao
}
