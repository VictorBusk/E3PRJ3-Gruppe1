/*******************************************************************************
* File Name: segments.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "segments.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        segments_PC =   (segments_PC & \
                                (uint32)(~(uint32)(segments_DRIVE_MODE_IND_MASK << (segments_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (segments_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: segments_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void segments_Write(uint8 value) 
{
    uint8 drVal = (uint8)(segments_DR & (uint8)(~segments_MASK));
    drVal = (drVal | ((uint8)(value << segments_SHIFT) & segments_MASK));
    segments_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: segments_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  segments_DM_STRONG     Strong Drive 
*  segments_DM_OD_HI      Open Drain, Drives High 
*  segments_DM_OD_LO      Open Drain, Drives Low 
*  segments_DM_RES_UP     Resistive Pull Up 
*  segments_DM_RES_DWN    Resistive Pull Down 
*  segments_DM_RES_UPDWN  Resistive Pull Up/Down 
*  segments_DM_DIG_HIZ    High Impedance Digital 
*  segments_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void segments_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(segments__0__SHIFT, mode);
	SetP4PinDriveMode(segments__1__SHIFT, mode);
	SetP4PinDriveMode(segments__2__SHIFT, mode);
	SetP4PinDriveMode(segments__3__SHIFT, mode);
	SetP4PinDriveMode(segments__4__SHIFT, mode);
	SetP4PinDriveMode(segments__5__SHIFT, mode);
	SetP4PinDriveMode(segments__6__SHIFT, mode);
	SetP4PinDriveMode(segments__7__SHIFT, mode);
}


/*******************************************************************************
* Function Name: segments_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro segments_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 segments_Read(void) 
{
    return (uint8)((segments_PS & segments_MASK) >> segments_SHIFT);
}


/*******************************************************************************
* Function Name: segments_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 segments_ReadDataReg(void) 
{
    return (uint8)((segments_DR & segments_MASK) >> segments_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(segments_INTSTAT) 

    /*******************************************************************************
    * Function Name: segments_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 segments_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(segments_INTSTAT & segments_MASK);
		segments_INTSTAT = maskedStatus;
        return maskedStatus >> segments_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
