/*!
 * @file        settings.cpp
 * @brief       Handles sensor behavior
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "maindisplay.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>

/***************************************
 *       Public constants
 ****************************************/

const unsigned char cmdLumen = 0x33u;
const unsigned char cmdDistance = 0x40u;
const unsigned char cmdMovement = 0x41u;

const unsigned char cmdCalX = 0x18u;
const unsigned char cmdCalY = 0x19u;
const unsigned char cmdCalZ = 0x24u;

/*!
 *  @brief      Sends turn on/off value to lumen sensor according to lumen slider position.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

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

/*!
 *  @brief      Sends turn on/off value to movement sensor according to movement slider position.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

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

/*!
 *  @brief      Sends distance value to distance sensor according to distance spinbox value.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_distanceChanged()
{
    unsigned char valDistance = ui->distanceSpinBox->value();

    setSensor.setPacket(&cmdDistance, &valDistance);

    qDebug() << "Distance value: " << valDistance;

}

/*!
 *  @brief      Sends calibration commands on Calibrate button pressed event.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_calButton_pressed()
{
    unsigned char startVal = 1;

    setSensor.setPacket(&cmdCalX, &startVal);
    setSensor.setPacket(&cmdCalY, &startVal);
    setSensor.setPacket(&cmdCalZ, &startVal);

    qDebug() << "Starting calibration sequence.";
}

/* [] END OF FILE */
