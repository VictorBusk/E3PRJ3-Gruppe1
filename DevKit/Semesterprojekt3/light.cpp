/*!
 * @file        light.cpp
 * @brief       Handles light
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "maindisplay.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>

/***************************************
 *       Public constants
 ****************************************/

const unsigned char cmdR = 0x30u;
const unsigned char cmdG = 0x31u;
const unsigned char cmdB = 0x32u;

const unsigned char cmdPower = 0x34u;


/*!
 *  @brief      Sets up colorpalette to color preview
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_ColorChanged()
{
    //Opdaterer farvepalette

    rgbColor.setRgb(((ui->redSlider->value())), ((ui->greenSlider->value())), ((ui->blueSlider->value())));
    QPalette pal = ui->colorPalette->palette();
    pal.setColor(QPalette::Window, rgbColor);

    // set line values
    ui->redLine->setText(QString::number(ui->redSlider->value()));
    ui->greenLine->setText(QString::number(ui->greenSlider->value()));
    ui->blueLine->setText(QString::number(ui->blueSlider->value()));

    // set color in palette
    ui->colorPalette->setPalette(pal);

    //Send values
}

/*!
 *  @brief      Increments red-, green- and blue-slider by 5 on Up-Button-pressed event
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_upButton_pressed()
{
    // disables moving all sliders up when one reaches maximum
    // checks if individual sliders have reached maximum

    ui->redSlider->setSliderPosition(ui->redSlider->value() == 255 ? ui->redSlider->value() : ui->redSlider->value() + 5);
    ui->greenSlider->setSliderPosition(ui->greenSlider->value() == 255 ? ui->greenSlider->value() : ui->greenSlider->value() + 5);
    ui->blueSlider->setSliderPosition(ui->blueSlider->value() == 255 ? ui->blueSlider->value() : ui->blueSlider->value() + 5);
}

/*!
 *  @brief      Decrements red-, green- and blue-slider by 5 on Up-Button-pressed event
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_downButton_pressed()
{
    // disables moving all sliders down when one reaches minimum
    // checks if individual sliders have reached minimum
    ui->redSlider->setSliderPosition(ui->redSlider->value() == 0 ? ui->redSlider->value() : ui->redSlider->value() - 5);
    ui->greenSlider->setSliderPosition(ui->greenSlider->value() == 0 ? ui->greenSlider->value() : ui->greenSlider->value() - 5);
    ui->blueSlider->setSliderPosition(ui->blueSlider->value() == 0 ? ui->blueSlider->value() : ui->blueSlider->value() - 5);
}

/*!
 *  @brief      Sends light RGB on Go-Button-pressed event
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_goLightButton_pressed()
{
    unsigned char valR = ui->redSlider->value();
    unsigned char valG = ui->greenSlider->value();
    unsigned char valB = ui->blueSlider->value();

    setLight.setPacket(&cmdR, &valR);
    setLight.setPacket(&cmdG, &valG);
    setLight.setPacket(&cmdB, &valB);
}

/*!
 *  @brief      Turns on light on white light (RGB = 255)
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_onButton_pressed()
{
    unsigned char valOn = 1;

    setSensor.setPacket(&cmdPower, &valOn);

    qDebug() << "Power is on (0=Off & 1=On): " << valOn;

}

/*!
 *  @brief      Turns off light (RGB = 0)
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_offButton_pressed()
{
    unsigned char valOff = 0;

    setSensor.setPacket(&cmdPower, &valOff);

    qDebug() << "Power is off (0=Off & 1=On): " << valOff;
}
/* [] END OF FILE */


