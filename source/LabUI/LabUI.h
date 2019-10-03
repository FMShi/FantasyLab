#ifndef LABUI_H
#define LABUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LabUI; }
QT_END_NAMESPACE

class LabUI : public QMainWindow
{
    Q_OBJECT

public:
    LabUI(QWidget *parent = nullptr);
    void closeButtonClicked();
    ~LabUI();

private:
    Ui::LabUI *ui;
};
#endif // LABUI_H
