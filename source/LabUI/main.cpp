#include "LabUI.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LabUI w;
    w.show();
    return a.exec();
}
