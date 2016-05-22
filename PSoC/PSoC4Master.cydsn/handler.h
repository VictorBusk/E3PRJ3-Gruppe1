/*!
 * @file        handler.h
 * @brief       Handels incoming commands
 * @class       Handler
 * @author      Jeppe Stærk (201271201@uni.au.dk)
 */
#ifndef HANDLER_H
#define HANDLER_H
    
#include <project.h>

/***************************************
 *       Public methods
 ***************************************/
    
extern void handler(uint8 cmd, uint8 val);

/***************************************
 *       Public constants
 ****************************************/

/*!
 *  @defgroup CMD Command constants
 */

/*! \addtogroup CMD
 *  @{
 */

/* Commands set */
#define CMD_SET_X_POS (0x10u)         /*!< Command for set X position */
#define CMD_SET_Y_POS (0x11u)         /*!< Command for set Y position */
#define CMD_GET_X_POS (0x12u)         /*!< Command for get X position */
#define CMD_GET_Y_POS (0x13u)         /*!< Command for get Y position */
#define CMD_GET_X_MAX (0x14u)         /*!< Command for get X maximum */
#define CMD_GET_Y_MAX (0x15u)         /*!< Command for get Y maximum */
#define CMD_X_STP (0x16u)             /*!< Command for stop X */
#define CMD_Y_STP (0x17u)             /*!< Command for stop Y */
#define CMD_X_CAL (0x18u)             /*!< Command for calibrate X */
#define CMD_Y_CAL (0x19u)             /*!< Command for calibrate Y */
#define CMD_SET_Z_POS (0x20u)         /*!< Command for set Z position */
#define CMD_GET_Z_POS (0x21u)         /*!< Command for get Z position */
#define CMD_GET_Z_MAX (0x22u)         /*!< Command for get Z maximum */
#define CMD_Z_STP (0x23u)             /*!< Command for stop Z */
#define CMD_Z_CAL (0x24u)             /*!< Command for calibrate Z */
#define CMD_SET_RED_VAL (0x30u)       /*!< Command for set red value */
#define CMD_SET_GREEN_VAL (0x31u)     /*!< Command for set green value */
#define CMD_SET_BLUE_VAL (0x32u)      /*!< Command for set blue value */
#define CMD_SET_LUMEN_VAL (0x33u)     /*!< Command for set lumen value */
#define CMD_SET_POWER_STS (0x34u)     /*!< Command for set power status */
#define CMD_GET_RED_VAL (0x35u)       /*!< Command for get red value */
#define CMD_GET_GREEN_VAL (0x36u)     /*!< Command for get green value */
#define CMD_GET_BLUE_VAL (0x37u)      /*!< Command for get blue value */
#define CMD_GET_LUMEN_VAL (0x38u)     /*!< Command for get lumen value */
#define CMD_GET_POWER_STS (0x39u)     /*!< Command for get power status */
#define CMD_SET_DISTANCE_STS (0x40u)  /*!< Command for set distance status */
#define CMD_SET_MOVEMENT_STS (0x41u)  /*!< Command for set movement status */
#define CMD_GET_DISTANCE_STS (0x42u)  /*!< Command for get distance status */
#define CMD_GET_MOVEMENT_STS (0x43u)  /*!< Command for get movement status */
#define CMD_DISTANCE_ALRT (0x44u)     /*!< Command for distance alert */
#define CMD_MOVEMENT_ALRT (0x45u)     /*!< Command for movement alert */
/*! @} */

#endif  // ifndef HANDLER_H
/* [] END OF FILE */