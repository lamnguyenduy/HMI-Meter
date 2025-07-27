#ifndef HMIDISPLAY_H
#define HMIDISPLAY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class HMIDisplay;
}
QT_END_NAMESPACE

class HMIDisplay : public QWidget
{
    Q_OBJECT

public:
    HMIDisplay(QWidget *parent = nullptr);
    ~HMIDisplay();

private:
    Ui::HMIDisplay *ui;
};
#endif // HMIDISPLAY_H
