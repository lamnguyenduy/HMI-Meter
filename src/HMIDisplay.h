#ifndef HMI_DISPLAY_H
#define HMI_DISPLAY_H

#include <array>
#include <QWidget>

namespace Ui {
class HMIDisplay;
}

class HMIDisplay : public QWidget {
    Q_OBJECT

private:
    Ui::HMIDisplay* ui{nullptr}; // Con trỏ đến đối tượng UI

public:
    explicit HMIDisplay(QWidget* parent = nullptr);
    ~HMIDisplay() override;

    void updateDisplay(float speed, float fuel, float temp, const std::array<bool, 3>& warnings);
};

#endif // HMI_DISPLAY_H
