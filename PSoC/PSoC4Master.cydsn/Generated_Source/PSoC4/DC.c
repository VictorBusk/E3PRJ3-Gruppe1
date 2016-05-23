/*******************************************************************************
* File Name: DC.c  
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
#include "DC.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        DC_PC =   (DC_PC & \
                                (uint32)(~(uint32)(DC_DRIVE_MODE_IND_MASK << (DC_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (DC_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: DC_Write
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
void DC_Write(uint8 value) 
{
    uint8 drVal = (uint8)(DC_DR & (uint8)(~DC_MASK));
    drVal = (drVal | ((uint8)(value << DC_SHIFT) & DC_MASK));
    DC_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: DC_SetDriveMode
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
void DC_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(DC__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: DC_Read
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
*  Macro DC_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 DC_Read(void) 
{
    return (uint8)((DC_PS & DC_MASK) >> DC_SHIFT);
}


/*******************************************************************************
* Function Name: DC_ReadDataReg
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
uint8 DC_ReadDataReg(void) 
{
    return (uint8)((DC_DR & DC_MASK) >> DC_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(DC_INTSTAT) 

    /*******************************************************************************
    * Function Name: DC_ClearInterrupt
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
    uint8 DC_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(DC_INTSTAT & DC_MASK);
		DC_INTSTAT = maskedStatus;
        return maskedStatus >> DC_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
