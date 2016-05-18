/*******************************************************************************
* File Name: DistTimer_PM.c
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

#include "DistTimer.h"

static DistTimer_backupStruct DistTimer_backup;


/*******************************************************************************
* Function Name: DistTimer_SaveConfig
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
*  DistTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DistTimer_SaveConfig(void) 
{
    #if (!DistTimer_UsingFixedFunction)
        DistTimer_backup.TimerUdb = DistTimer_ReadCounter();
        DistTimer_backup.InterruptMaskValue = DistTimer_STATUS_MASK;
        #if (DistTimer_UsingHWCaptureCounter)
            DistTimer_backup.TimerCaptureCounter = DistTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!DistTimer_UDB_CONTROL_REG_REMOVED)
            DistTimer_backup.TimerControlRegister = DistTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: DistTimer_RestoreConfig
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
*  DistTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DistTimer_RestoreConfig(void) 
{   
    #if (!DistTimer_UsingFixedFunction)

        DistTimer_WriteCounter(DistTimer_backup.TimerUdb);
        DistTimer_STATUS_MASK =DistTimer_backup.InterruptMaskValue;
        #if (DistTimer_UsingHWCaptureCounter)
            DistTimer_SetCaptureCount(DistTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!DistTimer_UDB_CONTROL_REG_REMOVED)
            DistTimer_WriteControlRegister(DistTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: DistTimer_Sleep
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
*  DistTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void DistTimer_Sleep(void) 
{
    #if(!DistTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(DistTimer_CTRL_ENABLE == (DistTimer_CONTROL & DistTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            DistTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            DistTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    DistTimer_Stop();
    DistTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: DistTimer_Wakeup
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
*  DistTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DistTimer_Wakeup(void) 
{
    DistTimer_RestoreConfig();
    #if(!DistTimer_UDB_CONTROL_REG_REMOVED)
        if(DistTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                DistTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
