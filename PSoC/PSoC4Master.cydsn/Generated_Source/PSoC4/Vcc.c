/*******************************************************************************
* File Name: Vcc.c  
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
#include "Vcc.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Vcc_PC =   (Vcc_PC & \
                                (uint32)(~(uint32)(Vcc_DRIVE_MODE_IND_MASK << (Vcc_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Vcc_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Vcc_Write
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
void Vcc_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Vcc_DR & (uint8)(~Vcc_MASK));
    drVal = (drVal | ((uint8)(value << Vcc_SHIFT) & Vcc_MASK));
    Vcc_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Vcc_SetDriveMode
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
void Vcc_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Vcc__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Vcc_Read
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
*  Macro Vcc_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Vcc_Read(void) 
{
    return (uint8)((Vcc_PS & Vcc_MASK) >> Vcc_SHIFT);
}


/*******************************************************************************
* Function Name: Vcc_ReadDataReg
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
uint8 Vcc_ReadDataReg(void) 
{
    return (uint8)((Vcc_DR & Vcc_MASK) >> Vcc_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Vcc_INTSTAT) 

    /*******************************************************************************
    * Function Name: Vcc_ClearInterrupt
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
    uint8 Vcc_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Vcc_INTSTAT & Vcc_MASK);
		Vcc_INTSTAT = maskedStatus;
        return maskedStatus >> Vcc_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
