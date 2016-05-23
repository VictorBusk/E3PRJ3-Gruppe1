/*******************************************************************************
* File Name: Gnd.c  
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
#include "Gnd.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Gnd_PC =   (Gnd_PC & \
                                (uint32)(~(uint32)(Gnd_DRIVE_MODE_IND_MASK << (Gnd_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Gnd_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Gnd_Write
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
void Gnd_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Gnd_DR & (uint8)(~Gnd_MASK));
    drVal = (drVal | ((uint8)(value << Gnd_SHIFT) & Gnd_MASK));
    Gnd_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Gnd_SetDriveMode
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
void Gnd_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Gnd__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Gnd_Read
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
*  Macro Gnd_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Gnd_Read(void) 
{
    return (uint8)((Gnd_PS & Gnd_MASK) >> Gnd_SHIFT);
}


/*******************************************************************************
* Function Name: Gnd_ReadDataReg
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
uint8 Gnd_ReadDataReg(void) 
{
    return (uint8)((Gnd_DR & Gnd_MASK) >> Gnd_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Gnd_INTSTAT) 

    /*******************************************************************************
    * Function Name: Gnd_ClearInterrupt
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
    uint8 Gnd_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Gnd_INTSTAT & Gnd_MASK);
		Gnd_INTSTAT = maskedStatus;
        return maskedStatus >> Gnd_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
