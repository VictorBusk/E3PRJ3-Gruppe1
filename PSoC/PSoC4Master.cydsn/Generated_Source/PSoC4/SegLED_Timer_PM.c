/*******************************************************************************
* File Name: SegLED_Timer_PM.c
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

#include "SegLED_Timer.h"

static SegLED_Timer_backupStruct SegLED_Timer_backup;


/*******************************************************************************
* Function Name: SegLED_Timer_SaveConfig
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
*  SegLED_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SegLED_Timer_SaveConfig(void) 
{
    #if (!SegLED_Timer_UsingFixedFunction)
        SegLED_Timer_backup.TimerUdb = SegLED_Timer_ReadCounter();
        SegLED_Timer_backup.InterruptMaskValue = SegLED_Timer_STATUS_MASK;
        #if (SegLED_Timer_UsingHWCaptureCounter)
            SegLED_Timer_backup.TimerCaptureCounter = SegLED_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SegLED_Timer_UDB_CONTROL_REG_REMOVED)
            SegLED_Timer_backup.TimerControlRegister = SegLED_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SegLED_Timer_RestoreConfig
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
*  SegLED_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SegLED_Timer_RestoreConfig(void) 
{   
    #if (!SegLED_Timer_UsingFixedFunction)

        SegLED_Timer_WriteCounter(SegLED_Timer_backup.TimerUdb);
        SegLED_Timer_STATUS_MASK =SegLED_Timer_backup.InterruptMaskValue;
        #if (SegLED_Timer_UsingHWCaptureCounter)
            SegLED_Timer_SetCaptureCount(SegLED_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SegLED_Timer_UDB_CONTROL_REG_REMOVED)
            SegLED_Timer_WriteControlRegister(SegLED_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SegLED_Timer_Sleep
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
*  SegLED_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SegLED_Timer_Sleep(void) 
{
    #if(!SegLED_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SegLED_Timer_CTRL_ENABLE == (SegLED_Timer_CONTROL & SegLED_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SegLED_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SegLED_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SegLED_Timer_Stop();
    SegLED_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: SegLED_Timer_Wakeup
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
*  SegLED_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SegLED_Timer_Wakeup(void) 
{
    SegLED_Timer_RestoreConfig();
    #if(!SegLED_Timer_UDB_CONTROL_REG_REMOVED)
        if(SegLED_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SegLED_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
