#include "LabUI.h"
#include "./ui_LabUI.h"

LabUI::LabUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LabUI)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}
void LabUI::closeButtonClicked()
{
    QApplication::quit ();
}
LabUI::~LabUI()
{
    delete ui;
}

