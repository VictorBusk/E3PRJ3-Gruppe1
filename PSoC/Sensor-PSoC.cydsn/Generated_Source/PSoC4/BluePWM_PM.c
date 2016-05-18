/*******************************************************************************
* File Name: BluePWM_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BluePWM.h"

static BluePWM_BACKUP_STRUCT BluePWM_backup;


/*******************************************************************************
* Function Name: BluePWM_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BluePWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: BluePWM_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BluePWM_Sleep(void)
{
    if(0u != (BluePWM_BLOCK_CONTROL_REG & BluePWM_MASK))
    {
        BluePWM_backup.enableState = 1u;
    }
    else
    {
        BluePWM_backup.enableState = 0u;
    }

    BluePWM_Stop();
    BluePWM_SaveConfig();
}


/*******************************************************************************
* Function Name: BluePWM_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BluePWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: BluePWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BluePWM_Wakeup(void)
{
    BluePWM_RestoreConfig();

    if(0u != BluePWM_backup.enableState)
    {
        BluePWM_Enable();
    }
}


/* [] END OF FILE */
