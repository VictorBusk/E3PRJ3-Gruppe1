/*******************************************************************************
* File Name: Debug_PM.c
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

#include "Debug.h"
#include "Debug_PVT.h"

#if(Debug_SCB_MODE_I2C_INC)
    #include "Debug_I2C_PVT.h"
#endif /* (Debug_SCB_MODE_I2C_INC) */

#if(Debug_SCB_MODE_EZI2C_INC)
    #include "Debug_EZI2C_PVT.h"
#endif /* (Debug_SCB_MODE_EZI2C_INC) */

#if(Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC)
    #include "Debug_SPI_UART_PVT.h"
#endif /* (Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Debug_SCB_MODE_I2C_CONST_CFG   && (!Debug_I2C_WAKE_ENABLE_CONST))   || \
   (Debug_SCB_MODE_EZI2C_CONST_CFG && (!Debug_EZI2C_WAKE_ENABLE_CONST)) || \
   (Debug_SCB_MODE_SPI_CONST_CFG   && (!Debug_SPI_WAKE_ENABLE_CONST))   || \
   (Debug_SCB_MODE_UART_CONST_CFG  && (!Debug_UART_WAKE_ENABLE_CONST)))

    Debug_BACKUP_STRUCT Debug_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Debug_Sleep
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
void Debug_Sleep(void)
{
#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Debug_SCB_WAKE_ENABLE_CHECK)
    {
        if(Debug_SCB_MODE_I2C_RUNTM_CFG)
        {
            Debug_I2CSaveConfig();
        }
        else if(Debug_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Debug_EzI2CSaveConfig();
        }
    #if(!Debug_CY_SCBIP_V1)
        else if(Debug_SCB_MODE_SPI_RUNTM_CFG)
        {
            Debug_SpiSaveConfig();
        }
        else if(Debug_SCB_MODE_UART_RUNTM_CFG)
        {
            Debug_UartSaveConfig();
        }
    #endif /* (!Debug_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Debug_backup.enableState = (uint8) Debug_GET_CTRL_ENABLED;

        if(0u != Debug_backup.enableState)
        {
            Debug_Stop();
        }
    }

#else

    #if (Debug_SCB_MODE_I2C_CONST_CFG && Debug_I2C_WAKE_ENABLE_CONST)
        Debug_I2CSaveConfig();

    #elif (Debug_SCB_MODE_EZI2C_CONST_CFG && Debug_EZI2C_WAKE_ENABLE_CONST)
        Debug_EzI2CSaveConfig();

    #elif (Debug_SCB_MODE_SPI_CONST_CFG && Debug_SPI_WAKE_ENABLE_CONST)
        Debug_SpiSaveConfig();

    #elif (Debug_SCB_MODE_UART_CONST_CFG && Debug_UART_WAKE_ENABLE_CONST)
        Debug_UartSaveConfig();

    #else

        Debug_backup.enableState = (uint8) Debug_GET_CTRL_ENABLED;

        if(0u != Debug_backup.enableState)
        {
            Debug_Stop();
        }

    #endif /* defined (Debug_SCB_MODE_I2C_CONST_CFG) && (Debug_I2C_WAKE_ENABLE_CONST) */

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Debug_Wakeup
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
void Debug_Wakeup(void)
{
#if(Debug_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Debug_SCB_WAKE_ENABLE_CHECK)
    {
        if(Debug_SCB_MODE_I2C_RUNTM_CFG)
        {
            Debug_I2CRestoreConfig();
        }
        else if(Debug_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Debug_EzI2CRestoreConfig();
        }
    #if(!Debug_CY_SCBIP_V1)
        else if(Debug_SCB_MODE_SPI_RUNTM_CFG)
        {
            Debug_SpiRestoreConfig();
        }
        else if(Debug_SCB_MODE_UART_RUNTM_CFG)
        {
            Debug_UartRestoreConfig();
        }
    #endif /* (!Debug_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Debug_backup.enableState)
        {
            Debug_Enable();
        }
    }

#else

    #if (Debug_SCB_MODE_I2C_CONST_CFG  && Debug_I2C_WAKE_ENABLE_CONST)
        Debug_I2CRestoreConfig();

    #elif (Debug_SCB_MODE_EZI2C_CONST_CFG && Debug_EZI2C_WAKE_ENABLE_CONST)
        Debug_EzI2CRestoreConfig();

    #elif (Debug_SCB_MODE_SPI_CONST_CFG && Debug_SPI_WAKE_ENABLE_CONST)
        Debug_SpiRestoreConfig();

    #elif (Debug_SCB_MODE_UART_CONST_CFG && Debug_UART_WAKE_ENABLE_CONST)
        Debug_UartRestoreConfig();

    #else

        if(0u != Debug_backup.enableState)
        {
            Debug_Enable();
        }

    #endif /* (Debug_I2C_WAKE_ENABLE_CONST) */

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
