/*******************************************************************************
* File Name: LumenCom_PM.c
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

#include "LumenCom.h"
#include "LumenCom_PVT.h"

#if(LumenCom_SCB_MODE_I2C_INC)
    #include "LumenCom_I2C_PVT.h"
#endif /* (LumenCom_SCB_MODE_I2C_INC) */

#if(LumenCom_SCB_MODE_EZI2C_INC)
    #include "LumenCom_EZI2C_PVT.h"
#endif /* (LumenCom_SCB_MODE_EZI2C_INC) */

#if(LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC)
    #include "LumenCom_SPI_UART_PVT.h"
#endif /* (LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG || \
   (LumenCom_SCB_MODE_I2C_CONST_CFG   && (!LumenCom_I2C_WAKE_ENABLE_CONST))   || \
   (LumenCom_SCB_MODE_EZI2C_CONST_CFG && (!LumenCom_EZI2C_WAKE_ENABLE_CONST)) || \
   (LumenCom_SCB_MODE_SPI_CONST_CFG   && (!LumenCom_SPI_WAKE_ENABLE_CONST))   || \
   (LumenCom_SCB_MODE_UART_CONST_CFG  && (!LumenCom_UART_WAKE_ENABLE_CONST)))

    LumenCom_BACKUP_STRUCT LumenCom_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: LumenCom_Sleep
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
void LumenCom_Sleep(void)
{
#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LumenCom_SCB_WAKE_ENABLE_CHECK)
    {
        if(LumenCom_SCB_MODE_I2C_RUNTM_CFG)
        {
            LumenCom_I2CSaveConfig();
        }
        else if(LumenCom_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LumenCom_EzI2CSaveConfig();
        }
    #if(!LumenCom_CY_SCBIP_V1)
        else if(LumenCom_SCB_MODE_SPI_RUNTM_CFG)
        {
            LumenCom_SpiSaveConfig();
        }
        else if(LumenCom_SCB_MODE_UART_RUNTM_CFG)
        {
            LumenCom_UartSaveConfig();
        }
    #endif /* (!LumenCom_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        LumenCom_backup.enableState = (uint8) LumenCom_GET_CTRL_ENABLED;

        if(0u != LumenCom_backup.enableState)
        {
            LumenCom_Stop();
        }
    }

#else

    #if (LumenCom_SCB_MODE_I2C_CONST_CFG && LumenCom_I2C_WAKE_ENABLE_CONST)
        LumenCom_I2CSaveConfig();

    #elif (LumenCom_SCB_MODE_EZI2C_CONST_CFG && LumenCom_EZI2C_WAKE_ENABLE_CONST)
        LumenCom_EzI2CSaveConfig();

    #elif (LumenCom_SCB_MODE_SPI_CONST_CFG && LumenCom_SPI_WAKE_ENABLE_CONST)
        LumenCom_SpiSaveConfig();

    #elif (LumenCom_SCB_MODE_UART_CONST_CFG && LumenCom_UART_WAKE_ENABLE_CONST)
        LumenCom_UartSaveConfig();

    #else

        LumenCom_backup.enableState = (uint8) LumenCom_GET_CTRL_ENABLED;

        if(0u != LumenCom_backup.enableState)
        {
            LumenCom_Stop();
        }

    #endif /* defined (LumenCom_SCB_MODE_I2C_CONST_CFG) && (LumenCom_I2C_WAKE_ENABLE_CONST) */

#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LumenCom_Wakeup
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
void LumenCom_Wakeup(void)
{
#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)

    if(LumenCom_SCB_WAKE_ENABLE_CHECK)
    {
        if(LumenCom_SCB_MODE_I2C_RUNTM_CFG)
        {
            LumenCom_I2CRestoreConfig();
        }
        else if(LumenCom_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            LumenCom_EzI2CRestoreConfig();
        }
    #if(!LumenCom_CY_SCBIP_V1)
        else if(LumenCom_SCB_MODE_SPI_RUNTM_CFG)
        {
            LumenCom_SpiRestoreConfig();
        }
        else if(LumenCom_SCB_MODE_UART_RUNTM_CFG)
        {
            LumenCom_UartRestoreConfig();
        }
    #endif /* (!LumenCom_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != LumenCom_backup.enableState)
        {
            LumenCom_Enable();
        }
    }

#else

    #if (LumenCom_SCB_MODE_I2C_CONST_CFG  && LumenCom_I2C_WAKE_ENABLE_CONST)
        LumenCom_I2CRestoreConfig();

    #elif (LumenCom_SCB_MODE_EZI2C_CONST_CFG && LumenCom_EZI2C_WAKE_ENABLE_CONST)
        LumenCom_EzI2CRestoreConfig();

    #elif (LumenCom_SCB_MODE_SPI_CONST_CFG && LumenCom_SPI_WAKE_ENABLE_CONST)
        LumenCom_SpiRestoreConfig();

    #elif (LumenCom_SCB_MODE_UART_CONST_CFG && LumenCom_UART_WAKE_ENABLE_CONST)
        LumenCom_UartRestoreConfig();

    #else

        if(0u != LumenCom_backup.enableState)
        {
            LumenCom_Enable();
        }

    #endif /* (LumenCom_I2C_WAKE_ENABLE_CONST) */

#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
