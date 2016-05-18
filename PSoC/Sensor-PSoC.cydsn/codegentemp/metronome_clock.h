/*******************************************************************************
* File Name: metronome_clock.h
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

#if !defined(CY_CLOCK_metronome_clock_H)
#define CY_CLOCK_metronome_clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void metronome_clock_StartEx(uint32 alignClkDiv);
#define metronome_clock_Start() \
    metronome_clock_StartEx(metronome_clock__PA_DIV_ID)

#else

void metronome_clock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void metronome_clock_Stop(void);

void metronome_clock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 metronome_clock_GetDividerRegister(void);
uint8  metronome_clock_GetFractionalDividerRegister(void);

#define metronome_clock_Enable()                         metronome_clock_Start()
#define metronome_clock_Disable()                        metronome_clock_Stop()
#define metronome_clock_SetDividerRegister(clkDivider, reset)  \
    metronome_clock_SetFractionalDividerRegister((clkDivider), 0u)
#define metronome_clock_SetDivider(clkDivider)           metronome_clock_SetDividerRegister((clkDivider), 1u)
#define metronome_clock_SetDividerValue(clkDivider)      metronome_clock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define metronome_clock_DIV_ID     metronome_clock__DIV_ID

#define metronome_clock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define metronome_clock_CTRL_REG   (*(reg32 *)metronome_clock__CTRL_REGISTER)
#define metronome_clock_DIV_REG    (*(reg32 *)metronome_clock__DIV_REGISTER)

#define metronome_clock_CMD_DIV_SHIFT          (0u)
#define metronome_clock_CMD_PA_DIV_SHIFT       (8u)
#define metronome_clock_CMD_DISABLE_SHIFT      (30u)
#define metronome_clock_CMD_ENABLE_SHIFT       (31u)

#define metronome_clock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << metronome_clock_CMD_DISABLE_SHIFT))
#define metronome_clock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << metronome_clock_CMD_ENABLE_SHIFT))

#define metronome_clock_DIV_FRAC_MASK  (0x000000F8u)
#define metronome_clock_DIV_FRAC_SHIFT (3u)
#define metronome_clock_DIV_INT_MASK   (0xFFFFFF00u)
#define metronome_clock_DIV_INT_SHIFT  (8u)

#else 

#define metronome_clock_DIV_REG        (*(reg32 *)metronome_clock__REGISTER)
#define metronome_clock_ENABLE_REG     metronome_clock_DIV_REG
#define metronome_clock_DIV_FRAC_MASK  metronome_clock__FRAC_MASK
#define metronome_clock_DIV_FRAC_SHIFT (16u)
#define metronome_clock_DIV_INT_MASK   metronome_clock__DIVIDER_MASK
#define metronome_clock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_metronome_clock_H) */

/* [] END OF FILE */
