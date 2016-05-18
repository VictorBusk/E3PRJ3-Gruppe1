/*******************************************************************************
* File Name: LumenCom_SCBCLK.h
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

#if !defined(CY_CLOCK_LumenCom_SCBCLK_H)
#define CY_CLOCK_LumenCom_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void LumenCom_SCBCLK_StartEx(uint32 alignClkDiv);
#define LumenCom_SCBCLK_Start() \
    LumenCom_SCBCLK_StartEx(LumenCom_SCBCLK__PA_DIV_ID)

#else

void LumenCom_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void LumenCom_SCBCLK_Stop(void);

void LumenCom_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 LumenCom_SCBCLK_GetDividerRegister(void);
uint8  LumenCom_SCBCLK_GetFractionalDividerRegister(void);

#define LumenCom_SCBCLK_Enable()                         LumenCom_SCBCLK_Start()
#define LumenCom_SCBCLK_Disable()                        LumenCom_SCBCLK_Stop()
#define LumenCom_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    LumenCom_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define LumenCom_SCBCLK_SetDivider(clkDivider)           LumenCom_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define LumenCom_SCBCLK_SetDividerValue(clkDivider)      LumenCom_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define LumenCom_SCBCLK_DIV_ID     LumenCom_SCBCLK__DIV_ID

#define LumenCom_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define LumenCom_SCBCLK_CTRL_REG   (*(reg32 *)LumenCom_SCBCLK__CTRL_REGISTER)
#define LumenCom_SCBCLK_DIV_REG    (*(reg32 *)LumenCom_SCBCLK__DIV_REGISTER)

#define LumenCom_SCBCLK_CMD_DIV_SHIFT          (0u)
#define LumenCom_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define LumenCom_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define LumenCom_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define LumenCom_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << LumenCom_SCBCLK_CMD_DISABLE_SHIFT))
#define LumenCom_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << LumenCom_SCBCLK_CMD_ENABLE_SHIFT))

#define LumenCom_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define LumenCom_SCBCLK_DIV_FRAC_SHIFT (3u)
#define LumenCom_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define LumenCom_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define LumenCom_SCBCLK_DIV_REG        (*(reg32 *)LumenCom_SCBCLK__REGISTER)
#define LumenCom_SCBCLK_ENABLE_REG     LumenCom_SCBCLK_DIV_REG
#define LumenCom_SCBCLK_DIV_FRAC_MASK  LumenCom_SCBCLK__FRAC_MASK
#define LumenCom_SCBCLK_DIV_FRAC_SHIFT (16u)
#define LumenCom_SCBCLK_DIV_INT_MASK   LumenCom_SCBCLK__DIVIDER_MASK
#define LumenCom_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_LumenCom_SCBCLK_H) */

/* [] END OF FILE */
