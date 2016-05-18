/*******************************************************************************
* File Name: Debug.c
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

#include "Debug_PVT.h"

#if (Debug_SCB_MODE_I2C_INC)
    #include "Debug_I2C_PVT.h"
#endif /* (Debug_SCB_MODE_I2C_INC) */

#if (Debug_SCB_MODE_EZI2C_INC)
    #include "Debug_EZI2C_PVT.h"
#endif /* (Debug_SCB_MODE_EZI2C_INC) */

#if (Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC)
    #include "Debug_SPI_UART_PVT.h"
#endif /* (Debug_SCB_MODE_SPI_INC || Debug_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 Debug_scbMode = Debug_SCB_MODE_UNCONFIG;
    uint8 Debug_scbEnableWake;
    uint8 Debug_scbEnableIntr;

    /* I2C configuration variables */
    uint8 Debug_mode;
    uint8 Debug_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * Debug_rxBuffer;
    uint8  Debug_rxDataBits;
    uint32 Debug_rxBufferSize;

    volatile uint8 * Debug_txBuffer;
    uint8  Debug_txDataBits;
    uint32 Debug_txBufferSize;

    /* EZI2C configuration variables */
    uint8 Debug_numberOfAddr;
    uint8 Debug_subAddrSize;
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 Debug_initVar = 0u;

#if (Debug_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER)
    void (*Debug_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER) */
