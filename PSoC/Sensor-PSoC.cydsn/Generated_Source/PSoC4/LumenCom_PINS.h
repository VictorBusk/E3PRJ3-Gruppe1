/*******************************************************************************
* File Name: LumenCom_PINS.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_LumenCom_H)
#define CY_SCB_PINS_LumenCom_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define LumenCom_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define LumenCom_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define LumenCom_REMOVE_TX_SDA_MISO_PIN      (1u)
#define LumenCom_REMOVE_SCLK_PIN      (1u)
#define LumenCom_REMOVE_SS0_PIN      (1u)
#define LumenCom_REMOVE_SS1_PIN                 (1u)
#define LumenCom_REMOVE_SS2_PIN                 (1u)
#define LumenCom_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define LumenCom_REMOVE_I2C_PINS                (0u)
#define LumenCom_REMOVE_SPI_MASTER_PINS         (1u)
#define LumenCom_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define LumenCom_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define LumenCom_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define LumenCom_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define LumenCom_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define LumenCom_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define LumenCom_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define LumenCom_REMOVE_SPI_SLAVE_PINS          (1u)
#define LumenCom_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define LumenCom_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define LumenCom_REMOVE_UART_TX_PIN             (1u)
#define LumenCom_REMOVE_UART_RX_TX_PIN          (1u)
#define LumenCom_REMOVE_UART_RX_PIN             (1u)
#define LumenCom_REMOVE_UART_RX_WAKE_PIN        (1u)
#define LumenCom_REMOVE_UART_RTS_PIN            (1u)
#define LumenCom_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define LumenCom_RX_WAKE_SCL_MOSI_PIN (0u == LumenCom_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define LumenCom_RX_SCL_MOSI_PIN     (0u == LumenCom_REMOVE_RX_SCL_MOSI_PIN)
#define LumenCom_TX_SDA_MISO_PIN     (0u == LumenCom_REMOVE_TX_SDA_MISO_PIN)
#define LumenCom_SCLK_PIN     (0u == LumenCom_REMOVE_SCLK_PIN)
#define LumenCom_SS0_PIN     (0u == LumenCom_REMOVE_SS0_PIN)
#define LumenCom_SS1_PIN                (0u == LumenCom_REMOVE_SS1_PIN)
#define LumenCom_SS2_PIN                (0u == LumenCom_REMOVE_SS2_PIN)
#define LumenCom_SS3_PIN                (0u == LumenCom_REMOVE_SS3_PIN)

/* Mode defined pins */
#define LumenCom_I2C_PINS               (0u == LumenCom_REMOVE_I2C_PINS)
#define LumenCom_SPI_MASTER_PINS        (0u == LumenCom_REMOVE_SPI_MASTER_PINS)
#define LumenCom_SPI_MASTER_SCLK_PIN    (0u == LumenCom_REMOVE_SPI_MASTER_SCLK_PIN)
#define LumenCom_SPI_MASTER_MOSI_PIN    (0u == LumenCom_REMOVE_SPI_MASTER_MOSI_PIN)
#define LumenCom_SPI_MASTER_MISO_PIN    (0u == LumenCom_REMOVE_SPI_MASTER_MISO_PIN)
#define LumenCom_SPI_MASTER_SS0_PIN     (0u == LumenCom_REMOVE_SPI_MASTER_SS0_PIN)
#define LumenCom_SPI_MASTER_SS1_PIN     (0u == LumenCom_REMOVE_SPI_MASTER_SS1_PIN)
#define LumenCom_SPI_MASTER_SS2_PIN     (0u == LumenCom_REMOVE_SPI_MASTER_SS2_PIN)
#define LumenCom_SPI_MASTER_SS3_PIN     (0u == LumenCom_REMOVE_SPI_MASTER_SS3_PIN)
#define LumenCom_SPI_SLAVE_PINS         (0u == LumenCom_REMOVE_SPI_SLAVE_PINS)
#define LumenCom_SPI_SLAVE_MOSI_PIN     (0u == LumenCom_REMOVE_SPI_SLAVE_MOSI_PIN)
#define LumenCom_SPI_SLAVE_MISO_PIN     (0u == LumenCom_REMOVE_SPI_SLAVE_MISO_PIN)
#define LumenCom_UART_TX_PIN            (0u == LumenCom_REMOVE_UART_TX_PIN)
#define LumenCom_UART_RX_TX_PIN         (0u == LumenCom_REMOVE_UART_RX_TX_PIN)
#define LumenCom_UART_RX_PIN            (0u == LumenCom_REMOVE_UART_RX_PIN)
#define LumenCom_UART_RX_WAKE_PIN       (0u == LumenCom_REMOVE_UART_RX_WAKE_PIN)
#define LumenCom_UART_RTS_PIN           (0u == LumenCom_REMOVE_UART_RTS_PIN)
#define LumenCom_UART_CTS_PIN           (0u == LumenCom_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (LumenCom_RX_WAKE_SCL_MOSI_PIN)
    #include "LumenCom_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (LumenCom_RX_SCL_MOSI) */

