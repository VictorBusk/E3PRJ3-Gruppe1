/*******************************************************************************
* File Name: SPIS.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
*
* Note:
*
*******************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIS_PVT.h"

#if (SPIS_SCB_MODE_I2C_INC)
    #include "SPIS_I2C_PVT.h"
#endif /* (SPIS_SCB_MODE_I2C_INC) */

#if (SPIS_SCB_MODE_EZI2C_INC)
    #include "SPIS_EZI2C_PVT.h"
#endif /* (SPIS_SCB_MODE_EZI2C_INC) */

#if (SPIS_SCB_MODE_SPI_INC || SPIS_SCB_MODE_UART_INC)
    #include "SPIS_SPI_UART_PVT.h"
#endif /* (SPIS_SCB_MODE_SPI_INC || SPIS_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 SPIS_scbMode = SPIS_SCB_MODE_UNCONFIG;
    uint8 SPIS_scbEnableWake;
    uint8 SPIS_scbEnableIntr;

    /* I2C configuration variables */
    uint8 SPIS_mode;
    uint8 SPIS_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * SPIS_rxBuffer;
    uint8  SPIS_rxDataBits;
    uint32 SPIS_rxBufferSize;

    volatile uint8 * SPIS_txBuffer;
    uint8  SPIS_txDataBits;
    uint32 SPIS_txBufferSize;

    /* EZI2C configuration variables */
    uint8 SPIS_numberOfAddr;
    uint8 SPIS_subAddrSize;
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 SPIS_initVar = 0u;

#if (SPIS_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SPIS_CUSTOM_INTR_HANDLER)
    void (*SPIS_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_SPIS_CUSTOM_INTR_HANDLER) */
