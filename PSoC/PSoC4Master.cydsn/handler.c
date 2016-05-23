/*!
 * @file        handler.c
 * @brief       Handels incoming commands
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "handler.h"
#include "data.h"
#include "i2c.h"
#include "spi.h"
#include "lcd.h"
#include <stdio.h>

/***************************************
 *       Public methods
 ***************************************/

/*!
 *  @brief      Handels incoming commands
 *  @param[in]  cmd   Command to be handled.
 *  @param[in]  val   Value to pass along with the command.
 *  @public
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
void handler(uint8 cmd, uint8 val)
{    
//    char str[10];
//    sprintf(str, "C: %d V: %d", (int)cmd, (int)val);
//    lcd_newline(str);
    switch (cmd)
    {
        case 0x01 :
            i2c_getPacket(PSoC_XY, CMD_GET_X_POS, &dataMaster.xVal);
            i2c_getPacket(PSoC_XY, CMD_GET_Y_POS, &dataMaster.yVal);
            i2c_getPacket(PSoC_Z, CMD_GET_Z_POS, &dataMaster.zVal);
            break;
        case 0x03 :
            i2c_getPacket(PSoC_Sensor, CMD_GET_RED_VAL, &dataMaster.rVal);
            i2c_getPacket(PSoC_Sensor, CMD_GET_BLUE_VAL, &dataMaster.gVal);
            i2c_getPacket(PSoC_Sensor, CMD_GET_GREEN_VAL, &dataMaster.bVal);
            break;
        case 0x04 :
            i2c_getPacket(PSoC_Sensor, CMD_GET_LUMEN_VAL, &dataMaster.lumenVal);
            i2c_getPacket(PSoC_Sensor, CMD_GET_POWER_STS, &dataMaster.powerVal);
            i2c_getPacket(PSoC_Sensor, CMD_SET_DISTANCE_STS, &dataMaster.distanceVal);
            i2c_getPacket(PSoC_Sensor, CMD_GET_MOVEMENT_STS, &dataMaster.movementVal);
            break;
        case CMD_SET_X_POS :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_SET_Y_POS :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_GET_X_POS :
            spi_tx(dataMaster.xVal);
            break;
        case CMD_GET_Y_POS :
            spi_tx(dataMaster.yVal);
            break;
        case CMD_GET_X_MAX :
            spi_tx(0xEE);
            break;
        case CMD_GET_Y_MAX :
            spi_tx(0xEE);
            break;
        case CMD_X_STP :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_Y_STP :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_X_CAL :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_Y_CAL :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_SET_Z_POS :
            i2c_setPacket(PSoC_Z, cmd, val);
            break;
        case CMD_GET_Z_POS :
            spi_tx(dataMaster.zVal);
            break;
        case CMD_GET_Z_MAX :
            spi_tx(0xEE);
            break;
        case CMD_Z_STP :
            i2c_setPacket(PSoC_Z, cmd, val);
            break;
        case CMD_Z_CAL :
            i2c_setPacket(PSoC_Z, cmd, val);
            break;
        case CMD_SET_RED_VAL :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_SET_GREEN_VAL :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_SET_BLUE_VAL :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_SET_LUMEN_VAL :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_SET_POWER_STS :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_GET_RED_VAL :
            spi_tx(dataMaster.rVal);
            break;
        case CMD_GET_GREEN_VAL :
            spi_tx(dataMaster.gVal);
            break;
        case CMD_GET_BLUE_VAL :
            spi_tx(dataMaster.bVal);
            break;
        case CMD_GET_LUMEN_VAL :
            spi_tx(dataMaster.lumenVal);
            break;
        case CMD_GET_POWER_STS :
            spi_tx(dataMaster.powerVal);
            break;
        case CMD_SET_DISTANCE_STS :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_SET_MOVEMENT_STS :
            i2c_setPacket(PSoC_Sensor, cmd, val);
            break;
        case CMD_GET_DISTANCE_STS :
            spi_tx(dataMaster.distanceVal);
            break;
        case CMD_GET_MOVEMENT_STS :
            spi_tx(dataMaster.movementVal);
            break;
        case CMD_DISTANCE_ALRT :
            handler(CMD_X_STP, val);
            handler(CMD_Y_STP, val);
            handler(CMD_Z_STP, val);
            break;
        case CMD_MOVEMENT_ALRT : 
            handler(CMD_SET_POWER_STS, val);
            break;
        default :
            break;
    }
}

/* [] END OF FILE */
