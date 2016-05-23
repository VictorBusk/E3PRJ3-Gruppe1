/*******************************************************************************
* File Name: BL.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "BL.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        BL_PC =   (BL_PC & \
                                (uint32)(~(uint32)(BL_DRIVE_MODE_IND_MASK << (BL_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (BL_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: BL_Write
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
void BL_Write(uint8 value) 
{
    uint8 drVal = (uint8)(BL_DR & (uint8)(~BL_MASK));
    drVal = (drVal | ((uint8)(value << BL_SHIFT) & BL_MASK));
    BL_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: BL_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void BL_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(BL__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: BL_Read
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
*  Macro BL_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 BL_Read(void) 
{
    return (uint8)((BL_PS & BL_MASK) >> BL_SHIFT);
}


/*******************************************************************************
* Function Name: BL_ReadDataReg
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
uint8 BL_ReadDataReg(void) 
{
    return (uint8)((BL_DR & BL_MASK) >> BL_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(BL_INTSTAT) 

    /*******************************************************************************
    * Function Name: BL_ClearInterrupt
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
    uint8 BL_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(BL_INTSTAT & BL_MASK);
		BL_INTSTAT = maskedStatus;
        return maskedStatus >> BL_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
