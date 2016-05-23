#include "maindisplay.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>

const unsigned char cmdLumen = 0x33u;
const unsigned char cmdDistance = 0x40u;
const unsigned char cmdMovement = 0x41u;

void MainDisplay::on_lumenChanged()
{
    unsigned char valLumen = ui->lumenSlider->value();

    setSensor.setPacket(&cmdLumen, &valLumen);

    if(valLumen==1)
        ui->lumenSlider->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        ui->lumenSlider->setStyleSheet("background-color: rgb(255, 0, 0);");

    qDebug() << "Lumen value: " << valLumen;

}

void MainDisplay::on_movementChanged()
{
    unsigned char valMovement = ui->movementSlider->value();

    setSensor.setPacket(&cmdMovement, &valMovement);

    if(valMovement==1)
        ui->movementSlider->setStyleSheet("background-color: rgb(0, 255, 0);");
    else
        ui->movementSlider->setStyleSheet("background-color: rgb(255, 0, 0);");

    qDebug() << "Movement value: " << valMovement;

}

void MainDisplay::on_distanceChanged()
{
    unsigned char valDistance = ui->distanceSpinBox->value();

    setSensor.setPacket(&cmdDistance, &valDistance);

    qDebug() << "Distance value: " << valDistance;

}

