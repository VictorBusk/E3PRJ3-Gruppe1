/*******************************************************************************
* File Name: LumenCom_I2C.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LumenCom_PVT.h"
#include "LumenCom_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 LumenCom_state;  /* Current state of I2C FSM */

#if(LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const LumenCom_I2C_INIT_STRUCT LumenCom_configI2C =
    {
        LumenCom_I2C_MODE,
        LumenCom_I2C_OVS_FACTOR_LOW,
        LumenCom_I2C_OVS_FACTOR_HIGH,
        LumenCom_I2C_MEDIAN_FILTER_ENABLE,
        LumenCom_I2C_SLAVE_ADDRESS,
        LumenCom_I2C_SLAVE_ADDRESS_MASK,
        LumenCom_I2C_ACCEPT_ADDRESS,
        LumenCom_I2C_WAKE_ENABLE,
        LumenCom_I2C_BYTE_MODE_ENABLE,
        LumenCom_I2C_DATA_RATE,
        LumenCom_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: LumenCom_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for I2C operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LumenCom_I2CInit(const LumenCom_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            LumenCom_SetPins(LumenCom_SCB_MODE_I2C, LumenCom_DUMMY_PARAM,
                                     LumenCom_DUMMY_PARAM);

            /* Store internal configuration */
            LumenCom_scbMode       = (uint8) LumenCom_SCB_MODE_I2C;
            LumenCom_scbEnableWake = (uint8) config->enableWake;
            LumenCom_scbEnableIntr = (uint8) LumenCom_SCB_IRQ_INTERNAL;

            LumenCom_mode          = (uint8) config->mode;
            LumenCom_acceptAddr    = (uint8) config->acceptAddr;

        #if (LumenCom_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            LumenCom_SET_I2C_CFG_SDA_FILT_TRIM(LumenCom_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (LumenCom_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((LumenCom_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= LumenCom_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (LumenCom_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                LumenCom_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = LumenCom_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                LumenCom_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = LumenCom_DIGITAL_FILTER_ENABLE;
            }

        #if (!LumenCom_CY_SCBIP_V0)
            locEnableWake = (LumenCom_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!LumenCom_CY_SCBIP_V0) */

            /* Configure I2C interface */
            LumenCom_CTRL_REG     = LumenCom_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            LumenCom_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            LumenCom_GET_CTRL_EC_AM_MODE (locEnableWake);

            LumenCom_I2C_CTRL_REG = LumenCom_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    LumenCom_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    LumenCom_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    LumenCom_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            LumenCom_RX_CTRL_REG      = LumenCom_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                LumenCom_I2C_RX_CTRL;
            LumenCom_RX_FIFO_CTRL_REG = LumenCom_CLEAR_REG;

            /* Set default address and mask */
            LumenCom_RX_MATCH_REG    = ((LumenCom_I2C_SLAVE) ?
                                                (LumenCom_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 LumenCom_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (LumenCom_CLEAR_REG));


            /* Configure TX direction */
            LumenCom_TX_CTRL_REG      = LumenCom_I2C_TX_CTRL;
            LumenCom_TX_FIFO_CTRL_REG = LumenCom_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (LumenCom_ISR_NUMBER);
            CyIntSetPriority(LumenCom_ISR_NUMBER, LumenCom_ISR_PRIORITY);
            (void) CyIntSetVector(LumenCom_ISR_NUMBER, &LumenCom_I2C_ISR);

            /* Configure interrupt sources */
        #if(!LumenCom_CY_SCBIP_V1)
            LumenCom_INTR_SPI_EC_MASK_REG = LumenCom_NO_INTR_SOURCES;
        #endif /* (!LumenCom_CY_SCBIP_V1) */

            LumenCom_INTR_I2C_EC_MASK_REG = LumenCom_NO_INTR_SOURCES;
            LumenCom_INTR_RX_MASK_REG     = LumenCom_NO_INTR_SOURCES;
            LumenCom_INTR_TX_MASK_REG     = LumenCom_NO_INTR_SOURCES;

            LumenCom_INTR_SLAVE_MASK_REG  = ((LumenCom_I2C_SLAVE) ?
                            (LumenCom_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             LumenCom_I2C_INTR_SLAVE_MASK) : (LumenCom_CLEAR_REG));

            LumenCom_INTR_MASTER_MASK_REG = ((LumenCom_I2C_MASTER) ?
                                                     (LumenCom_I2C_INTR_MASTER_MASK) :
                                                     (LumenCom_CLEAR_REG));

            /* Configure global variables */
            LumenCom_state = LumenCom_I2C_FSM_IDLE;

            /* Internal slave variables */
            LumenCom_slStatus        = 0u;
            LumenCom_slRdBufIndex    = 0u;
            LumenCom_slWrBufIndex    = 0u;
            LumenCom_slOverFlowCount = 0u;

            /* Internal master variables */
            LumenCom_mstrStatus     = 0u;
            LumenCom_mstrRdBufIndex = 0u;
            LumenCom_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: LumenCom_I2CInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for the I2C operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LumenCom_I2CInit(void)
    {
    #if(LumenCom_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        LumenCom_SET_I2C_CFG_SDA_FILT_TRIM(LumenCom_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (LumenCom_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        LumenCom_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        LumenCom_CTRL_REG     = LumenCom_I2C_DEFAULT_CTRL;
        LumenCom_I2C_CTRL_REG = LumenCom_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        LumenCom_RX_CTRL_REG      = LumenCom_I2C_DEFAULT_RX_CTRL;
        LumenCom_RX_FIFO_CTRL_REG = LumenCom_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        LumenCom_RX_MATCH_REG     = LumenCom_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        LumenCom_TX_CTRL_REG      = LumenCom_I2C_DEFAULT_TX_CTRL;
        LumenCom_TX_FIFO_CTRL_REG = LumenCom_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (LumenCom_ISR_NUMBER);
        CyIntSetPriority(LumenCom_ISR_NUMBER, LumenCom_ISR_PRIORITY);
    #if(!LumenCom_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(LumenCom_ISR_NUMBER, &LumenCom_I2C_ISR);
    #endif /* (LumenCom_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!LumenCom_CY_SCBIP_V1)
        LumenCom_INTR_SPI_EC_MASK_REG = LumenCom_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!LumenCom_CY_SCBIP_V1) */

        LumenCom_INTR_I2C_EC_MASK_REG = LumenCom_I2C_DEFAULT_INTR_I2C_EC_MASK;
        LumenCom_INTR_SLAVE_MASK_REG  = LumenCom_I2C_DEFAULT_INTR_SLAVE_MASK;
        LumenCom_INTR_MASTER_MASK_REG = LumenCom_I2C_DEFAULT_INTR_MASTER_MASK;
        LumenCom_INTR_RX_MASK_REG     = LumenCom_I2C_DEFAULT_INTR_RX_MASK;
        LumenCom_INTR_TX_MASK_REG     = LumenCom_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        LumenCom_state = LumenCom_I2C_FSM_IDLE;

    #if(LumenCom_I2C_SLAVE)
        /* Internal slave variable */
        LumenCom_slStatus        = 0u;
        LumenCom_slRdBufIndex    = 0u;
        LumenCom_slWrBufIndex    = 0u;
        LumenCom_slOverFlowCount = 0u;
    #endif /* (LumenCom_I2C_SLAVE) */

    #if(LumenCom_I2C_MASTER)
    /* Internal master variable */
        LumenCom_mstrStatus     = 0u;
        LumenCom_mstrRdBufIndex = 0u;
        LumenCom_mstrWrBufIndex = 0u;
    #endif /* (LumenCom_I2C_MASTER) */
    }
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: LumenCom_I2CStop
********************************************************************************
*
* Summary:
*  Resets the I2C FSM into the default state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void LumenCom_I2CStop(void)
{
    LumenCom_state = LumenCom_I2C_FSM_IDLE;
}


#if(LumenCom_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LumenCom_I2CSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Enables LumenCom_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LumenCom_I2CSaveConfig(void)
    {
    #if (!LumenCom_CY_SCBIP_V0)
        #if (LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (LumenCom_CTRL_REG & LumenCom_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                LumenCom_Stop();
                LumenCom_CTRL_REG |= LumenCom_CTRL_EC_AM_MODE;
                LumenCom_Enable();
            }
        #endif /* (LumenCom_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (LumenCom_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            LumenCom_SCBCLK_Stop();
        #endif /* (LumenCom_SCB_CLK_INTERNAL) */
    #endif /* (!LumenCom_CY_SCBIP_V0) */

        LumenCom_SetI2CExtClkInterruptMode(LumenCom_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: LumenCom_I2CRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Disables LumenCom_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void LumenCom_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        LumenCom_SetI2CExtClkInterruptMode(LumenCom_NO_INTR_SOURCES);

    #if (!LumenCom_CY_SCBIP_V0)
        #if (LumenCom_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            LumenCom_SCBCLK_Start();
        #endif /* (LumenCom_SCB_CLK_INTERNAL) */
    #endif /* (!LumenCom_CY_SCBIP_V0) */
    }
#endif /* (LumenCom_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
