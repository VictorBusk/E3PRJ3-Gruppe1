/*******************************************************************************
* File Name: Lumen_I2C_SCBCLK.h
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

#if !defined(CY_CLOCK_Lumen_I2C_SCBCLK_H)
#define CY_CLOCK_Lumen_I2C_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Lumen_I2C_SCBCLK_StartEx(uint32 alignClkDiv);
#define Lumen_I2C_SCBCLK_Start() \
    Lumen_I2C_SCBCLK_StartEx(Lumen_I2C_SCBCLK__PA_DIV_ID)

#else

void Lumen_I2C_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Lumen_I2C_SCBCLK_Stop(void);

void Lumen_I2C_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Lumen_I2C_SCBCLK_GetDividerRegister(void);
uint8  Lumen_I2C_SCBCLK_GetFractionalDividerRegister(void);

#define Lumen_I2C_SCBCLK_Enable()                         Lumen_I2C_SCBCLK_Start()
#define Lumen_I2C_SCBCLK_Disable()                        Lumen_I2C_SCBCLK_Stop()
#define Lumen_I2C_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    Lumen_I2C_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define Lumen_I2C_SCBCLK_SetDivider(clkDivider)           Lumen_I2C_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define Lumen_I2C_SCBCLK_SetDividerValue(clkDivider)      Lumen_I2C_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Lumen_I2C_SCBCLK_DIV_ID     Lumen_I2C_SCBCLK__DIV_ID

#define Lumen_I2C_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Lumen_I2C_SCBCLK_CTRL_REG   (*(reg32 *)Lumen_I2C_SCBCLK__CTRL_REGISTER)
#define Lumen_I2C_SCBCLK_DIV_REG    (*(reg32 *)Lumen_I2C_SCBCLK__DIV_REGISTER)

#define Lumen_I2C_SCBCLK_CMD_DIV_SHIFT          (0u)
#define Lumen_I2C_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define Lumen_I2C_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define Lumen_I2C_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define Lumen_I2C_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Lumen_I2C_SCBCLK_CMD_DISABLE_SHIFT))
#define Lumen_I2C_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Lumen_I2C_SCBCLK_CMD_ENABLE_SHIFT))

#define Lumen_I2C_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define Lumen_I2C_SCBCLK_DIV_FRAC_SHIFT (3u)
#define Lumen_I2C_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define Lumen_I2C_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define Lumen_I2C_SCBCLK_DIV_REG        (*(reg32 *)Lumen_I2C_SCBCLK__REGISTER)
#define Lumen_I2C_SCBCLK_ENABLE_REG     Lumen_I2C_SCBCLK_DIV_REG
#define Lumen_I2C_SCBCLK_DIV_FRAC_MASK  Lumen_I2C_SCBCLK__FRAC_MASK
#define Lumen_I2C_SCBCLK_DIV_FRAC_SHIFT (16u)
#define Lumen_I2C_SCBCLK_DIV_INT_MASK   Lumen_I2C_SCBCLK__DIVIDER_MASK
#define Lumen_I2C_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Lumen_I2C_SCBCLK_H) */

/* [] END OF FILE */
