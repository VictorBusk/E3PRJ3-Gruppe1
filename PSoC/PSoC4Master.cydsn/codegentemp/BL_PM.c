/*******************************************************************************
* File Name: BL.c  
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
#include "BL.h"

static BL_BACKUP_STRUCT  BL_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BL_Sleep
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
*  \snippet BL_SUT.c usage_BL_Sleep_Wakeup
*******************************************************************************/
void BL_Sleep(void)
{
    #if defined(BL__PC)
        BL_backup.pcState = BL_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BL_backup.usbState = BL_CR1_REG;
            BL_USB_POWER_REG |= BL_USBIO_ENTER_SLEEP;
            BL_CR1_REG &= BL_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BL__SIO)
        BL_backup.sioState = BL_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BL_SIO_REG &= (uint32)(~BL_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BL_Wakeup
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
*  Refer to BL_Sleep() for an example usage.
*******************************************************************************/
void BL_Wakeup(void)
{
    #if defined(BL__PC)
        BL_PC = BL_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BL_USB_POWER_REG &= BL_USBIO_EXIT_SLEEP_PH1;
            BL_CR1_REG = BL_backup.usbState;
            BL_USB_POWER_REG &= BL_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BL__SIO)
        BL_SIO_REG = BL_backup.sioState;
    #endif
}


/* [] END OF FILE */
