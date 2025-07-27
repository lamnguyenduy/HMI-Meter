#include "HMIDisplay.h"
#include "ui_HMIDisplay.h"

HMIDisplay::HMIDisplay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HMIDisplay)
{
    ui->setupUi(this);
}

HMIDisplay::~HMIDisplay()
{
    delete ui;
}