#endif /* (SPIS_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void SPIS_ScbEnableIntr(void);
static void SPIS_ScbModeStop(void);
static void SPIS_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: SPIS_Init
********************************************************************************
*
* Summary:
*  Initializes the SCB component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  SCB_I2CInit, SCB_SpiInit, SCB_UartInit or SCB_EzI2CInit.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIS_Init(void)
{
#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPIS_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPIS_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (SPIS_SCB_MODE_I2C_CONST_CFG)
    SPIS_I2CInit();

#elif (SPIS_SCB_MODE_SPI_CONST_CFG)
    SPIS_SpiInit();

#elif (SPIS_SCB_MODE_UART_CONST_CFG)
    SPIS_UartInit();

#elif (SPIS_SCB_MODE_EZI2C_CONST_CFG)
    SPIS_EzI2CInit();

#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIS_Enable
********************************************************************************
*
* Summary:
*  Enables the SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIS_Enable(void)
{
#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!SPIS_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPIS_CTRL_REG |= SPIS_CTRL_ENABLED;

        SPIS_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        SPIS_ScbModePostEnable();
    }
#else
    SPIS_CTRL_REG |= SPIS_CTRL_ENABLED;

    SPIS_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    SPIS_ScbModePostEnable();
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIS_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZ I2C. Otherwise this function does not enable the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SPIS_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SPIS_Start(void)
{
    if (0u == SPIS_initVar)
    {
        SPIS_Init();
        SPIS_initVar = 1u; /* Component was initialized */
    }

    SPIS_Enable();
}


/*******************************************************************************
* Function Name: SPIS_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component and its interrupt.
*  It also disables all TX interrupt sources so as not to cause an unexpected
*  interrupt trigger because after the component is enabled, the TX FIFO 
*  is empty.
*
* Parameters:
*  None
*
* Return:
*  None
* 
*******************************************************************************/
void SPIS_Stop(void)
{
#if (SPIS_SCB_IRQ_INTERNAL)
    SPIS_DisableInt();
#endif /* (SPIS_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    SPIS_ScbModeStop();

    /* Disable SCB IP */
    SPIS_CTRL_REG &= (uint32) ~SPIS_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    SPIS_SetTxInterruptMode(SPIS_NO_INTR_SOURCES);

#if (SPIS_SCB_IRQ_INTERNAL)
    SPIS_ClearPendingInt();
#endif /* (SPIS_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPIS_SetRxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the RX FIFO to generate RX level interrupt.
*         The range of valid level values is between 0 and RX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void SPIS_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = SPIS_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~SPIS_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (SPIS_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPIS_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: SPIS_SetTxFifoLevel
********************************************************************************
*
* Summary:
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has more entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
* Parameters:
*  level: Level in the TX FIFO to generate TX level interrupt.
*         The range of valid level values is between 0 and TX FIFO depth - 1.
*
* Return:
*  None
*
*******************************************************************************/
void SPIS_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = SPIS_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~SPIS_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (SPIS_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    SPIS_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (SPIS_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: SPIS_SetCustomInterruptHandler
    ********************************************************************************
    *
    * Summary:
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    * Parameters:
    *  func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_SPIS_CUSTOM_INTR_HANDLER)
        SPIS_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_SPIS_CUSTOM_INTR_HANDLER) */
    }
#endif /* (SPIS_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: SPIS_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables an interrupt for a specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SPIS_ScbEnableIntr(void)
{
#if (SPIS_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != SPIS_scbEnableIntr)
        {
            SPIS_EnableInt();
        }

    #else
        SPIS_EnableInt();

    #endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SPIS_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPIS_ScbModePostEnable
********************************************************************************
*
* Summary:
*  Calls the PostEnable function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SPIS_ScbModePostEnable(void)
{
#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!SPIS_CY_SCBIP_V1)
    if (SPIS_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPIS_SpiPostEnable();
    }
    else if (SPIS_SCB_MODE_UART_RUNTM_CFG)
    {
        SPIS_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!SPIS_CY_SCBIP_V1) */

#elif (SPIS_SCB_MODE_SPI_CONST_CFG)
    SPIS_SpiPostEnable();

#elif (SPIS_SCB_MODE_UART_CONST_CFG)
    SPIS_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPIS_ScbModeStop
********************************************************************************
*
* Summary:
*  Calls the Stop function for a specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SPIS_ScbModeStop(void)
{
#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    if (SPIS_SCB_MODE_I2C_RUNTM_CFG)
    {
        SPIS_I2CStop();
    }
    else if (SPIS_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SPIS_EzI2CStop();
    }
#if (!SPIS_CY_SCBIP_V1)
    else if (SPIS_SCB_MODE_SPI_RUNTM_CFG)
    {
        SPIS_SpiStop();
    }
    else if (SPIS_SCB_MODE_UART_RUNTM_CFG)
    {
        SPIS_UartStop();
    }
#endif /* (!SPIS_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (SPIS_SCB_MODE_I2C_CONST_CFG)
    SPIS_I2CStop();

#elif (SPIS_SCB_MODE_EZI2C_CONST_CFG)
    SPIS_EzI2CStop();

#elif (SPIS_SCB_MODE_SPI_CONST_CFG)
    SPIS_SpiStop();

#elif (SPIS_SCB_MODE_UART_CONST_CFG)
    SPIS_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SPIS_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPIS_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [SPIS_SCB_PINS_NUMBER];
        uint32 pinsDm   [SPIS_SCB_PINS_NUMBER];

    #if (!SPIS_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!SPIS_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < SPIS_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = SPIS_HSIOM_DEF_SEL;
            pinsDm[i]    = SPIS_PIN_DM_ALG_HIZ;
        }

        if ((SPIS_SCB_MODE_I2C   == mode) ||
           (SPIS_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_HSIOM_I2C_SEL;
            hsiomSel[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_HSIOM_I2C_SEL;

            pinsDm[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_PIN_DM_OD_LO;
            pinsDm[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_PIN_DM_OD_LO;
        }
    #if (!SPIS_CY_SCBIP_V1)
        else if (SPIS_SCB_MODE_SPI == mode)
        {
            hsiomSel[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
            hsiomSel[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
            hsiomSel[SPIS_SCLK_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;

            if (SPIS_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;
                pinsDm[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsDm[SPIS_SCLK_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;

            #if (SPIS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SPIS_SS0_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
                pinsDm  [SPIS_SS0_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;
            #endif /* (SPIS_SS0_PIN) */

            #if (SPIS_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= SPIS_TX_SDA_MISO_PIN_MASK;
            #endif /* (SPIS_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsDm[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;
                pinsDm[SPIS_SCLK_PIN_INDEX] = SPIS_PIN_DM_STRONG;

            #if (SPIS_SS0_PIN)
                hsiomSel [SPIS_SS0_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
                pinsDm   [SPIS_SS0_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsInBuf |= SPIS_SS0_PIN_MASK;
            #endif /* (SPIS_SS0_PIN) */

            #if (SPIS_SS1_PIN)
                hsiomSel [SPIS_SS1_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
                pinsDm   [SPIS_SS1_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsInBuf |= SPIS_SS1_PIN_MASK;
            #endif /* (SPIS_SS1_PIN) */

            #if (SPIS_SS2_PIN)
                hsiomSel [SPIS_SS2_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
                pinsDm   [SPIS_SS2_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsInBuf |= SPIS_SS2_PIN_MASK;
            #endif /* (SPIS_SS2_PIN) */

            #if (SPIS_SS3_PIN)
                hsiomSel [SPIS_SS3_PIN_INDEX] = SPIS_HSIOM_SPI_SEL;
                pinsDm   [SPIS_SS3_PIN_INDEX] = SPIS_PIN_DM_STRONG;
                pinsInBuf |= SPIS_SS3_PIN_MASK;
            #endif /* (SPIS_SS3_PIN) */

                /* Disable input buffers */
            #if (SPIS_RX_SCL_MOSI_PIN)
                pinsInBuf |= SPIS_RX_SCL_MOSI_PIN_MASK;
            #endif /* (SPIS_RX_SCL_MOSI_PIN) */

             #if (SPIS_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= SPIS_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (SPIS_RX_WAKE_SCL_MOSI_PIN) */

            #if (SPIS_SCLK_PIN)
                pinsInBuf |= SPIS_SCLK_PIN_MASK;
            #endif /* (SPIS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (SPIS_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_HSIOM_UART_SEL;
                pinsDm  [SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (SPIS_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_HSIOM_UART_SEL;
                    pinsDm  [SPIS_RX_SCL_MOSI_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;
                }

                if (0u != (SPIS_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_HSIOM_UART_SEL;
                    pinsDm  [SPIS_TX_SDA_MISO_PIN_INDEX] = SPIS_PIN_DM_STRONG;

                #if (SPIS_TX_SDA_MISO_PIN)
                     pinsInBuf |= SPIS_TX_SDA_MISO_PIN_MASK;
                #endif /* (SPIS_TX_SDA_MISO_PIN) */
                }

            #if !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
                if (SPIS_UART_MODE_STD == subMode)
                {
                    if (0u != (SPIS_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[SPIS_SCLK_PIN_INDEX] = SPIS_HSIOM_UART_SEL;
                        pinsDm  [SPIS_SCLK_PIN_INDEX] = SPIS_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (SPIS_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[SPIS_SS0_PIN_INDEX] = SPIS_HSIOM_UART_SEL;
                        pinsDm  [SPIS_SS0_PIN_INDEX] = SPIS_PIN_DM_STRONG;

                    #if (SPIS_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= SPIS_SS0_PIN_MASK;
                    #endif /* (SPIS_SS0_PIN) */
                    }
                }
            #endif /* !(SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */
            }
        }
    #endif /* (!SPIS_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (SPIS_RX_WAKE_SCL_MOSI_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       SPIS_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       SPIS_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[SPIS_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPIS_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[SPIS_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     SPIS_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SPIS_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        SPIS_SET_INCFG_TYPE(SPIS_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        SPIS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        SPIS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        SPIS_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (SPIS_RX_WAKE_SCL_MOSI_PIN) */

    #if (SPIS_RX_SCL_MOSI_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_RX_SCL_MOSI_HSIOM_REG,
                                       SPIS_RX_SCL_MOSI_HSIOM_MASK,
                                       SPIS_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[SPIS_RX_SCL_MOSI_PIN_INDEX]);

        SPIS_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[SPIS_RX_SCL_MOSI_PIN_INDEX]);

    #if (!SPIS_CY_SCBIP_V1)
        SPIS_SET_INP_DIS(SPIS_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     SPIS_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & SPIS_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!SPIS_CY_SCBIP_V1) */
    #endif /* (SPIS_RX_SCL_MOSI_PIN) */

    #if (SPIS_TX_SDA_MISO_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_TX_SDA_MISO_HSIOM_REG,
                                       SPIS_TX_SDA_MISO_HSIOM_MASK,
                                       SPIS_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[SPIS_TX_SDA_MISO_PIN_INDEX]);

        SPIS_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[SPIS_TX_SDA_MISO_PIN_INDEX]);

    #if (!SPIS_CY_SCBIP_V1)
        SPIS_SET_INP_DIS(SPIS_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     SPIS_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & SPIS_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!SPIS_CY_SCBIP_V1) */
    #endif /* (SPIS_RX_SCL_MOSI_PIN) */

    #if (SPIS_SCLK_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_SCLK_HSIOM_REG,
                                       SPIS_SCLK_HSIOM_MASK,
                                       SPIS_SCLK_HSIOM_POS,
                                       hsiomSel[SPIS_SCLK_PIN_INDEX]);

        SPIS_spi_sclk_SetDriveMode((uint8) pinsDm[SPIS_SCLK_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_spi_sclk_INP_DIS,
                                     SPIS_spi_sclk_MASK,
                                     (0u != (pinsInBuf & SPIS_SCLK_PIN_MASK)));
    #endif /* (SPIS_SCLK_PIN) */

    #if (SPIS_SS0_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_SS0_HSIOM_REG,
                                       SPIS_SS0_HSIOM_MASK,
                                       SPIS_SS0_HSIOM_POS,
                                       hsiomSel[SPIS_SS0_PIN_INDEX]);

        SPIS_spi_ss0_SetDriveMode((uint8) pinsDm[SPIS_SS0_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_spi_ss0_INP_DIS,
                                     SPIS_spi_ss0_MASK,
                                     (0u != (pinsInBuf & SPIS_SS0_PIN_MASK)));
    #endif /* (SPIS_SS0_PIN) */

    #if (SPIS_SS1_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_SS1_HSIOM_REG,
                                       SPIS_SS1_HSIOM_MASK,
                                       SPIS_SS1_HSIOM_POS,
                                       hsiomSel[SPIS_SS1_PIN_INDEX]);

        SPIS_spi_ss1_SetDriveMode((uint8) pinsDm[SPIS_SS1_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_spi_ss1_INP_DIS,
                                     SPIS_spi_ss1_MASK,
                                     (0u != (pinsInBuf & SPIS_SS1_PIN_MASK)));
    #endif /* (SPIS_SS1_PIN) */

    #if (SPIS_SS2_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_SS2_HSIOM_REG,
                                       SPIS_SS2_HSIOM_MASK,
                                       SPIS_SS2_HSIOM_POS,
                                       hsiomSel[SPIS_SS2_PIN_INDEX]);

        SPIS_spi_ss2_SetDriveMode((uint8) pinsDm[SPIS_SS2_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_spi_ss2_INP_DIS,
                                     SPIS_spi_ss2_MASK,
                                     (0u != (pinsInBuf & SPIS_SS2_PIN_MASK)));
    #endif /* (SPIS_SS2_PIN) */

    #if (SPIS_SS3_PIN)
        SPIS_SET_HSIOM_SEL(SPIS_SS3_HSIOM_REG,
                                       SPIS_SS3_HSIOM_MASK,
                                       SPIS_SS3_HSIOM_POS,
                                       hsiomSel[SPIS_SS3_PIN_INDEX]);

        SPIS_spi_ss3_SetDriveMode((uint8) pinsDm[SPIS_SS3_PIN_INDEX]);

        SPIS_SET_INP_DIS(SPIS_spi_ss3_INP_DIS,
                                     SPIS_spi_ss3_MASK,
                                     (0u != (pinsInBuf & SPIS_SS3_PIN_MASK)));
    #endif /* (SPIS_SS3_PIN) */
    }

#endif /* (SPIS_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SPIS_I2CSlaveNackGeneration
    ********************************************************************************
    *
    * Summary:
    *  Sets command to generate NACK to the address or data.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPIS_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (SPIS_CTRL_REG & SPIS_CTRL_EC_AM_MODE)) &&
            (0u == (SPIS_I2C_CTRL_REG & SPIS_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            SPIS_CTRL_REG &= ~SPIS_CTRL_EC_AM_MODE;
            SPIS_CTRL_REG |=  SPIS_CTRL_EC_AM_MODE;
        }

        SPIS_I2C_SLAVE_CMD_REG = SPIS_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (SPIS_CY_SCBIP_V0 || SPIS_CY_SCBIP_V1) */


/* [] END OF FILE */
