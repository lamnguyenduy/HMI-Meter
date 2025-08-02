#ifndef HMI_CONTROLLER_H
#define HMI_CONTROLLER_H

#include <array>
#include <QObject>

class HMIDisplay;
class VehicleData;
class QTimer;

class HMIController : public QObject {
    Q_OBJECT

private:
    HMIDisplay* display{nullptr};     // Con trỏ đến giao diện hiển thị
    VehicleData* vehicleData{nullptr}; // Con trỏ đến nguồn dữ liệu
    QTimer* updateTimer{nullptr};     // Timer cập nhật giao diện

public:
    explicit HMIController(HMIDisplay* display, VehicleData* data, QObject* parent = nullptr);
    ~HMIController() override = default;

protected slots:
    virtual void updateInterface(); // Cập nhật giao diện từ dữ liệu xe
};

#endif // HMI_CONTROLLER_H