#if (LumenCom_RX_SCL_MOSI_PIN)
    #include "LumenCom_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (LumenCom_RX_SCL_MOSI) */

#if (LumenCom_TX_SDA_MISO_PIN)
    #include "LumenCom_uart_tx_i2c_sda_spi_miso.h"
#endif /* (LumenCom_TX_SDA_MISO) */

#if (LumenCom_SCLK_PIN)
    #include "LumenCom_spi_sclk.h"
#endif /* (LumenCom_SCLK) */

#if (LumenCom_SS0_PIN)
    #include "LumenCom_spi_ss0.h"
#endif /* (LumenCom_SS0_PIN) */

#if (LumenCom_SS1_PIN)
    #include "LumenCom_spi_ss1.h"
#endif /* (LumenCom_SS1_PIN) */

#if (LumenCom_SS2_PIN)
    #include "LumenCom_spi_ss2.h"
#endif /* (LumenCom_SS2_PIN) */

#if (LumenCom_SS3_PIN)
    #include "LumenCom_spi_ss3.h"
#endif /* (LumenCom_SS3_PIN) */

#if (LumenCom_I2C_PINS)
    #include "LumenCom_scl.h"
    #include "LumenCom_sda.h"
#endif /* (LumenCom_I2C_PINS) */

#if (LumenCom_SPI_MASTER_PINS)
#if (LumenCom_SPI_MASTER_SCLK_PIN)
    #include "LumenCom_sclk_m.h"
#endif /* (LumenCom_SPI_MASTER_SCLK_PIN) */

#if (LumenCom_SPI_MASTER_MOSI_PIN)
    #include "LumenCom_mosi_m.h"
#endif /* (LumenCom_SPI_MASTER_MOSI_PIN) */

#if (LumenCom_SPI_MASTER_MISO_PIN)
    #include "LumenCom_miso_m.h"
#endif /*(LumenCom_SPI_MASTER_MISO_PIN) */
#endif /* (LumenCom_SPI_MASTER_PINS) */

#if (LumenCom_SPI_SLAVE_PINS)
    #include "LumenCom_sclk_s.h"
    #include "LumenCom_ss_s.h"

#if (LumenCom_SPI_SLAVE_MOSI_PIN)
    #include "LumenCom_mosi_s.h"
#endif /* (LumenCom_SPI_SLAVE_MOSI_PIN) */

#if (LumenCom_SPI_SLAVE_MISO_PIN)
    #include "LumenCom_miso_s.h"
#endif /*(LumenCom_SPI_SLAVE_MISO_PIN) */
#endif /* (LumenCom_SPI_SLAVE_PINS) */

#if (LumenCom_SPI_MASTER_SS0_PIN)
    #include "LumenCom_ss0_m.h"
#endif /* (LumenCom_SPI_MASTER_SS0_PIN) */

#if (LumenCom_SPI_MASTER_SS1_PIN)
    #include "LumenCom_ss1_m.h"
