/*******************************************************************************
* File Name: RedPWM_PM.c
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

#include "RedPWM.h"

static RedPWM_BACKUP_STRUCT RedPWM_backup;


/*******************************************************************************
* Function Name: RedPWM_SaveConfig
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
void RedPWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: RedPWM_Sleep
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
void RedPWM_Sleep(void)
{
    if(0u != (RedPWM_BLOCK_CONTROL_REG & RedPWM_MASK))
    {
        RedPWM_backup.enableState = 1u;
    }
    else
    {
        RedPWM_backup.enableState = 0u;
    }

    RedPWM_Stop();
    RedPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: RedPWM_RestoreConfig
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
void RedPWM_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: RedPWM_Wakeup
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
void RedPWM_Wakeup(void)
{
    RedPWM_RestoreConfig();

    if(0u != RedPWM_backup.enableState)
    {
        RedPWM_Enable();
    }
}


/* [] END OF FILE */
