/*!
 * @file        maindisplay.h
 * @brief       Handles all UI-related in maindisplay including all tabs
 * @class       MainDisplay
 * @author      Victor Busk (201409557@post.au.dk)
 */

#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QWidget>
#include <QApplication>
#include "spiapi.h"

namespace Ui {
class MainDisplay;
}

class MainDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

private slots:
    void on_PosChanged();
    void on_ColorChanged();
    void on_upButton_pressed();
    void on_downButton_pressed();
    void on_goPosButton_pressed();
    void on_goLightButton_pressed();
    void on_onButton_pressed();
    void on_offButton_pressed();
    void on_addButton_pressed();
    void on_button_pressed();
    void on_delButton_pressed();
    void on_distanceChanged();
    void on_movementChanged();
    void on_lumenChanged();

private:
    Ui::MainDisplay *ui;
    QColor rgbColor;
    SPIapi setSendPos;
    SPIapi setLight;
    SPIapi setSensor;

};

#endif // MAINDISPLAY_H

/* [] END OF FILE */
