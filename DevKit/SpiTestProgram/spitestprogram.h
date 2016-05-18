#ifndef SPITESTPROGRAM_H
#define SPITESTPROGRAM_H

#include <QWidget>
#include <QString>
#include "spiapi.h"

namespace Ui {
class SpiTestProgram;
}

class SpiTestProgram : public QWidget
{
    Q_OBJECT

public:
    explicit SpiTestProgram(QWidget *parent = 0);
    ~SpiTestProgram();

private slots:
    void on_pbRedOn_clicked();
    void on_pbRedOff_clicked();
    void on_pbGreenOn_clicked();
    void on_pbGreenOff_clicked();
    void on_pbBlueOn_clicked();
    void on_pbBlueOff_clicked();
    void on_pbReslutat_clicked();
    void on_pbClear_clicked();

private:
    Ui::SpiTestProgram *ui;
};

#endif // SPITESTPROGRAM_H