#endif /* (LumenCom_SPI_MASTER_SS1_PIN) */

#if (LumenCom_SPI_MASTER_SS2_PIN)
    #include "LumenCom_ss2_m.h"
#endif /* (LumenCom_SPI_MASTER_SS2_PIN) */

#if (LumenCom_SPI_MASTER_SS3_PIN)
    #include "LumenCom_ss3_m.h"
#endif /* (LumenCom_SPI_MASTER_SS3_PIN) */

#if (LumenCom_UART_TX_PIN)
    #include "LumenCom_tx.h"
#endif /* (LumenCom_UART_TX_PIN) */

#if (LumenCom_UART_RX_TX_PIN)
    #include "LumenCom_rx_tx.h"
#endif /* (LumenCom_UART_RX_TX_PIN) */

#if (LumenCom_UART_RX_PIN)
    #include "LumenCom_rx.h"
#endif /* (LumenCom_UART_RX_PIN) */

#if (LumenCom_UART_RX_WAKE_PIN)
    #include "LumenCom_rx_wake.h"
#endif /* (LumenCom_UART_RX_WAKE_PIN) */

#if (LumenCom_UART_RTS_PIN)
    #include "LumenCom_rts.h"
#endif /* (LumenCom_UART_RTS_PIN) */

#if (LumenCom_UART_CTS_PIN)
    #include "LumenCom_cts.h"
#endif /* (LumenCom_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (LumenCom_RX_WAKE_SCL_MOSI_PIN)
    #define LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define LumenCom_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define LumenCom_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define LumenCom_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define LumenCom_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define LumenCom_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) LumenCom_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define LumenCom_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (LumenCom_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define LumenCom_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) LumenCom_INTCFG_TYPE_MASK << \
                                      LumenCom_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (LumenCom_RX_WAKE_SCL_MOSI_PIN) */

#if (LumenCom_RX_SCL_MOSI_PIN)
    #define LumenCom_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) LumenCom_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define LumenCom_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) LumenCom_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define LumenCom_RX_SCL_MOSI_HSIOM_MASK  (LumenCom_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define LumenCom_RX_SCL_MOSI_HSIOM_POS   (LumenCom_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (LumenCom_RX_SCL_MOSI_PIN) */

#if (LumenCom_TX_SDA_MISO_PIN)
    #define LumenCom_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) LumenCom_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define LumenCom_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) LumenCom_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define LumenCom_TX_SDA_MISO_HSIOM_MASK  (LumenCom_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define LumenCom_TX_SDA_MISO_HSIOM_POS   (LumenCom_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (LumenCom_TX_SDA_MISO_PIN) */

#if (LumenCom_SCLK_PIN)
    #define LumenCom_SCLK_HSIOM_REG   (*(reg32 *) LumenCom_spi_sclk__0__HSIOM)
    #define LumenCom_SCLK_HSIOM_PTR   ( (reg32 *) LumenCom_spi_sclk__0__HSIOM)
    #define LumenCom_SCLK_HSIOM_MASK  (LumenCom_spi_sclk__0__HSIOM_MASK)
    #define LumenCom_SCLK_HSIOM_POS   (LumenCom_spi_sclk__0__HSIOM_SHIFT)
#endif /* (LumenCom_SCLK_PIN) */

#if (LumenCom_SS0_PIN)
    #define LumenCom_SS0_HSIOM_REG   (*(reg32 *) LumenCom_spi_ss0__0__HSIOM)
    #define LumenCom_SS0_HSIOM_PTR   ( (reg32 *) LumenCom_spi_ss0__0__HSIOM)
    #define LumenCom_SS0_HSIOM_MASK  (LumenCom_spi_ss0__0__HSIOM_MASK)
    #define LumenCom_SS0_HSIOM_POS   (LumenCom_spi_ss0__0__HSIOM_SHIFT)
#endif /* (LumenCom_SS0_PIN) */

