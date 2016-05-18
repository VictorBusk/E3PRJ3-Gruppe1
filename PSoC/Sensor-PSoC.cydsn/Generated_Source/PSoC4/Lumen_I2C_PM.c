/*******************************************************************************
* File Name: Lumen_I2C_PM.c
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

#include "Lumen_I2C.h"
#include "Lumen_I2C_PVT.h"

#if(Lumen_I2C_SCB_MODE_I2C_INC)
    #include "Lumen_I2C_I2C_PVT.h"
#endif /* (Lumen_I2C_SCB_MODE_I2C_INC) */

#if(Lumen_I2C_SCB_MODE_EZI2C_INC)
    #include "Lumen_I2C_EZI2C_PVT.h"
#endif /* (Lumen_I2C_SCB_MODE_EZI2C_INC) */

#if(Lumen_I2C_SCB_MODE_SPI_INC || Lumen_I2C_SCB_MODE_UART_INC)
    #include "Lumen_I2C_SPI_UART_PVT.h"
#endif /* (Lumen_I2C_SCB_MODE_SPI_INC || Lumen_I2C_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG || \
   (Lumen_I2C_SCB_MODE_I2C_CONST_CFG   && (!Lumen_I2C_I2C_WAKE_ENABLE_CONST))   || \
   (Lumen_I2C_SCB_MODE_EZI2C_CONST_CFG && (!Lumen_I2C_EZI2C_WAKE_ENABLE_CONST)) || \
   (Lumen_I2C_SCB_MODE_SPI_CONST_CFG   && (!Lumen_I2C_SPI_WAKE_ENABLE_CONST))   || \
   (Lumen_I2C_SCB_MODE_UART_CONST_CFG  && (!Lumen_I2C_UART_WAKE_ENABLE_CONST)))

    Lumen_I2C_BACKUP_STRUCT Lumen_I2C_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: Lumen_I2C_Sleep
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
void Lumen_I2C_Sleep(void)
{
#if(Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Lumen_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            Lumen_I2C_I2CSaveConfig();
        }
        else if(Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Lumen_I2C_EzI2CSaveConfig();
        }
    #if(!Lumen_I2C_CY_SCBIP_V1)
        else if(Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            Lumen_I2C_SpiSaveConfig();
        }
        else if(Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            Lumen_I2C_UartSaveConfig();
        }
    #endif /* (!Lumen_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        Lumen_I2C_backup.enableState = (uint8) Lumen_I2C_GET_CTRL_ENABLED;

        if(0u != Lumen_I2C_backup.enableState)
        {
            Lumen_I2C_Stop();
        }
    }

#else

    #if (Lumen_I2C_SCB_MODE_I2C_CONST_CFG && Lumen_I2C_I2C_WAKE_ENABLE_CONST)
        Lumen_I2C_I2CSaveConfig();

    #elif (Lumen_I2C_SCB_MODE_EZI2C_CONST_CFG && Lumen_I2C_EZI2C_WAKE_ENABLE_CONST)
        Lumen_I2C_EzI2CSaveConfig();

    #elif (Lumen_I2C_SCB_MODE_SPI_CONST_CFG && Lumen_I2C_SPI_WAKE_ENABLE_CONST)
        Lumen_I2C_SpiSaveConfig();

    #elif (Lumen_I2C_SCB_MODE_UART_CONST_CFG && Lumen_I2C_UART_WAKE_ENABLE_CONST)
        Lumen_I2C_UartSaveConfig();

    #else

        Lumen_I2C_backup.enableState = (uint8) Lumen_I2C_GET_CTRL_ENABLED;

        if(0u != Lumen_I2C_backup.enableState)
        {
            Lumen_I2C_Stop();
        }

    #endif /* defined (Lumen_I2C_SCB_MODE_I2C_CONST_CFG) && (Lumen_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Lumen_I2C_Wakeup
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
void Lumen_I2C_Wakeup(void)
{
#if(Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    if(Lumen_I2C_SCB_WAKE_ENABLE_CHECK)
    {
        if(Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
        {
            Lumen_I2C_I2CRestoreConfig();
        }
        else if(Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            Lumen_I2C_EzI2CRestoreConfig();
        }
    #if(!Lumen_I2C_CY_SCBIP_V1)
        else if(Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
        {
            Lumen_I2C_SpiRestoreConfig();
        }
        else if(Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
        {
            Lumen_I2C_UartRestoreConfig();
        }
    #endif /* (!Lumen_I2C_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != Lumen_I2C_backup.enableState)
        {
            Lumen_I2C_Enable();
        }
    }

#else

    #if (Lumen_I2C_SCB_MODE_I2C_CONST_CFG  && Lumen_I2C_I2C_WAKE_ENABLE_CONST)
        Lumen_I2C_I2CRestoreConfig();

    #elif (Lumen_I2C_SCB_MODE_EZI2C_CONST_CFG && Lumen_I2C_EZI2C_WAKE_ENABLE_CONST)
        Lumen_I2C_EzI2CRestoreConfig();

    #elif (Lumen_I2C_SCB_MODE_SPI_CONST_CFG && Lumen_I2C_SPI_WAKE_ENABLE_CONST)
        Lumen_I2C_SpiRestoreConfig();

    #elif (Lumen_I2C_SCB_MODE_UART_CONST_CFG && Lumen_I2C_UART_WAKE_ENABLE_CONST)
        Lumen_I2C_UartRestoreConfig();

    #else

        if(0u != Lumen_I2C_backup.enableState)
        {
            Lumen_I2C_Enable();
        }

    #endif /* (Lumen_I2C_I2C_WAKE_ENABLE_CONST) */

#endif /* (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
