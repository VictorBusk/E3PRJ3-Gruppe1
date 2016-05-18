/*******************************************************************************
* File Name: DistEcho.c  
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
#include "DistEcho.h"

static DistEcho_BACKUP_STRUCT  DistEcho_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DistEcho_Sleep
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
*  \snippet DistEcho_SUT.c usage_DistEcho_Sleep_Wakeup
*******************************************************************************/
void DistEcho_Sleep(void)
{
    #if defined(DistEcho__PC)
        DistEcho_backup.pcState = DistEcho_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DistEcho_backup.usbState = DistEcho_CR1_REG;
            DistEcho_USB_POWER_REG |= DistEcho_USBIO_ENTER_SLEEP;
            DistEcho_CR1_REG &= DistEcho_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DistEcho__SIO)
        DistEcho_backup.sioState = DistEcho_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DistEcho_SIO_REG &= (uint32)(~DistEcho_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DistEcho_Wakeup
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
*  Refer to DistEcho_Sleep() for an example usage.
*******************************************************************************/
void DistEcho_Wakeup(void)
{
    #if defined(DistEcho__PC)
        DistEcho_PC = DistEcho_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DistEcho_USB_POWER_REG &= DistEcho_USBIO_EXIT_SLEEP_PH1;
            DistEcho_CR1_REG = DistEcho_backup.usbState;
            DistEcho_USB_POWER_REG &= DistEcho_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DistEcho__SIO)
        DistEcho_SIO_REG = DistEcho_backup.sioState;
    #endif
}


/* [] END OF FILE */
