/*******************************************************************************
* File Name: DistTrigger.c  
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
#include "DistTrigger.h"

static DistTrigger_BACKUP_STRUCT  DistTrigger_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DistTrigger_Sleep
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
*  \snippet DistTrigger_SUT.c usage_DistTrigger_Sleep_Wakeup
*******************************************************************************/
void DistTrigger_Sleep(void)
{
    #if defined(DistTrigger__PC)
        DistTrigger_backup.pcState = DistTrigger_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DistTrigger_backup.usbState = DistTrigger_CR1_REG;
            DistTrigger_USB_POWER_REG |= DistTrigger_USBIO_ENTER_SLEEP;
            DistTrigger_CR1_REG &= DistTrigger_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DistTrigger__SIO)
        DistTrigger_backup.sioState = DistTrigger_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DistTrigger_SIO_REG &= (uint32)(~DistTrigger_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DistTrigger_Wakeup
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
*  Refer to DistTrigger_Sleep() for an example usage.
*******************************************************************************/
void DistTrigger_Wakeup(void)
{
    #if defined(DistTrigger__PC)
        DistTrigger_PC = DistTrigger_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DistTrigger_USB_POWER_REG &= DistTrigger_USBIO_EXIT_SLEEP_PH1;
            DistTrigger_CR1_REG = DistTrigger_backup.usbState;
            DistTrigger_USB_POWER_REG &= DistTrigger_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DistTrigger__SIO)
        DistTrigger_SIO_REG = DistTrigger_backup.sioState;
    #endif
}


/* [] END OF FILE */