#if (LumenCom_SS1_PIN)
    #define LumenCom_SS1_HSIOM_REG      (*(reg32 *) LumenCom_spi_ss1__0__HSIOM)
    #define LumenCom_SS1_HSIOM_PTR      ( (reg32 *) LumenCom_spi_ss1__0__HSIOM)
    #define LumenCom_SS1_HSIOM_MASK     (LumenCom_spi_ss1__0__HSIOM_MASK)
    #define LumenCom_SS1_HSIOM_POS      (LumenCom_spi_ss1__0__HSIOM_SHIFT)
#endif /* (LumenCom_SS1_PIN) */

#if (LumenCom_SS2_PIN)
    #define LumenCom_SS2_HSIOM_REG     (*(reg32 *) LumenCom_spi_ss2__0__HSIOM)
    #define LumenCom_SS2_HSIOM_PTR     ( (reg32 *) LumenCom_spi_ss2__0__HSIOM)
    #define LumenCom_SS2_HSIOM_MASK    (LumenCom_spi_ss2__0__HSIOM_MASK)
    #define LumenCom_SS2_HSIOM_POS     (LumenCom_spi_ss2__0__HSIOM_SHIFT)
#endif /* (LumenCom_SS2_PIN) */

#if (LumenCom_SS3_PIN)
    #define LumenCom_SS3_HSIOM_REG     (*(reg32 *) LumenCom_spi_ss3__0__HSIOM)
    #define LumenCom_SS3_HSIOM_PTR     ( (reg32 *) LumenCom_spi_ss3__0__HSIOM)
    #define LumenCom_SS3_HSIOM_MASK    (LumenCom_spi_ss3__0__HSIOM_MASK)
    #define LumenCom_SS3_HSIOM_POS     (LumenCom_spi_ss3__0__HSIOM_SHIFT)
#endif /* (LumenCom_SS3_PIN) */

#if (LumenCom_I2C_PINS)
    #define LumenCom_SCL_HSIOM_REG     (*(reg32 *) LumenCom_scl__0__HSIOM)
    #define LumenCom_SCL_HSIOM_PTR     ( (reg32 *) LumenCom_scl__0__HSIOM)
    #define LumenCom_SCL_HSIOM_MASK    (LumenCom_scl__0__HSIOM_MASK)
    #define LumenCom_SCL_HSIOM_POS     (LumenCom_scl__0__HSIOM_SHIFT)

    #define LumenCom_SDA_HSIOM_REG     (*(reg32 *) LumenCom_sda__0__HSIOM)
    #define LumenCom_SDA_HSIOM_PTR     ( (reg32 *) LumenCom_sda__0__HSIOM)
    #define LumenCom_SDA_HSIOM_MASK    (LumenCom_sda__0__HSIOM_MASK)
    #define LumenCom_SDA_HSIOM_POS     (LumenCom_sda__0__HSIOM_SHIFT)
#endif /* (LumenCom_I2C_PINS) */

#if (LumenCom_SPI_MASTER_SCLK_PIN)
    #define LumenCom_SCLK_M_HSIOM_REG   (*(reg32 *) LumenCom_sclk_m__0__HSIOM)
    #define LumenCom_SCLK_M_HSIOM_PTR   ( (reg32 *) LumenCom_sclk_m__0__HSIOM)
    #define LumenCom_SCLK_M_HSIOM_MASK  (LumenCom_sclk_m__0__HSIOM_MASK)
    #define LumenCom_SCLK_M_HSIOM_POS   (LumenCom_sclk_m__0__HSIOM_SHIFT)
#endif /* (LumenCom_SPI_MASTER_SCLK_PIN) */

#if (LumenCom_SPI_MASTER_SS0_PIN)
    #define LumenCom_SS0_M_HSIOM_REG    (*(reg32 *) LumenCom_ss0_m__0__HSIOM)
    #define LumenCom_SS0_M_HSIOM_PTR    ( (reg32 *) LumenCom_ss0_m__0__HSIOM)
    #define LumenCom_SS0_M_HSIOM_MASK   (LumenCom_ss0_m__0__HSIOM_MASK)
    #define LumenCom_SS0_M_HSIOM_POS    (LumenCom_ss0_m__0__HSIOM_SHIFT)
