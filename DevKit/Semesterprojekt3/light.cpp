#include "light.h"
#include "position.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>

void MainDisplay::on_ColorChanged()
{
    //Opdaterer farvepalette
    MainDisplay::setSliders *setSlidersPtr = new setSliders((ui->redSlider->value()), (ui->greenSlider->value()), (ui->blueSlider->value()));

    qDebug() << "Color values: " << setSlidersPtr->red << "," << setSlidersPtr->green << "," << setSlidersPtr->blue;

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

void MainDisplay::on_upButton_pressed()
{
    // disables moving all sliders up when one reaches maximum
    // checks if individual sliders have reached maximum

    ui->redSlider->setSliderPosition(ui->redSlider->value() == 99 ? ui->redSlider->value() : ui->redSlider->value() + 1);
    ui->greenSlider->setSliderPosition(ui->greenSlider->value() == 99 ? ui->greenSlider->value() : ui->greenSlider->value() + 1);
    ui->blueSlider->setSliderPosition(ui->blueSlider->value() == 99 ? ui->blueSlider->value() : ui->blueSlider->value() + 1);

    on_ColorChanged();
}

void MainDisplay::on_downButton_pressed()
{
    // disables moving all sliders down when one reaches minimum
    // checks if individual sliders have reached minimum
    ui->redSlider->setSliderPosition(ui->redSlider->value() == 0 ? ui->redSlider->value() : ui->redSlider->value() - 1);
    ui->greenSlider->setSliderPosition(ui->greenSlider->value() == 0 ? ui->greenSlider->value() : ui->greenSlider->value() - 1);
    ui->blueSlider->setSliderPosition(ui->blueSlider->value() == 0 ? ui->blueSlider->value() : ui->blueSlider->value() - 1);

    on_ColorChanged();
}

void MainDisplay::on_goLightButton_pressed()
{
    SPIapi setLight;

    unsigned char cmdR = 0x21;
    unsigned char cmdG = 0x22;
    unsigned char cmdB = 0x23;

    unsigned char valR = ui->redSlider->value();
    unsigned char valG = ui->greenSlider->value();
    unsigned char valB = ui->blueSlider->value();

    setLight.setPacket(&cmdR, &valR);
    setLight.setPacket(&cmdG, &valG);
    setLight.setPacket(&cmdB, &valB);

    on_ColorChanged();
}


void MainDisplay::on_onButton_pressed()
{
    SPIapi redOn;
    SPIapi greenOn;
    SPIapi blueOn;

    unsigned char cmdR = 0x21;
    unsigned char cmdG = 0x22;
    unsigned char cmdB = 0x23;

    unsigned char On = 0xff;

    redOn.setPacket(&cmdR, &On);
    greenOn.setPacket(&cmdG, &On);
    blueOn.setPacket(&cmdB, &On);

    qDebug() << "On button pressed: ";

    on_ColorChanged();
}

void MainDisplay::on_offButton_pressed()
{
    SPIapi redOff;
    SPIapi greenOff;
    SPIapi blueOff;

    unsigned char cmdR = 0x21;
    unsigned char cmdG = 0x22;
    unsigned char cmdB = 0x23;

    unsigned char Off = 0x00;

    redOff.setPacket(&cmdR, &Off);
    greenOff.setPacket(&cmdG, &Off);
    blueOff.setPacket(&cmdB, &Off);
}


