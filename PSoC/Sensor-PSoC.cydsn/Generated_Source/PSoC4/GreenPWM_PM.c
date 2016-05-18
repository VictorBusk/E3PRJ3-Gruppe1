/*******************************************************************************
* File Name: GreenPWM_PM.c
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

#include "GreenPWM.h"

static GreenPWM_BACKUP_STRUCT GreenPWM_backup;


/*******************************************************************************
* Function Name: GreenPWM_SaveConfig
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
void GreenPWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: GreenPWM_Sleep
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
void GreenPWM_Sleep(void)
{
    if(0u != (GreenPWM_BLOCK_CONTROL_REG & GreenPWM_MASK))
    {
        GreenPWM_backup.enableState = 1u;
    }
    else
    {
        GreenPWM_backup.enableState = 0u;
    }

    GreenPWM_Stop();
    GreenPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: GreenPWM_RestoreConfig
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
void GreenPWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: GreenPWM_Wakeup
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
void GreenPWM_Wakeup(void)
{
    GreenPWM_RestoreConfig();

    if(0u != GreenPWM_backup.enableState)
    {
        GreenPWM_Enable();
    }
}


/* [] END OF FILE */
