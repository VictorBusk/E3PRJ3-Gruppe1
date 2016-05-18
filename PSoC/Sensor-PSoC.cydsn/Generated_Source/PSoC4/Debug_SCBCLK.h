/*******************************************************************************
* File Name: Debug_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Debug_SCBCLK_H)
#define CY_CLOCK_Debug_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Debug_SCBCLK_StartEx(uint32 alignClkDiv);
#define Debug_SCBCLK_Start() \
    Debug_SCBCLK_StartEx(Debug_SCBCLK__PA_DIV_ID)

#else

void Debug_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Debug_SCBCLK_Stop(void);

void Debug_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Debug_SCBCLK_GetDividerRegister(void);
uint8  Debug_SCBCLK_GetFractionalDividerRegister(void);

#define Debug_SCBCLK_Enable()                         Debug_SCBCLK_Start()
#define Debug_SCBCLK_Disable()                        Debug_SCBCLK_Stop()
#define Debug_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    Debug_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define Debug_SCBCLK_SetDivider(clkDivider)           Debug_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define Debug_SCBCLK_SetDividerValue(clkDivider)      Debug_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Debug_SCBCLK_DIV_ID     Debug_SCBCLK__DIV_ID

#define Debug_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Debug_SCBCLK_CTRL_REG   (*(reg32 *)Debug_SCBCLK__CTRL_REGISTER)
#define Debug_SCBCLK_DIV_REG    (*(reg32 *)Debug_SCBCLK__DIV_REGISTER)

#define Debug_SCBCLK_CMD_DIV_SHIFT          (0u)
#define Debug_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define Debug_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define Debug_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define Debug_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Debug_SCBCLK_CMD_DISABLE_SHIFT))
#define Debug_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Debug_SCBCLK_CMD_ENABLE_SHIFT))

#define Debug_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define Debug_SCBCLK_DIV_FRAC_SHIFT (3u)
#define Debug_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define Debug_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define Debug_SCBCLK_DIV_REG        (*(reg32 *)Debug_SCBCLK__REGISTER)
#define Debug_SCBCLK_ENABLE_REG     Debug_SCBCLK_DIV_REG
#define Debug_SCBCLK_DIV_FRAC_MASK  Debug_SCBCLK__FRAC_MASK
#define Debug_SCBCLK_DIV_FRAC_SHIFT (16u)
#define Debug_SCBCLK_DIV_INT_MASK   Debug_SCBCLK__DIVIDER_MASK
#define Debug_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Debug_SCBCLK_H) */

/* [] END OF FILE */