#endif /* (LumenCom_SPI_MASTER_SS0_PIN) */

#if (LumenCom_SPI_MASTER_SS1_PIN)
    #define LumenCom_SS1_M_HSIOM_REG    (*(reg32 *) LumenCom_ss1_m__0__HSIOM)
    #define LumenCom_SS1_M_HSIOM_PTR    ( (reg32 *) LumenCom_ss1_m__0__HSIOM)
    #define LumenCom_SS1_M_HSIOM_MASK   (LumenCom_ss1_m__0__HSIOM_MASK)
    #define LumenCom_SS1_M_HSIOM_POS    (LumenCom_ss1_m__0__HSIOM_SHIFT)
#endif /* (LumenCom_SPI_MASTER_SS1_PIN) */

#if (LumenCom_SPI_MASTER_SS2_PIN)
    #define LumenCom_SS2_M_HSIOM_REG    (*(reg32 *) LumenCom_ss2_m__0__HSIOM)
    #define LumenCom_SS2_M_HSIOM_PTR    ( (reg32 *) LumenCom_ss2_m__0__HSIOM)
    #define LumenCom_SS2_M_HSIOM_MASK   (LumenCom_ss2_m__0__HSIOM_MASK)
    #define LumenCom_SS2_M_HSIOM_POS    (LumenCom_ss2_m__0__HSIOM_SHIFT)
#endif /* (LumenCom_SPI_MASTER_SS2_PIN) */

#if (LumenCom_SPI_MASTER_SS3_PIN)
    #define LumenCom_SS3_M_HSIOM_REG    (*(reg32 *) LumenCom_ss3_m__0__HSIOM)
    #define LumenCom_SS3_M_HSIOM_PTR    ( (reg32 *) LumenCom_ss3_m__0__HSIOM)
    #define LumenCom_SS3_M_HSIOM_MASK   (LumenCom_ss3_m__0__HSIOM_MASK)
    #define LumenCom_SS3_M_HSIOM_POS    (LumenCom_ss3_m__0__HSIOM_SHIFT)
#endif /* (LumenCom_SPI_MASTER_SS3_PIN) */

#if (LumenCom_UART_TX_PIN)
    #define LumenCom_TX_HSIOM_REG   (*(reg32 *) LumenCom_tx__0__HSIOM)
    #define LumenCom_TX_HSIOM_PTR   ( (reg32 *) LumenCom_tx_0__HSIOM)
    #define LumenCom_TX_HSIOM_MASK  (LumenCom_tx__0__HSIOM_MASK)
    #define LumenCom_TX_HSIOM_POS   (LumenCom_tx__0__HSIOM_SHIFT)
#endif /* (LumenCom_UART_TX_PIN) */

#if (LumenCom_UART_RTS_PIN)
    #define LumenCom_RTS_HSIOM_REG  (*(reg32 *) LumenCom_rts__0__HSIOM)
    #define LumenCom_RTS_HSIOM_PTR  ( (reg32 *) LumenCom_rts__0__HSIOM)
    #define LumenCom_RTS_HSIOM_MASK (LumenCom_rts__0__HSIOM_MASK)
    #define LumenCom_RTS_HSIOM_POS  (LumenCom_rts__0__HSIOM_SHIFT)
#endif /* (LumenCom_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define LumenCom_HSIOM_DEF_SEL      (0x00u)
#define LumenCom_HSIOM_GPIO_SEL     (0x00u)
#define LumenCom_HSIOM_UART_SEL     (0x09u)
#define LumenCom_HSIOM_I2C_SEL      (0x0Eu)
#define LumenCom_HSIOM_SPI_SEL      (0x0Fu)

#define LumenCom_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define LumenCom_RX_SCL_MOSI_PIN_INDEX       (0u)
#define LumenCom_TX_SDA_MISO_PIN_INDEX       (1u)
#define LumenCom_SCLK_PIN_INDEX       (2u)
#define LumenCom_SS0_PIN_INDEX       (3u)
#define LumenCom_SS1_PIN_INDEX                  (4u)
#define LumenCom_SS2_PIN_INDEX                  (5u)
#define LumenCom_SS3_PIN_INDEX                  (6u)

