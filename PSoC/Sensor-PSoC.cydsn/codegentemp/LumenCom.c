/*******************************************************************************
* File Name: LumenCom.c
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

#include "LumenCom_PVT.h"

#if (LumenCom_SCB_MODE_I2C_INC)
    #include "LumenCom_I2C_PVT.h"
#endif /* (LumenCom_SCB_MODE_I2C_INC) */

#if (LumenCom_SCB_MODE_EZI2C_INC)
    #include "LumenCom_EZI2C_PVT.h"
#endif /* (LumenCom_SCB_MODE_EZI2C_INC) */

#if (LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC)
    #include "LumenCom_SPI_UART_PVT.h"
#endif /* (LumenCom_SCB_MODE_SPI_INC || LumenCom_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 LumenCom_scbMode = LumenCom_SCB_MODE_UNCONFIG;
    uint8 LumenCom_scbEnableWake;
    uint8 LumenCom_scbEnableIntr;

    /* I2C configuration variables */
    uint8 LumenCom_mode;
    uint8 LumenCom_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * LumenCom_rxBuffer;
    uint8  LumenCom_rxDataBits;
    uint32 LumenCom_rxBufferSize;

    volatile uint8 * LumenCom_txBuffer;
    uint8  LumenCom_txDataBits;
    uint32 LumenCom_txBufferSize;

    /* EZI2C configuration variables */
    uint8 LumenCom_numberOfAddr;
    uint8 LumenCom_subAddrSize;
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/

uint8 LumenCom_initVar = 0u;

