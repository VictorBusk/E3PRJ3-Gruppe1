#ifndef POSITION_H
#define POSITION_H

#include <QWidget>
#include <QApplication>
#include <QString>
#include "spiapi.h"
#include <QPushButton>

namespace Ui {
class MainDisplay;
}

class MainDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit MainDisplay(QWidget *parent = 0);
    struct setXYZ
    {
        setXYZ(){}
        setXYZ(quint8 xVal, quint8 yVal, quint8 zVal)
        {
            x = xVal;
            y = yVal;
            z = zVal;
        }

        quint8 x;
        quint8 y;
        quint8 z;
    };

    struct setSliders
    {
        setSliders(){}
        setSliders(quint8 redVal, quint8 blueVal, quint8 greenVal)
        {
            red = redVal;
            green = greenVal;
            blue = blueVal;
        }

        quint8 red;
        quint8 green;
        quint8 blue;
    };

    ~MainDisplay();


private slots:
    void on_PosChanged();
    void on_ColorChanged();
    void on_upButton_pressed();
    void on_downButton_pressed();
    void on_calButton_pressed();
    void on_goPosButton_pressed();
    void on_goLightButton_pressed();
    void on_onButton_pressed();
    void on_offButton_pressed();
    void on_addButton_pressed();
    void on_setTestButton_pressed();
    void on_getTestButton_pressed();

private:
    Ui::MainDisplay *ui;
    QColor rgbColor;
    SPIapi setSendPos;

    unsigned char cmdX = 0x10u;
    unsigned char cmdY = 0x11u;
    unsigned char cmdZ = 0x20u;

    unsigned char cmdR = 0x30u;
    unsigned char cmdG = 0x31u;
    unsigned char cmdB = 0x32u;

};

#endif // POSITION_H
