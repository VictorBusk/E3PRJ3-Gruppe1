/* ========================================
 *
 * File: handler.h
 * Description:
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 *
 * Author:
 * Matriculation number:
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
 */

#ifndef HANDLER_H
#define HANDLER_H

#include <project.h>

extern void handler(uint8 cmd, uint8 val);

/* Commands set */
#define CMD_SET_X_POS (0x10u)
#define CMD_SET_Y_POS (0x11u)
#define CMD_GET_X_POS (0x12u)
#define CMD_GET_Y_POS (0x13u)
#define CMD_X_STP (0x16u)
#define CMD_Y_STP (0x17u)
#define CMD_X_CAL (0x18u)
#define CMD_Y_CAL (0x19u)

#endif  // ifndef HANDLER_H
/* [] END OF FILE */
