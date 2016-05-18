/*******************************************************************************
* File Name: SPIM_PM.c
* Version 3.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIM.h"
#include "SPIM_PVT.h"

#if(SPIM_SCB_MODE_I2C_INC)
    #include "SPIM_I2C_PVT.h"
#endif /* (SPIM_SCB_MODE_I2C_INC) */

#if(SPIM_SCB_MODE_EZI2C_INC)
    #include "SPIM_EZI2C_PVT.h"
#endif /* (SPIM_SCB_MODE_EZI2C_INC) */

#if(SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC)
    #include "SPIM_SPI_UART_PVT.h"
#endif /* (SPIM_SCB_MODE_SPI_INC || SPIM_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SPIM_SCB_MODE_I2C_CONST_CFG   && (!SPIM_I2C_WAKE_ENABLE_CONST))   || \
   (SPIM_SCB_MODE_EZI2C_CONST_CFG && (!SPIM_EZI2C_WAKE_ENABLE_CONST)) || \
   (SPIM_SCB_MODE_SPI_CONST_CFG   && (!SPIM_SPI_WAKE_ENABLE_CONST))   || \
   (SPIM_SCB_MODE_UART_CONST_CFG  && (!SPIM_UART_WAKE_ENABLE_CONST)))

    SPIM_BACKUP_STRUCT SPIM_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SPIM_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component to enter Deep Sleep.
*  The "Enable wakeup from Sleep Mode" selection has an influence on
*  this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIM_Sleep(void)
{
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPIM_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPIM_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPIM_I2CSaveConfig();
        }
        else if(SPIM_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPIM_EzI2CSaveConfig();
        }
    #if(!SPIM_CY_SCBIP_V1)
        else if(SPIM_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPIM_SpiSaveConfig();
        }
        else if(SPIM_SCB_MODE_UART_RUNTM_CFG)
        {
            SPIM_UartSaveConfig();
        }
    #endif /* (!SPIM_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SPIM_backup.enableState = (uint8) SPIM_GET_CTRL_ENABLED;

        if(0u != SPIM_backup.enableState)
        {
            SPIM_Stop();
        }
    }

#else

    #if (SPIM_SCB_MODE_I2C_CONST_CFG && SPIM_I2C_WAKE_ENABLE_CONST)
        SPIM_I2CSaveConfig();

    #elif (SPIM_SCB_MODE_EZI2C_CONST_CFG && SPIM_EZI2C_WAKE_ENABLE_CONST)
        SPIM_EzI2CSaveConfig();

    #elif (SPIM_SCB_MODE_SPI_CONST_CFG && SPIM_SPI_WAKE_ENABLE_CONST)
        SPIM_SpiSaveConfig();

    #elif (SPIM_SCB_MODE_UART_CONST_CFG && SPIM_UART_WAKE_ENABLE_CONST)
        SPIM_UartSaveConfig();

    #else

        SPIM_backup.enableState = (uint8) SPIM_GET_CTRL_ENABLED;

        if(0u != SPIM_backup.enableState)
        {
            SPIM_Stop();
        }

    #endif /* defined (SPIM_SCB_MODE_I2C_CONST_CFG) && (SPIM_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIM_Wakeup
********************************************************************************
*
* Summary:
*  Prepares the component for the Active mode operation after exiting
*  Deep Sleep. The "Enable wakeup from Sleep Mode" option has an influence
*  on this function implementation.
*  This function should not be called after exiting Sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIM_Wakeup(void)
{
#if(SPIM_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPIM_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPIM_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPIM_I2CRestoreConfig();
        }
        else if(SPIM_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPIM_EzI2CRestoreConfig();
        }
    #if(!SPIM_CY_SCBIP_V1)
        else if(SPIM_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPIM_SpiRestoreConfig();
        }
        else if(SPIM_SCB_MODE_UART_RUNTM_CFG)
        {
            SPIM_UartRestoreConfig();
        }
    #endif /* (!SPIM_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SPIM_backup.enableState)
        {
            SPIM_Enable();
        }
    }

#else

    #if (SPIM_SCB_MODE_I2C_CONST_CFG  && SPIM_I2C_WAKE_ENABLE_CONST)
        SPIM_I2CRestoreConfig();

    #elif (SPIM_SCB_MODE_EZI2C_CONST_CFG && SPIM_EZI2C_WAKE_ENABLE_CONST)
        SPIM_EzI2CRestoreConfig();

    #elif (SPIM_SCB_MODE_SPI_CONST_CFG && SPIM_SPI_WAKE_ENABLE_CONST)
        SPIM_SpiRestoreConfig();

    #elif (SPIM_SCB_MODE_UART_CONST_CFG && SPIM_UART_WAKE_ENABLE_CONST)
        SPIM_UartRestoreConfig();

    #else

        if(0u != SPIM_backup.enableState)
        {
            SPIM_Enable();
        }

    #endif /* (SPIM_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPIM_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
