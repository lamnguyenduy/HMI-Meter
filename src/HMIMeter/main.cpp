#include "HMIDisplay.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HMIDisplay w;
    w.show();
    return a.exec();
}
