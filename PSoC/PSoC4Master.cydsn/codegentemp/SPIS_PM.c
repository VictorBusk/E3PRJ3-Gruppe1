/*******************************************************************************
* File Name: SPIS_PM.c
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

#include "SPIS.h"
#include "SPIS_PVT.h"

#if(SPIS_SCB_MODE_I2C_INC)
    #include "SPIS_I2C_PVT.h"
#endif /* (SPIS_SCB_MODE_I2C_INC) */

#if(SPIS_SCB_MODE_EZI2C_INC)
    #include "SPIS_EZI2C_PVT.h"
#endif /* (SPIS_SCB_MODE_EZI2C_INC) */

#if(SPIS_SCB_MODE_SPI_INC || SPIS_SCB_MODE_UART_INC)
    #include "SPIS_SPI_UART_PVT.h"
#endif /* (SPIS_SCB_MODE_SPI_INC || SPIS_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SPIS_SCB_MODE_I2C_CONST_CFG   && (!SPIS_I2C_WAKE_ENABLE_CONST))   || \
   (SPIS_SCB_MODE_EZI2C_CONST_CFG && (!SPIS_EZI2C_WAKE_ENABLE_CONST)) || \
   (SPIS_SCB_MODE_SPI_CONST_CFG   && (!SPIS_SPI_WAKE_ENABLE_CONST))   || \
   (SPIS_SCB_MODE_UART_CONST_CFG  && (!SPIS_UART_WAKE_ENABLE_CONST)))

    SPIS_BACKUP_STRUCT SPIS_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SPIS_Sleep
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
void SPIS_Sleep(void)
{
#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPIS_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPIS_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPIS_I2CSaveConfig();
        }
        else if(SPIS_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPIS_EzI2CSaveConfig();
        }
    #if(!SPIS_CY_SCBIP_V1)
        else if(SPIS_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPIS_SpiSaveConfig();
        }
        else if(SPIS_SCB_MODE_UART_RUNTM_CFG)
        {
            SPIS_UartSaveConfig();
        }
    #endif /* (!SPIS_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SPIS_backup.enableState = (uint8) SPIS_GET_CTRL_ENABLED;

        if(0u != SPIS_backup.enableState)
        {
            SPIS_Stop();
        }
    }

#else

    #if (SPIS_SCB_MODE_I2C_CONST_CFG && SPIS_I2C_WAKE_ENABLE_CONST)
        SPIS_I2CSaveConfig();

    #elif (SPIS_SCB_MODE_EZI2C_CONST_CFG && SPIS_EZI2C_WAKE_ENABLE_CONST)
        SPIS_EzI2CSaveConfig();

    #elif (SPIS_SCB_MODE_SPI_CONST_CFG && SPIS_SPI_WAKE_ENABLE_CONST)
        SPIS_SpiSaveConfig();

    #elif (SPIS_SCB_MODE_UART_CONST_CFG && SPIS_UART_WAKE_ENABLE_CONST)
        SPIS_UartSaveConfig();

    #else

        SPIS_backup.enableState = (uint8) SPIS_GET_CTRL_ENABLED;

        if(0u != SPIS_backup.enableState)
        {
            SPIS_Stop();
        }

    #endif /* defined (SPIS_SCB_MODE_I2C_CONST_CFG) && (SPIS_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIS_Wakeup
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
void SPIS_Wakeup(void)
{
#if(SPIS_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SPIS_SCB_WAKE_ENABLE_CHECK)
    {
        if(SPIS_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPIS_I2CRestoreConfig();
        }
        else if(SPIS_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPIS_EzI2CRestoreConfig();
        }
    #if(!SPIS_CY_SCBIP_V1)
        else if(SPIS_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPIS_SpiRestoreConfig();
        }
        else if(SPIS_SCB_MODE_UART_RUNTM_CFG)
        {
            SPIS_UartRestoreConfig();
        }
    #endif /* (!SPIS_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SPIS_backup.enableState)
        {
            SPIS_Enable();
        }
    }

#else

    #if (SPIS_SCB_MODE_I2C_CONST_CFG  && SPIS_I2C_WAKE_ENABLE_CONST)
        SPIS_I2CRestoreConfig();

    #elif (SPIS_SCB_MODE_EZI2C_CONST_CFG && SPIS_EZI2C_WAKE_ENABLE_CONST)
        SPIS_EzI2CRestoreConfig();

    #elif (SPIS_SCB_MODE_SPI_CONST_CFG && SPIS_SPI_WAKE_ENABLE_CONST)
        SPIS_SpiRestoreConfig();

    #elif (SPIS_SCB_MODE_UART_CONST_CFG && SPIS_UART_WAKE_ENABLE_CONST)
        SPIS_UartRestoreConfig();

    #else

        if(0u != SPIS_backup.enableState)
        {
            SPIS_Enable();
        }

    #endif /* (SPIS_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
