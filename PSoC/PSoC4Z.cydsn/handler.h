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
#define CMD_SET_Z_POS (0x20u)
#define CMD_GET_Z_POS (0x21u)
#define CMD_Z_STP (0x23u)
#define CMD_Z_CAL (0x24u)
    
#endif  // ifndef HANDLER_H
/* [] END OF FILE */
