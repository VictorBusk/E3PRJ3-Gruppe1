/*!
 * @file        handler.c
 * @brief       Handels incoming commands
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#include "handler.h"
#include "i2c.h"
#include "spi.h"

/***************************************
 *       Private attributes
 ***************************************/

/*!
 *  @brief      Value of the X position.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 xPos = 0;

/*!
 *  @brief      Value of the X maximum.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 xMax = 0;

/*!
 *  @brief      Value of the Y position.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 yPos = 0;

/*!
 *  @brief      Value of the Y maximum.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 yMax = 0;

/*!
 *  @brief      Value of the Z position.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 zPos = 0;

/*!
 *  @brief      Value of the Z maximum.
 *  @private
 *  @memberof   Handler
 *  @author     Jeppe Stærk (201271201@uni.au.dk)
 */
static uint8 zMax = 0;


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
    uint8 rxVal = 0;
    
    switch (cmd)
    {
        case 0x01 :
            i2c_getPacket(PSoC_XY, getXPos, &xPos);
            i2c_getPacket(PSoC_XY, getYPos, &yPos);
            i2c_getPacket(PSoC_Z, getZPos, &zPos);
            break;
        case 0x02 :
            i2c_getPacket(PSoC_XY, getXMax, &xMax);
            i2c_getPacket(PSoC_XY, getYMax, &yMax);
            i2c_getPacket(PSoC_Z, getZMax, &zMax);
            break;
        case CMD_SET_X_POS :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_SET_Y_POS :
            i2c_setPacket(PSoC_XY, cmd, val);
            break;
        case CMD_GET_X_POS :
            spi_tx(xPos);
            break;
        case CMD_GET_Y_POS :
            spi_tx(yPos);
            break;
        case CMD_GET_X_MAX :
            spi_tx(xMax);
            break;
        case CMD_GET_Y_MAX :
            spi_tx(yMax);
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
            i2c_setPacket(zPos);
            break;
        case CMD_GET_Z_MAX :
            i2c_setPacket(zMax);
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
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_GET_GREEN_VAL :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_GET_BLUE_VAL :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_GET_LUMEN_VAL :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_SET_POWER_STS :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_SET_DISTANCE_STS :
            i2c_setPacket(PSoC_Sensor, cmd, txVal);
            break;
        case CMD_SET_MOVEMENT_STS :
            i2c_setPacket(PSoC_Sensor, cmd, txVal);
            break;
        case CMD_GET_DISTANCE_STS :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_GET_MOVEMENT_STS :
            i2c_getPacket(PSoC_Sensor, cmd, &rxVal);
            break;
        case CMD_DISTANCE_ALRT :
            handler(cmdStopX, val);
            handler(cmdStopY, val);
            handler(cmdStopZ, val);
            break;
        case CMD_MOVEMENT_ALRT : 
            handler(setPower, val);
            break;
        default :
            break;
    }
}

/* [] END OF FILE */
