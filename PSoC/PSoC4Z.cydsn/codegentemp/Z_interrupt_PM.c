/*******************************************************************************
* File Name: Z_interrupt.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Z_interrupt.h"

static Z_interrupt_BACKUP_STRUCT  Z_interrupt_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Z_interrupt_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Z_interrupt_SUT.c usage_Z_interrupt_Sleep_Wakeup
*******************************************************************************/
void Z_interrupt_Sleep(void)
{
    #if defined(Z_interrupt__PC)
        Z_interrupt_backup.pcState = Z_interrupt_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Z_interrupt_backup.usbState = Z_interrupt_CR1_REG;
            Z_interrupt_USB_POWER_REG |= Z_interrupt_USBIO_ENTER_SLEEP;
            Z_interrupt_CR1_REG &= Z_interrupt_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Z_interrupt__SIO)
        Z_interrupt_backup.sioState = Z_interrupt_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Z_interrupt_SIO_REG &= (uint32)(~Z_interrupt_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Z_interrupt_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Z_interrupt_Sleep() for an example usage.
*******************************************************************************/
void Z_interrupt_Wakeup(void)
{
    #if defined(Z_interrupt__PC)
        Z_interrupt_PC = Z_interrupt_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Z_interrupt_USB_POWER_REG &= Z_interrupt_USBIO_EXIT_SLEEP_PH1;
            Z_interrupt_CR1_REG = Z_interrupt_backup.usbState;
            Z_interrupt_USB_POWER_REG &= Z_interrupt_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Z_interrupt__SIO)
        Z_interrupt_SIO_REG = Z_interrupt_backup.sioState;
    #endif
}


/* [] END OF FILE */
