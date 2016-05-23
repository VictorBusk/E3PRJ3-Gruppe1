/*******************************************************************************
* File Name: DEBUG.h
* Version 1.50
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_DEBUG_H
#define CY_SW_TX_UART_DEBUG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define DEBUG_BAUD_RATE                      (9600u)
#define DEBUG_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(DEBUG_PIN_STATIC_MODE == 1u)
    void DEBUG_Start(void) ;
#else
    void DEBUG_StartEx(uint8 port, uint8 pin) ;
#endif /* (DEBUG_PIN_STATIC_MODE == 1u) */

void DEBUG_Stop(void) ;
void DEBUG_PutChar(uint8 txDataByte) ;
void DEBUG_PutString(const char8 string[]) ;
void DEBUG_PutArray(const uint8 array[], uint32 byteCount) ;
void DEBUG_PutHexByte(uint8 txHexByte) ;
void DEBUG_PutHexInt(uint16 txHexInt) ;
void DEBUG_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_DEBUG_H */


/* [] END OF FILE */
