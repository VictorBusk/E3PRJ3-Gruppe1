/*******************************************************************************
* File Name: Knap.c  
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
#include "Knap.h"

static Knap_BACKUP_STRUCT  Knap_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Knap_Sleep
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
*  \snippet Knap_SUT.c usage_Knap_Sleep_Wakeup
*******************************************************************************/
void Knap_Sleep(void)
{
    #if defined(Knap__PC)
        Knap_backup.pcState = Knap_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Knap_backup.usbState = Knap_CR1_REG;
            Knap_USB_POWER_REG |= Knap_USBIO_ENTER_SLEEP;
            Knap_CR1_REG &= Knap_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Knap__SIO)
        Knap_backup.sioState = Knap_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Knap_SIO_REG &= (uint32)(~Knap_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Knap_Wakeup
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
*  Refer to Knap_Sleep() for an example usage.
*******************************************************************************/
void Knap_Wakeup(void)
{
    #if defined(Knap__PC)
        Knap_PC = Knap_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Knap_USB_POWER_REG &= Knap_USBIO_EXIT_SLEEP_PH1;
            Knap_CR1_REG = Knap_backup.usbState;
            Knap_USB_POWER_REG &= Knap_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Knap__SIO)
        Knap_SIO_REG = Knap_backup.sioState;
    #endif
}


/* [] END OF FILE */