#define LumenCom_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << LumenCom_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define LumenCom_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << LumenCom_RX_SCL_MOSI_PIN_INDEX)
#define LumenCom_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << LumenCom_TX_SDA_MISO_PIN_INDEX)
#define LumenCom_SCLK_PIN_MASK     ((uint32) 0x01u << LumenCom_SCLK_PIN_INDEX)
#define LumenCom_SS0_PIN_MASK     ((uint32) 0x01u << LumenCom_SS0_PIN_INDEX)
#define LumenCom_SS1_PIN_MASK                ((uint32) 0x01u << LumenCom_SS1_PIN_INDEX)
#define LumenCom_SS2_PIN_MASK                ((uint32) 0x01u << LumenCom_SS2_PIN_INDEX)
#define LumenCom_SS3_PIN_MASK                ((uint32) 0x01u << LumenCom_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define LumenCom_INTCFG_TYPE_MASK           (0x03u)
#define LumenCom_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define LumenCom_PIN_DM_ALG_HIZ  (0u)
#define LumenCom_PIN_DM_DIG_HIZ  (1u)
#define LumenCom_PIN_DM_OD_LO    (4u)
#define LumenCom_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define LumenCom_DM_MASK    (0x7u)
#define LumenCom_DM_SIZE    (3)
#define LumenCom_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) LumenCom_DM_MASK << (LumenCom_DM_SIZE * (pos)))) >> \
                                                              (LumenCom_DM_SIZE * (pos)) )

