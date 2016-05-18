/*******************************************************************************
* File Name: MetronomeTimer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "MetronomeTimer.h"

static MetronomeTimer_backupStruct MetronomeTimer_backup;


/*******************************************************************************
* Function Name: MetronomeTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  MetronomeTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void MetronomeTimer_SaveConfig(void) 
{
    #if (!MetronomeTimer_UsingFixedFunction)
        MetronomeTimer_backup.TimerUdb = MetronomeTimer_ReadCounter();
        MetronomeTimer_backup.InterruptMaskValue = MetronomeTimer_STATUS_MASK;
        #if (MetronomeTimer_UsingHWCaptureCounter)
            MetronomeTimer_backup.TimerCaptureCounter = MetronomeTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
            MetronomeTimer_backup.TimerControlRegister = MetronomeTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: MetronomeTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  MetronomeTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void MetronomeTimer_RestoreConfig(void) 
{   
    #if (!MetronomeTimer_UsingFixedFunction)

        MetronomeTimer_WriteCounter(MetronomeTimer_backup.TimerUdb);
        MetronomeTimer_STATUS_MASK =MetronomeTimer_backup.InterruptMaskValue;
        #if (MetronomeTimer_UsingHWCaptureCounter)
            MetronomeTimer_SetCaptureCount(MetronomeTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
            MetronomeTimer_WriteControlRegister(MetronomeTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: MetronomeTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  MetronomeTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void MetronomeTimer_Sleep(void) 
{
    #if(!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(MetronomeTimer_CTRL_ENABLE == (MetronomeTimer_CONTROL & MetronomeTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            MetronomeTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            MetronomeTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    MetronomeTimer_Stop();
    MetronomeTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: MetronomeTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  MetronomeTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void MetronomeTimer_Wakeup(void) 
{
    MetronomeTimer_RestoreConfig();
    #if(!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
        if(MetronomeTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                MetronomeTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