#endif /* (Debug_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void Debug_ScbEnableIntr(void);
static void Debug_ScbModeStop(void);
static void Debug_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: Debug_Init
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
void Debug_Init(void)
{
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    if (Debug_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Debug_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (Debug_SCB_MODE_I2C_CONST_CFG)
    Debug_I2CInit();

#elif (Debug_SCB_MODE_SPI_CONST_CFG)
    Debug_SpiInit();

#elif (Debug_SCB_MODE_UART_CONST_CFG)
    Debug_UartInit();

#elif (Debug_SCB_MODE_EZI2C_CONST_CFG)
    Debug_EzI2CInit();

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Debug_Enable
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
void Debug_Enable(void)
{
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!Debug_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        Debug_CTRL_REG |= Debug_CTRL_ENABLED;

        Debug_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        Debug_ScbModePostEnable();
    }
#else
    Debug_CTRL_REG |= Debug_CTRL_ENABLED;

    Debug_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    Debug_ScbModePostEnable();
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Debug_Start
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
*  Debug_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void Debug_Start(void)
{
    if (0u == Debug_initVar)
    {
        Debug_Init();
        Debug_initVar = 1u; /* Component was initialized */
    }

    Debug_Enable();
}


/*******************************************************************************
* Function Name: Debug_Stop
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
void Debug_Stop(void)
{
#if (Debug_SCB_IRQ_INTERNAL)
    Debug_DisableInt();
#endif /* (Debug_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    Debug_ScbModeStop();

    /* Disable SCB IP */
    Debug_CTRL_REG &= (uint32) ~Debug_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    Debug_SetTxInterruptMode(Debug_NO_INTR_SOURCES);

#if (Debug_SCB_IRQ_INTERNAL)
    Debug_ClearPendingInt();
#endif /* (Debug_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Debug_SetRxFifoLevel
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
void Debug_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = Debug_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~Debug_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (Debug_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Debug_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: Debug_SetTxFifoLevel
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
void Debug_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = Debug_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~Debug_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (Debug_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    Debug_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (Debug_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: Debug_SetCustomInterruptHandler
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
    void Debug_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER)
        Debug_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_Debug_CUSTOM_INTR_HANDLER) */
    }
#endif /* (Debug_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: Debug_ScbModeEnableIntr
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
static void Debug_ScbEnableIntr(void)
{
#if (Debug_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != Debug_scbEnableIntr)
        {
            Debug_EnableInt();
        }

    #else
        Debug_EnableInt();

    #endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (Debug_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: Debug_ScbModePostEnable
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
static void Debug_ScbModePostEnable(void)
{
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!Debug_CY_SCBIP_V1)
    if (Debug_SCB_MODE_SPI_RUNTM_CFG)
    {
        Debug_SpiPostEnable();
    }
    else if (Debug_SCB_MODE_UART_RUNTM_CFG)
    {
        Debug_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!Debug_CY_SCBIP_V1) */

#elif (Debug_SCB_MODE_SPI_CONST_CFG)
    Debug_SpiPostEnable();

#elif (Debug_SCB_MODE_UART_CONST_CFG)
    Debug_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: Debug_ScbModeStop
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
static void Debug_ScbModeStop(void)
{
#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    if (Debug_SCB_MODE_I2C_RUNTM_CFG)
    {
        Debug_I2CStop();
    }
    else if (Debug_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Debug_EzI2CStop();
    }
#if (!Debug_CY_SCBIP_V1)
    else if (Debug_SCB_MODE_SPI_RUNTM_CFG)
    {
        Debug_SpiStop();
    }
    else if (Debug_SCB_MODE_UART_RUNTM_CFG)
    {
        Debug_UartStop();
    }
#endif /* (!Debug_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (Debug_SCB_MODE_I2C_CONST_CFG)
    Debug_I2CStop();

#elif (Debug_SCB_MODE_EZI2C_CONST_CFG)
    Debug_EzI2CStop();

#elif (Debug_SCB_MODE_SPI_CONST_CFG)
    Debug_SpiStop();

#elif (Debug_SCB_MODE_UART_CONST_CFG)
    Debug_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (Debug_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: Debug_SetPins
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
    void Debug_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [Debug_SCB_PINS_NUMBER];
        uint32 pinsDm   [Debug_SCB_PINS_NUMBER];

    #if (!Debug_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!Debug_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < Debug_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = Debug_HSIOM_DEF_SEL;
            pinsDm[i]    = Debug_PIN_DM_ALG_HIZ;
        }

        if ((Debug_SCB_MODE_I2C   == mode) ||
           (Debug_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_HSIOM_I2C_SEL;
            hsiomSel[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_HSIOM_I2C_SEL;

            pinsDm[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_PIN_DM_OD_LO;
            pinsDm[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_PIN_DM_OD_LO;
        }
    #if (!Debug_CY_SCBIP_V1)
        else if (Debug_SCB_MODE_SPI == mode)
        {
            hsiomSel[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
            hsiomSel[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
            hsiomSel[Debug_SCLK_PIN_INDEX] = Debug_HSIOM_SPI_SEL;

            if (Debug_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;
                pinsDm[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsDm[Debug_SCLK_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;

            #if (Debug_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[Debug_SS0_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
                pinsDm  [Debug_SS0_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;
            #endif /* (Debug_SS0_PIN) */

            #if (Debug_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= Debug_TX_SDA_MISO_PIN_MASK;
            #endif /* (Debug_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsDm[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;
                pinsDm[Debug_SCLK_PIN_INDEX] = Debug_PIN_DM_STRONG;

            #if (Debug_SS0_PIN)
                hsiomSel [Debug_SS0_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
                pinsDm   [Debug_SS0_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsInBuf |= Debug_SS0_PIN_MASK;
            #endif /* (Debug_SS0_PIN) */

            #if (Debug_SS1_PIN)
                hsiomSel [Debug_SS1_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
                pinsDm   [Debug_SS1_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsInBuf |= Debug_SS1_PIN_MASK;
            #endif /* (Debug_SS1_PIN) */

            #if (Debug_SS2_PIN)
                hsiomSel [Debug_SS2_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
                pinsDm   [Debug_SS2_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsInBuf |= Debug_SS2_PIN_MASK;
            #endif /* (Debug_SS2_PIN) */

            #if (Debug_SS3_PIN)
                hsiomSel [Debug_SS3_PIN_INDEX] = Debug_HSIOM_SPI_SEL;
                pinsDm   [Debug_SS3_PIN_INDEX] = Debug_PIN_DM_STRONG;
                pinsInBuf |= Debug_SS3_PIN_MASK;
            #endif /* (Debug_SS3_PIN) */

                /* Disable input buffers */
            #if (Debug_RX_SCL_MOSI_PIN)
                pinsInBuf |= Debug_RX_SCL_MOSI_PIN_MASK;
            #endif /* (Debug_RX_SCL_MOSI_PIN) */

             #if (Debug_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= Debug_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (Debug_RX_WAKE_SCL_MOSI_PIN) */

            #if (Debug_SCLK_PIN)
                pinsInBuf |= Debug_SCLK_PIN_MASK;
            #endif /* (Debug_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (Debug_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_HSIOM_UART_SEL;
                pinsDm  [Debug_TX_SDA_MISO_PIN_INDEX] = Debug_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (Debug_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_HSIOM_UART_SEL;
                    pinsDm  [Debug_RX_SCL_MOSI_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;
                }

                if (0u != (Debug_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[Debug_TX_SDA_MISO_PIN_INDEX] = Debug_HSIOM_UART_SEL;
                    pinsDm  [Debug_TX_SDA_MISO_PIN_INDEX] = Debug_PIN_DM_STRONG;

                #if (Debug_TX_SDA_MISO_PIN)
                     pinsInBuf |= Debug_TX_SDA_MISO_PIN_MASK;
                #endif /* (Debug_TX_SDA_MISO_PIN) */
                }

            #if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
                if (Debug_UART_MODE_STD == subMode)
                {
                    if (0u != (Debug_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[Debug_SCLK_PIN_INDEX] = Debug_HSIOM_UART_SEL;
                        pinsDm  [Debug_SCLK_PIN_INDEX] = Debug_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (Debug_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[Debug_SS0_PIN_INDEX] = Debug_HSIOM_UART_SEL;
                        pinsDm  [Debug_SS0_PIN_INDEX] = Debug_PIN_DM_STRONG;

                    #if (Debug_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= Debug_SS0_PIN_MASK;
                    #endif /* (Debug_SS0_PIN) */
                    }
                }
            #endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
            }
        }
    #endif /* (!Debug_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (Debug_RX_WAKE_SCL_MOSI_PIN)
        Debug_SET_HSIOM_SEL(Debug_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       Debug_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       Debug_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[Debug_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        Debug_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[Debug_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     Debug_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & Debug_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        Debug_SET_INCFG_TYPE(Debug_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        Debug_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        Debug_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        Debug_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (Debug_RX_WAKE_SCL_MOSI_PIN) */

    #if (Debug_RX_SCL_MOSI_PIN)
        Debug_SET_HSIOM_SEL(Debug_RX_SCL_MOSI_HSIOM_REG,
                                       Debug_RX_SCL_MOSI_HSIOM_MASK,
                                       Debug_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[Debug_RX_SCL_MOSI_PIN_INDEX]);

        Debug_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[Debug_RX_SCL_MOSI_PIN_INDEX]);

    #if (!Debug_CY_SCBIP_V1)
        Debug_SET_INP_DIS(Debug_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     Debug_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & Debug_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!Debug_CY_SCBIP_V1) */
    #endif /* (Debug_RX_SCL_MOSI_PIN) */

    #if (Debug_TX_SDA_MISO_PIN)
        Debug_SET_HSIOM_SEL(Debug_TX_SDA_MISO_HSIOM_REG,
                                       Debug_TX_SDA_MISO_HSIOM_MASK,
                                       Debug_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[Debug_TX_SDA_MISO_PIN_INDEX]);

        Debug_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[Debug_TX_SDA_MISO_PIN_INDEX]);

    #if (!Debug_CY_SCBIP_V1)
        Debug_SET_INP_DIS(Debug_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     Debug_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & Debug_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!Debug_CY_SCBIP_V1) */
    #endif /* (Debug_RX_SCL_MOSI_PIN) */

    #if (Debug_SCLK_PIN)
        Debug_SET_HSIOM_SEL(Debug_SCLK_HSIOM_REG,
                                       Debug_SCLK_HSIOM_MASK,
                                       Debug_SCLK_HSIOM_POS,
                                       hsiomSel[Debug_SCLK_PIN_INDEX]);

        Debug_spi_sclk_SetDriveMode((uint8) pinsDm[Debug_SCLK_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_spi_sclk_INP_DIS,
                                     Debug_spi_sclk_MASK,
                                     (0u != (pinsInBuf & Debug_SCLK_PIN_MASK)));
    #endif /* (Debug_SCLK_PIN) */

    #if (Debug_SS0_PIN)
        Debug_SET_HSIOM_SEL(Debug_SS0_HSIOM_REG,
                                       Debug_SS0_HSIOM_MASK,
                                       Debug_SS0_HSIOM_POS,
                                       hsiomSel[Debug_SS0_PIN_INDEX]);

        Debug_spi_ss0_SetDriveMode((uint8) pinsDm[Debug_SS0_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_spi_ss0_INP_DIS,
                                     Debug_spi_ss0_MASK,
                                     (0u != (pinsInBuf & Debug_SS0_PIN_MASK)));
    #endif /* (Debug_SS0_PIN) */

    #if (Debug_SS1_PIN)
        Debug_SET_HSIOM_SEL(Debug_SS1_HSIOM_REG,
                                       Debug_SS1_HSIOM_MASK,
                                       Debug_SS1_HSIOM_POS,
                                       hsiomSel[Debug_SS1_PIN_INDEX]);

        Debug_spi_ss1_SetDriveMode((uint8) pinsDm[Debug_SS1_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_spi_ss1_INP_DIS,
                                     Debug_spi_ss1_MASK,
                                     (0u != (pinsInBuf & Debug_SS1_PIN_MASK)));
    #endif /* (Debug_SS1_PIN) */

    #if (Debug_SS2_PIN)
        Debug_SET_HSIOM_SEL(Debug_SS2_HSIOM_REG,
                                       Debug_SS2_HSIOM_MASK,
                                       Debug_SS2_HSIOM_POS,
                                       hsiomSel[Debug_SS2_PIN_INDEX]);

        Debug_spi_ss2_SetDriveMode((uint8) pinsDm[Debug_SS2_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_spi_ss2_INP_DIS,
                                     Debug_spi_ss2_MASK,
                                     (0u != (pinsInBuf & Debug_SS2_PIN_MASK)));
    #endif /* (Debug_SS2_PIN) */

    #if (Debug_SS3_PIN)
        Debug_SET_HSIOM_SEL(Debug_SS3_HSIOM_REG,
                                       Debug_SS3_HSIOM_MASK,
                                       Debug_SS3_HSIOM_POS,
                                       hsiomSel[Debug_SS3_PIN_INDEX]);

        Debug_spi_ss3_SetDriveMode((uint8) pinsDm[Debug_SS3_PIN_INDEX]);

        Debug_SET_INP_DIS(Debug_spi_ss3_INP_DIS,
                                     Debug_spi_ss3_MASK,
                                     (0u != (pinsInBuf & Debug_SS3_PIN_MASK)));
    #endif /* (Debug_SS3_PIN) */
    }

#endif /* (Debug_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: Debug_I2CSlaveNackGeneration
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
    void Debug_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (Debug_CTRL_REG & Debug_CTRL_EC_AM_MODE)) &&
            (0u == (Debug_I2C_CTRL_REG & Debug_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            Debug_CTRL_REG &= ~Debug_CTRL_EC_AM_MODE;
            Debug_CTRL_REG |=  Debug_CTRL_EC_AM_MODE;
        }

        Debug_I2C_SLAVE_CMD_REG = Debug_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */


/* [] END OF FILE */