#if (LumenCom_TX_SDA_MISO_PIN)
    #define LumenCom_CHECK_TX_SDA_MISO_PIN_USED \
                (LumenCom_PIN_DM_ALG_HIZ != \
                    LumenCom_GET_P4_PIN_DM(LumenCom_uart_tx_i2c_sda_spi_miso_PC, \
                                                   LumenCom_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (LumenCom_TX_SDA_MISO_PIN) */

#if (LumenCom_SS0_PIN)
    #define LumenCom_CHECK_SS0_PIN_USED \
                (LumenCom_PIN_DM_ALG_HIZ != \
                    LumenCom_GET_P4_PIN_DM(LumenCom_spi_ss0_PC, \
                                                   LumenCom_spi_ss0_SHIFT))
#endif /* (LumenCom_SS0_PIN) */

/* Set bits-mask in register */
#define LumenCom_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define LumenCom_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define LumenCom_SET_HSIOM_SEL(reg, mask, pos, sel) LumenCom_SET_REGISTER_BITS(reg, mask, pos, sel)
#define LumenCom_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        LumenCom_SET_REGISTER_BITS(reg, mask, pos, intType)
#define LumenCom_SET_INP_DIS(reg, mask, val) LumenCom_SET_REGISTER_BIT(reg, mask, val)

/* LumenCom_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  LumenCom_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (LumenCom_CY_SCBIP_V0)
#if (LumenCom_I2C_PINS)
    #define LumenCom_SET_I2C_SCL_DR(val) LumenCom_scl_Write(val)

    #define LumenCom_SET_I2C_SCL_HSIOM_SEL(sel) \
                          LumenCom_SET_HSIOM_SEL(LumenCom_SCL_HSIOM_REG,  \
                                                         LumenCom_SCL_HSIOM_MASK, \
                                                         LumenCom_SCL_HSIOM_POS,  \
                                                         (sel))
    #define LumenCom_WAIT_SCL_SET_HIGH  (0u == LumenCom_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (LumenCom_RX_WAKE_SCL_MOSI_PIN)
    #define LumenCom_SET_I2C_SCL_DR(val) \
                            LumenCom_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define LumenCom_SET_I2C_SCL_HSIOM_SEL(sel) \
                    LumenCom_SET_HSIOM_SEL(LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   LumenCom_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   LumenCom_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define LumenCom_WAIT_SCL_SET_HIGH  (0u == LumenCom_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (LumenCom_RX_SCL_MOSI_PIN)
    #define LumenCom_SET_I2C_SCL_DR(val) \
                            LumenCom_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define LumenCom_SET_I2C_SCL_HSIOM_SEL(sel) \
                            LumenCom_SET_HSIOM_SEL(LumenCom_RX_SCL_MOSI_HSIOM_REG,  \
                                                           LumenCom_RX_SCL_MOSI_HSIOM_MASK, \
                                                           LumenCom_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define LumenCom_WAIT_SCL_SET_HIGH  (0u == LumenCom_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define LumenCom_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define LumenCom_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define LumenCom_WAIT_SCL_SET_HIGH  (0u)
#endif /* (LumenCom_I2C_PINS) */

/* SCB I2C: sda signal */
#if (LumenCom_I2C_PINS)
    #define LumenCom_WAIT_SDA_SET_HIGH  (0u == LumenCom_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (LumenCom_TX_SDA_MISO_PIN)
    #define LumenCom_WAIT_SDA_SET_HIGH  (0u == LumenCom_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define LumenCom_WAIT_SDA_SET_HIGH  (0u)
#endif /* (LumenCom_MOSI_SCL_RX_PIN) */
#endif /* (LumenCom_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define LumenCom_REMOVE_MOSI_SCL_RX_WAKE_PIN    LumenCom_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define LumenCom_REMOVE_MOSI_SCL_RX_PIN         LumenCom_REMOVE_RX_SCL_MOSI_PIN
#define LumenCom_REMOVE_MISO_SDA_TX_PIN         LumenCom_REMOVE_TX_SDA_MISO_PIN
#ifndef LumenCom_REMOVE_SCLK_PIN
#define LumenCom_REMOVE_SCLK_PIN                LumenCom_REMOVE_SCLK_PIN
#endif /* LumenCom_REMOVE_SCLK_PIN */
#ifndef LumenCom_REMOVE_SS0_PIN
#define LumenCom_REMOVE_SS0_PIN                 LumenCom_REMOVE_SS0_PIN
#endif /* LumenCom_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define LumenCom_MOSI_SCL_RX_WAKE_PIN   LumenCom_RX_WAKE_SCL_MOSI_PIN
#define LumenCom_MOSI_SCL_RX_PIN        LumenCom_RX_SCL_MOSI_PIN
#define LumenCom_MISO_SDA_TX_PIN        LumenCom_TX_SDA_MISO_PIN
#ifndef LumenCom_SCLK_PIN
#define LumenCom_SCLK_PIN               LumenCom_SCLK_PIN
#endif /* LumenCom_SCLK_PIN */
#ifndef LumenCom_SS0_PIN
#define LumenCom_SS0_PIN                LumenCom_SS0_PIN
#endif /* LumenCom_SS0_PIN */

#if (LumenCom_MOSI_SCL_RX_WAKE_PIN)
    #define LumenCom_MOSI_SCL_RX_WAKE_HSIOM_REG     LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_WAKE_HSIOM_PTR     LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_WAKE_HSIOM_MASK    LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_WAKE_HSIOM_POS     LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define LumenCom_MOSI_SCL_RX_WAKE_INTCFG_REG    LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_WAKE_INTCFG_PTR    LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define LumenCom_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  LumenCom_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (LumenCom_RX_WAKE_SCL_MOSI_PIN) */

#if (LumenCom_MOSI_SCL_RX_PIN)
    #define LumenCom_MOSI_SCL_RX_HSIOM_REG      LumenCom_RX_SCL_MOSI_HSIOM_REG
    #define LumenCom_MOSI_SCL_RX_HSIOM_PTR      LumenCom_RX_SCL_MOSI_HSIOM_PTR
    #define LumenCom_MOSI_SCL_RX_HSIOM_MASK     LumenCom_RX_SCL_MOSI_HSIOM_MASK
    #define LumenCom_MOSI_SCL_RX_HSIOM_POS      LumenCom_RX_SCL_MOSI_HSIOM_POS
#endif /* (LumenCom_MOSI_SCL_RX_PIN) */

#if (LumenCom_MISO_SDA_TX_PIN)
    #define LumenCom_MISO_SDA_TX_HSIOM_REG      LumenCom_TX_SDA_MISO_HSIOM_REG
    #define LumenCom_MISO_SDA_TX_HSIOM_PTR      LumenCom_TX_SDA_MISO_HSIOM_REG
    #define LumenCom_MISO_SDA_TX_HSIOM_MASK     LumenCom_TX_SDA_MISO_HSIOM_REG
    #define LumenCom_MISO_SDA_TX_HSIOM_POS      LumenCom_TX_SDA_MISO_HSIOM_REG
#endif /* (LumenCom_MISO_SDA_TX_PIN_PIN) */

#if (LumenCom_SCLK_PIN)
    #ifndef LumenCom_SCLK_HSIOM_REG
    #define LumenCom_SCLK_HSIOM_REG     LumenCom_SCLK_HSIOM_REG
    #define LumenCom_SCLK_HSIOM_PTR     LumenCom_SCLK_HSIOM_PTR
    #define LumenCom_SCLK_HSIOM_MASK    LumenCom_SCLK_HSIOM_MASK
    #define LumenCom_SCLK_HSIOM_POS     LumenCom_SCLK_HSIOM_POS
    #endif /* LumenCom_SCLK_HSIOM_REG */
#endif /* (LumenCom_SCLK_PIN) */

#if (LumenCom_SS0_PIN)
    #ifndef LumenCom_SS0_HSIOM_REG
    #define LumenCom_SS0_HSIOM_REG      LumenCom_SS0_HSIOM_REG
    #define LumenCom_SS0_HSIOM_PTR      LumenCom_SS0_HSIOM_PTR
    #define LumenCom_SS0_HSIOM_MASK     LumenCom_SS0_HSIOM_MASK
    #define LumenCom_SS0_HSIOM_POS      LumenCom_SS0_HSIOM_POS
    #endif /* LumenCom_SS0_HSIOM_REG */
#endif /* (LumenCom_SS0_PIN) */

#define LumenCom_MOSI_SCL_RX_WAKE_PIN_INDEX LumenCom_RX_WAKE_SCL_MOSI_PIN_INDEX
#define LumenCom_MOSI_SCL_RX_PIN_INDEX      LumenCom_RX_SCL_MOSI_PIN_INDEX
#define LumenCom_MISO_SDA_TX_PIN_INDEX      LumenCom_TX_SDA_MISO_PIN_INDEX
#ifndef LumenCom_SCLK_PIN_INDEX
#define LumenCom_SCLK_PIN_INDEX             LumenCom_SCLK_PIN_INDEX
#endif /* LumenCom_SCLK_PIN_INDEX */
#ifndef LumenCom_SS0_PIN_INDEX
#define LumenCom_SS0_PIN_INDEX              LumenCom_SS0_PIN_INDEX
#endif /* LumenCom_SS0_PIN_INDEX */

#define LumenCom_MOSI_SCL_RX_WAKE_PIN_MASK LumenCom_RX_WAKE_SCL_MOSI_PIN_MASK
#define LumenCom_MOSI_SCL_RX_PIN_MASK      LumenCom_RX_SCL_MOSI_PIN_MASK
#define LumenCom_MISO_SDA_TX_PIN_MASK      LumenCom_TX_SDA_MISO_PIN_MASK
#ifndef LumenCom_SCLK_PIN_MASK
#define LumenCom_SCLK_PIN_MASK             LumenCom_SCLK_PIN_MASK
#endif /* LumenCom_SCLK_PIN_MASK */
#ifndef LumenCom_SS0_PIN_MASK
#define LumenCom_SS0_PIN_MASK              LumenCom_SS0_PIN_MASK
#endif /* LumenCom_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_LumenCom_H) */


/* [] END OF FILE */
