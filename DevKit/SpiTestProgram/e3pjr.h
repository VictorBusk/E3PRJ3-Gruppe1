#ifndef E3PJR_H
#define E3PJR_H

#include <QTabWidget>
#include <QString>
#include <QShortcutEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include "spiapi.h"

namespace Ui {
class E3PJR;
}

class E3PJR : public QTabWidget
{
    Q_OBJECT

public:
    explicit E3PJR(QWidget *parent = 0);
    ~E3PJR();

private slots:
    void on_pushCalibrateXYZ_clicked();
    void on_pushSetXYZ_clicked();
    void on_pushGetXYZPos_clicked();
    void on_pushGetXYZMax_clicked();


private:
    Ui::E3PJR *ui;
    int spiCount_;
};

#endif // E3PJR_H
