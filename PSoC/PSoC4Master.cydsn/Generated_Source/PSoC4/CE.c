/*******************************************************************************
* File Name: CE.c  
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
#include "CE.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        CE_PC =   (CE_PC & \
                                (uint32)(~(uint32)(CE_DRIVE_MODE_IND_MASK << (CE_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (CE_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: CE_Write
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
void CE_Write(uint8 value) 
{
    uint8 drVal = (uint8)(CE_DR & (uint8)(~CE_MASK));
    drVal = (drVal | ((uint8)(value << CE_SHIFT) & CE_MASK));
    CE_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: CE_SetDriveMode
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
void CE_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(CE__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: CE_Read
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
*  Macro CE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 CE_Read(void) 
{
    return (uint8)((CE_PS & CE_MASK) >> CE_SHIFT);
}


/*******************************************************************************
* Function Name: CE_ReadDataReg
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
uint8 CE_ReadDataReg(void) 
{
    return (uint8)((CE_DR & CE_MASK) >> CE_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(CE_INTSTAT) 

    /*******************************************************************************
    * Function Name: CE_ClearInterrupt
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
    uint8 CE_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(CE_INTSTAT & CE_MASK);
		CE_INTSTAT = maskedStatus;
        return maskedStatus >> CE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
