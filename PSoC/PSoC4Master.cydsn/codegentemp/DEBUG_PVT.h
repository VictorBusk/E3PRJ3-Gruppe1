/*******************************************************************************
* File Name: DEBUG_PVT.h
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

#ifndef CY_SW_TX_UART_DEBUG_PVT_H
#define CY_SW_TX_UART_DEBUG_PVT_H

#include "DEBUG.h"


#if(DEBUG_PIN_STATIC_MODE == 1u)
    #define DEBUG_PIN_NUMBER                 (DEBUG_tx__0__SHIFT)
    #define DEBUG_PIN_PORT_NUMBER            (DEBUG_tx__0__PORT)
    #if (CY_PSOC4)
        #define DEBUG_PIN_DR                 (DEBUG_tx__DR)
    #else
        #define DEBUG_PIN_DR                 (DEBUG_tx__0__PC)
    #endif /* (CY_PSOC4) */
    
#else
    #if (!CY_PSOC4)
        #define DEBUG_PORT_CNF_BASE          (CYREG_PRT0_PC0)
    #else
        #if (CY_PSOC4A)
            #define DEBUG_PORT_CNF_BASE          ((uint32)CYDEV_PRT0_BASE)
            #define DEBUG_PORT_CNF_SIZE          ((uint32)CYDEV_PRT0_SIZE)
            #define DEBUG_PORT_CNF_MODE_OFFSET   ((uint32)(CYREG_PRT0_PC - CYDEV_PRT0_BASE))
            #define DEBUG_PORT_CNF_DR_OFFSET     ((uint32)(CYDEV_PRT0_BASE - CYREG_PRT0_DR))     
        #else
            #define DEBUG_PORT_CNF_BASE          ((uint32)CYDEV_GPIO_PRT0_BASE)
            #define DEBUG_PORT_CNF_SIZE          ((uint32)CYDEV_GPIO_PRT0_SIZE)
            #define DEBUG_PORT_CNF_MODE_OFFSET   ((uint32)(CYREG_GPIO_PRT0_PC - CYDEV_GPIO_PRT0_BASE))
            #define DEBUG_PORT_CNF_DR_OFFSET     ((uint32)(CYDEV_GPIO_PRT0_BASE - CYREG_GPIO_PRT0_DR))
        #endif /* (CY_PSOC4A) */
    #endif /* (!CY_PSOC4) */
#endif /* (DEBUG_PIN_STATIC_MODE == 1u) */

/* Nibble Offset and Mask */
#define DEBUG_BYTE_UPPER_NIBBLE_SHIFT        (0x04u)
#define DEBUG_U16_UPPER_BYTE_SHIFT           (0x08u)
#define DEBUG_BYTE_LOWER_NIBBLE_MASK         (0x0Fu)
#define DEBUG_U16_LOWER_BYTE_MASK            (0xFFu)

#if (!CY_PSOC4)
    #define DEBUG_MAX_PORT_NUMBER            (15u)
#else
    #if (CY_PSOC4_4100 || CY_PSOC4_4200)
        #define DEBUG_MAX_PORT_NUMBER            (4u)
    #else
        #define DEBUG_MAX_PORT_NUMBER            ((-1u) - 1u)
    #endif  /* (CY_PSOC4_4100 || CY_PSOC4_4200) */
#endif /* (!CY_PSOC4) */

#define DEBUG_MAX_PIN_NUMBER                 (7u)
#endif /* CY_SW_TX_UART_DEBUG_PVT_H */


/* [] END OF FILE */