#if (LumenCom_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER)
    void (*LumenCom_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER) */
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void LumenCom_ScbEnableIntr(void);
static void LumenCom_ScbModeStop(void);
static void LumenCom_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: LumenCom_Init
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
void LumenCom_Init(void)
{
#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    if (LumenCom_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        LumenCom_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (LumenCom_SCB_MODE_I2C_CONST_CFG)
    LumenCom_I2CInit();

#elif (LumenCom_SCB_MODE_SPI_CONST_CFG)
    LumenCom_SpiInit();

#elif (LumenCom_SCB_MODE_UART_CONST_CFG)
    LumenCom_UartInit();

#elif (LumenCom_SCB_MODE_EZI2C_CONST_CFG)
    LumenCom_EzI2CInit();

#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LumenCom_Enable
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
void LumenCom_Enable(void)
{
#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!LumenCom_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        LumenCom_CTRL_REG |= LumenCom_CTRL_ENABLED;

        LumenCom_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        LumenCom_ScbModePostEnable();
    }
#else
    LumenCom_CTRL_REG |= LumenCom_CTRL_ENABLED;

    LumenCom_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    LumenCom_ScbModePostEnable();
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LumenCom_Start
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
*  LumenCom_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void LumenCom_Start(void)
{
    if (0u == LumenCom_initVar)
    {
        LumenCom_Init();
        LumenCom_initVar = 1u; /* Component was initialized */
    }

    LumenCom_Enable();
}


/*******************************************************************************
* Function Name: LumenCom_Stop
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
void LumenCom_Stop(void)
{
#if (LumenCom_SCB_IRQ_INTERNAL)
    LumenCom_DisableInt();
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    LumenCom_ScbModeStop();

    /* Disable SCB IP */
    LumenCom_CTRL_REG &= (uint32) ~LumenCom_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger because after the component is enabled, the TX FIFO
    * is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when they are disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    LumenCom_SetTxInterruptMode(LumenCom_NO_INTR_SOURCES);

#if (LumenCom_SCB_IRQ_INTERNAL)
    LumenCom_ClearPendingInt();
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: LumenCom_SetRxFifoLevel
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
void LumenCom_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = LumenCom_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~LumenCom_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (LumenCom_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    LumenCom_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: LumenCom_SetTxFifoLevel
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
void LumenCom_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = LumenCom_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~LumenCom_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (LumenCom_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    LumenCom_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (LumenCom_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: LumenCom_SetCustomInterruptHandler
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
    void LumenCom_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER)
        LumenCom_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_LumenCom_CUSTOM_INTR_HANDLER) */
    }
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: LumenCom_ScbModeEnableIntr
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
static void LumenCom_ScbEnableIntr(void)
{
#if (LumenCom_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != LumenCom_scbEnableIntr)
        {
            LumenCom_EnableInt();
        }

    #else
        LumenCom_EnableInt();

    #endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: LumenCom_ScbModePostEnable
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
static void LumenCom_ScbModePostEnable(void)
{
#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!LumenCom_CY_SCBIP_V1)
    if (LumenCom_SCB_MODE_SPI_RUNTM_CFG)
    {
        LumenCom_SpiPostEnable();
    }
    else if (LumenCom_SCB_MODE_UART_RUNTM_CFG)
    {
        LumenCom_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!LumenCom_CY_SCBIP_V1) */

#elif (LumenCom_SCB_MODE_SPI_CONST_CFG)
    LumenCom_SpiPostEnable();

#elif (LumenCom_SCB_MODE_UART_CONST_CFG)
    LumenCom_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: LumenCom_ScbModeStop
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
static void LumenCom_ScbModeStop(void)
{
#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    if (LumenCom_SCB_MODE_I2C_RUNTM_CFG)
    {
        LumenCom_I2CStop();
    }
    else if (LumenCom_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        LumenCom_EzI2CStop();
    }
#if (!LumenCom_CY_SCBIP_V1)
    else if (LumenCom_SCB_MODE_SPI_RUNTM_CFG)
    {
        LumenCom_SpiStop();
    }
    else if (LumenCom_SCB_MODE_UART_RUNTM_CFG)
    {
        LumenCom_UartStop();
    }
#endif /* (!LumenCom_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (LumenCom_SCB_MODE_I2C_CONST_CFG)
    LumenCom_I2CStop();

#elif (LumenCom_SCB_MODE_EZI2C_CONST_CFG)
    LumenCom_EzI2CStop();

#elif (LumenCom_SCB_MODE_SPI_CONST_CFG)
    LumenCom_SpiStop();

#elif (LumenCom_SCB_MODE_UART_CONST_CFG)
    LumenCom_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: LumenCom_SetPins
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
    void LumenCom_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 hsiomSel [LumenCom_SCB_PINS_NUMBER];
        uint32 pinsDm   [LumenCom_SCB_PINS_NUMBER];

    #if (!LumenCom_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!LumenCom_CY_SCBIP_V1) */

        uint32 i;

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < LumenCom_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i]  = LumenCom_HSIOM_DEF_SEL;
            pinsDm[i]    = LumenCom_PIN_DM_ALG_HIZ;
        }

        if ((LumenCom_SCB_MODE_I2C   == mode) ||
           (LumenCom_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_HSIOM_I2C_SEL;
            hsiomSel[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_HSIOM_I2C_SEL;

            pinsDm[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_PIN_DM_OD_LO;
            pinsDm[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_PIN_DM_OD_LO;
        }
    #if (!LumenCom_CY_SCBIP_V1)
        else if (LumenCom_SCB_MODE_SPI == mode)
        {
            hsiomSel[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
            hsiomSel[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
            hsiomSel[LumenCom_SCLK_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;

            if (LumenCom_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;
                pinsDm[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsDm[LumenCom_SCLK_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;

            #if (LumenCom_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[LumenCom_SS0_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
                pinsDm  [LumenCom_SS0_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;
            #endif /* (LumenCom_SS0_PIN) */

            #if (LumenCom_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= LumenCom_TX_SDA_MISO_PIN_MASK;
            #endif /* (LumenCom_TX_SDA_MISO_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsDm[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;
                pinsDm[LumenCom_SCLK_PIN_INDEX] = LumenCom_PIN_DM_STRONG;

            #if (LumenCom_SS0_PIN)
                hsiomSel [LumenCom_SS0_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
                pinsDm   [LumenCom_SS0_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsInBuf |= LumenCom_SS0_PIN_MASK;
            #endif /* (LumenCom_SS0_PIN) */

            #if (LumenCom_SS1_PIN)
                hsiomSel [LumenCom_SS1_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
                pinsDm   [LumenCom_SS1_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsInBuf |= LumenCom_SS1_PIN_MASK;
            #endif /* (LumenCom_SS1_PIN) */

            #if (LumenCom_SS2_PIN)
                hsiomSel [LumenCom_SS2_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
                pinsDm   [LumenCom_SS2_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsInBuf |= LumenCom_SS2_PIN_MASK;
            #endif /* (LumenCom_SS2_PIN) */

            #if (LumenCom_SS3_PIN)
                hsiomSel [LumenCom_SS3_PIN_INDEX] = LumenCom_HSIOM_SPI_SEL;
                pinsDm   [LumenCom_SS3_PIN_INDEX] = LumenCom_PIN_DM_STRONG;
                pinsInBuf |= LumenCom_SS3_PIN_MASK;
            #endif /* (LumenCom_SS3_PIN) */

                /* Disable input buffers */
            #if (LumenCom_RX_SCL_MOSI_PIN)
                pinsInBuf |= LumenCom_RX_SCL_MOSI_PIN_MASK;
            #endif /* (LumenCom_RX_SCL_MOSI_PIN) */

             #if (LumenCom_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= LumenCom_RX_WAKE_SCL_MOSI_PIN_MASK;
            #endif /* (LumenCom_RX_WAKE_SCL_MOSI_PIN) */

            #if (LumenCom_SCLK_PIN)
                pinsInBuf |= LumenCom_SCLK_PIN_MASK;
            #endif /* (LumenCom_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (LumenCom_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_HSIOM_UART_SEL;
                pinsDm  [LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if (0u != (LumenCom_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_HSIOM_UART_SEL;
                    pinsDm  [LumenCom_RX_SCL_MOSI_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;
                }

                if (0u != (LumenCom_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                    hsiomSel[LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_HSIOM_UART_SEL;
                    pinsDm  [LumenCom_TX_SDA_MISO_PIN_INDEX] = LumenCom_PIN_DM_STRONG;

                #if (LumenCom_TX_SDA_MISO_PIN)
                     pinsInBuf |= LumenCom_TX_SDA_MISO_PIN_MASK;
                #endif /* (LumenCom_TX_SDA_MISO_PIN) */
                }

            #if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
                if (LumenCom_UART_MODE_STD == subMode)
                {
                    if (0u != (LumenCom_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                        hsiomSel[LumenCom_SCLK_PIN_INDEX] = LumenCom_HSIOM_UART_SEL;
                        pinsDm  [LumenCom_SCLK_PIN_INDEX] = LumenCom_PIN_DM_DIG_HIZ;
                    }

                    if (0u != (LumenCom_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                        hsiomSel[LumenCom_SS0_PIN_INDEX] = LumenCom_HSIOM_UART_SEL;
                        pinsDm  [LumenCom_SS0_PIN_INDEX] = LumenCom_PIN_DM_STRONG;

                    #if (LumenCom_SS0_PIN)
                        /* Disable input buffer */
                        pinsInBuf |= LumenCom_SS0_PIN_MASK;
                    #endif /* (LumenCom_SS0_PIN) */
                    }
                }
            #endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */
            }
        }
    #endif /* (!LumenCom_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (LumenCom_RX_WAKE_SCL_MOSI_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       LumenCom_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       LumenCom_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[LumenCom_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        LumenCom_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[LumenCom_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     LumenCom_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & LumenCom_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        LumenCom_SET_INCFG_TYPE(LumenCom_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        LumenCom_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        LumenCom_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        LumenCom_INTCFG_TYPE_FALLING_EDGE);
    #endif /* (LumenCom_RX_WAKE_SCL_MOSI_PIN) */

    #if (LumenCom_RX_SCL_MOSI_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_RX_SCL_MOSI_HSIOM_REG,
                                       LumenCom_RX_SCL_MOSI_HSIOM_MASK,
                                       LumenCom_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[LumenCom_RX_SCL_MOSI_PIN_INDEX]);

        LumenCom_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[LumenCom_RX_SCL_MOSI_PIN_INDEX]);

    #if (!LumenCom_CY_SCBIP_V1)
        LumenCom_SET_INP_DIS(LumenCom_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                     LumenCom_uart_rx_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & LumenCom_RX_SCL_MOSI_PIN_MASK)));
    #endif /* (!LumenCom_CY_SCBIP_V1) */
    #endif /* (LumenCom_RX_SCL_MOSI_PIN) */

    #if (LumenCom_TX_SDA_MISO_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_TX_SDA_MISO_HSIOM_REG,
                                       LumenCom_TX_SDA_MISO_HSIOM_MASK,
                                       LumenCom_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[LumenCom_TX_SDA_MISO_PIN_INDEX]);

        LumenCom_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[LumenCom_TX_SDA_MISO_PIN_INDEX]);

    #if (!LumenCom_CY_SCBIP_V1)
        LumenCom_SET_INP_DIS(LumenCom_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     LumenCom_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & LumenCom_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!LumenCom_CY_SCBIP_V1) */
    #endif /* (LumenCom_RX_SCL_MOSI_PIN) */

    #if (LumenCom_SCLK_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_SCLK_HSIOM_REG,
                                       LumenCom_SCLK_HSIOM_MASK,
                                       LumenCom_SCLK_HSIOM_POS,
                                       hsiomSel[LumenCom_SCLK_PIN_INDEX]);

        LumenCom_spi_sclk_SetDriveMode((uint8) pinsDm[LumenCom_SCLK_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_spi_sclk_INP_DIS,
                                     LumenCom_spi_sclk_MASK,
                                     (0u != (pinsInBuf & LumenCom_SCLK_PIN_MASK)));
    #endif /* (LumenCom_SCLK_PIN) */

    #if (LumenCom_SS0_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_SS0_HSIOM_REG,
                                       LumenCom_SS0_HSIOM_MASK,
                                       LumenCom_SS0_HSIOM_POS,
                                       hsiomSel[LumenCom_SS0_PIN_INDEX]);

        LumenCom_spi_ss0_SetDriveMode((uint8) pinsDm[LumenCom_SS0_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_spi_ss0_INP_DIS,
                                     LumenCom_spi_ss0_MASK,
                                     (0u != (pinsInBuf & LumenCom_SS0_PIN_MASK)));
    #endif /* (LumenCom_SS0_PIN) */

    #if (LumenCom_SS1_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_SS1_HSIOM_REG,
                                       LumenCom_SS1_HSIOM_MASK,
                                       LumenCom_SS1_HSIOM_POS,
                                       hsiomSel[LumenCom_SS1_PIN_INDEX]);

        LumenCom_spi_ss1_SetDriveMode((uint8) pinsDm[LumenCom_SS1_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_spi_ss1_INP_DIS,
                                     LumenCom_spi_ss1_MASK,
                                     (0u != (pinsInBuf & LumenCom_SS1_PIN_MASK)));
    #endif /* (LumenCom_SS1_PIN) */

    #if (LumenCom_SS2_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_SS2_HSIOM_REG,
                                       LumenCom_SS2_HSIOM_MASK,
                                       LumenCom_SS2_HSIOM_POS,
                                       hsiomSel[LumenCom_SS2_PIN_INDEX]);

        LumenCom_spi_ss2_SetDriveMode((uint8) pinsDm[LumenCom_SS2_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_spi_ss2_INP_DIS,
                                     LumenCom_spi_ss2_MASK,
                                     (0u != (pinsInBuf & LumenCom_SS2_PIN_MASK)));
    #endif /* (LumenCom_SS2_PIN) */

    #if (LumenCom_SS3_PIN)
        LumenCom_SET_HSIOM_SEL(LumenCom_SS3_HSIOM_REG,
                                       LumenCom_SS3_HSIOM_MASK,
                                       LumenCom_SS3_HSIOM_POS,
                                       hsiomSel[LumenCom_SS3_PIN_INDEX]);

        LumenCom_spi_ss3_SetDriveMode((uint8) pinsDm[LumenCom_SS3_PIN_INDEX]);

        LumenCom_SET_INP_DIS(LumenCom_spi_ss3_INP_DIS,
                                     LumenCom_spi_ss3_MASK,
                                     (0u != (pinsInBuf & LumenCom_SS3_PIN_MASK)));
    #endif /* (LumenCom_SS3_PIN) */
    }

#endif /* (LumenCom_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: LumenCom_I2CSlaveNackGeneration
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
    void LumenCom_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (LumenCom_CTRL_REG & LumenCom_CTRL_EC_AM_MODE)) &&
            (0u == (LumenCom_I2C_CTRL_REG & LumenCom_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            LumenCom_CTRL_REG &= ~LumenCom_CTRL_EC_AM_MODE;
            LumenCom_CTRL_REG |=  LumenCom_CTRL_EC_AM_MODE;
        }

        LumenCom_I2C_SLAVE_CMD_REG = LumenCom_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */


/* [] END OF FILE */
