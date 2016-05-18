/*******************************************************************************
* File Name: SPIS_PINS.h
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

#if !defined(CY_SCB_PINS_SPIS_H)
#define CY_SCB_PINS_SPIS_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SPIS_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define SPIS_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define SPIS_REMOVE_TX_SDA_MISO_PIN      (1u)
#define SPIS_REMOVE_SCLK_PIN      (1u)
#define SPIS_REMOVE_SS0_PIN      (1u)
#define SPIS_REMOVE_SS1_PIN                 (1u)
#define SPIS_REMOVE_SS2_PIN                 (1u)
#define SPIS_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SPIS_REMOVE_I2C_PINS                (1u)
#define SPIS_REMOVE_SPI_MASTER_PINS         (1u)
#define SPIS_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define SPIS_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define SPIS_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define SPIS_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define SPIS_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define SPIS_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SPIS_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SPIS_REMOVE_SPI_SLAVE_PINS          (0u)
#define SPIS_REMOVE_SPI_SLAVE_MOSI_PIN      (0u)
#define SPIS_REMOVE_SPI_SLAVE_MISO_PIN      (0u)
#define SPIS_REMOVE_UART_TX_PIN             (1u)
#define SPIS_REMOVE_UART_RX_TX_PIN          (1u)
#define SPIS_REMOVE_UART_RX_PIN             (1u)
#define SPIS_REMOVE_UART_RX_WAKE_PIN        (1u)
#define SPIS_REMOVE_UART_RTS_PIN            (1u)
#define SPIS_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define SPIS_RX_WAKE_SCL_MOSI_PIN (0u == SPIS_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define SPIS_RX_SCL_MOSI_PIN     (0u == SPIS_REMOVE_RX_SCL_MOSI_PIN)
#define SPIS_TX_SDA_MISO_PIN     (0u == SPIS_REMOVE_TX_SDA_MISO_PIN)
#define SPIS_SCLK_PIN     (0u == SPIS_REMOVE_SCLK_PIN)
#define SPIS_SS0_PIN     (0u == SPIS_REMOVE_SS0_PIN)
#define SPIS_SS1_PIN                (0u == SPIS_REMOVE_SS1_PIN)
#define SPIS_SS2_PIN                (0u == SPIS_REMOVE_SS2_PIN)
#define SPIS_SS3_PIN                (0u == SPIS_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SPIS_I2C_PINS               (0u == SPIS_REMOVE_I2C_PINS)
#define SPIS_SPI_MASTER_PINS        (0u == SPIS_REMOVE_SPI_MASTER_PINS)
#define SPIS_SPI_MASTER_SCLK_PIN    (0u == SPIS_REMOVE_SPI_MASTER_SCLK_PIN)
#define SPIS_SPI_MASTER_MOSI_PIN    (0u == SPIS_REMOVE_SPI_MASTER_MOSI_PIN)
#define SPIS_SPI_MASTER_MISO_PIN    (0u == SPIS_REMOVE_SPI_MASTER_MISO_PIN)
#define SPIS_SPI_MASTER_SS0_PIN     (0u == SPIS_REMOVE_SPI_MASTER_SS0_PIN)
#define SPIS_SPI_MASTER_SS1_PIN     (0u == SPIS_REMOVE_SPI_MASTER_SS1_PIN)
#define SPIS_SPI_MASTER_SS2_PIN     (0u == SPIS_REMOVE_SPI_MASTER_SS2_PIN)
#define SPIS_SPI_MASTER_SS3_PIN     (0u == SPIS_REMOVE_SPI_MASTER_SS3_PIN)
#define SPIS_SPI_SLAVE_PINS         (0u == SPIS_REMOVE_SPI_SLAVE_PINS)
#define SPIS_SPI_SLAVE_MOSI_PIN     (0u == SPIS_REMOVE_SPI_SLAVE_MOSI_PIN)
#define SPIS_SPI_SLAVE_MISO_PIN     (0u == SPIS_REMOVE_SPI_SLAVE_MISO_PIN)
#define SPIS_UART_TX_PIN            (0u == SPIS_REMOVE_UART_TX_PIN)
#define SPIS_UART_RX_TX_PIN         (0u == SPIS_REMOVE_UART_RX_TX_PIN)
#define SPIS_UART_RX_PIN            (0u == SPIS_REMOVE_UART_RX_PIN)
#define SPIS_UART_RX_WAKE_PIN       (0u == SPIS_REMOVE_UART_RX_WAKE_PIN)
#define SPIS_UART_RTS_PIN           (0u == SPIS_REMOVE_UART_RTS_PIN)
#define SPIS_UART_CTS_PIN           (0u == SPIS_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (SPIS_RX_WAKE_SCL_MOSI_PIN)
    #include "SPIS_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (SPIS_RX_SCL_MOSI) */

#if (SPIS_RX_SCL_MOSI_PIN)
    #include "SPIS_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (SPIS_RX_SCL_MOSI) */

#if (SPIS_TX_SDA_MISO_PIN)
    #include "SPIS_uart_tx_i2c_sda_spi_miso.h"
#endif /* (SPIS_TX_SDA_MISO) */

#if (SPIS_SCLK_PIN)
    #include "SPIS_spi_sclk.h"
#endif /* (SPIS_SCLK) */

#if (SPIS_SS0_PIN)
    #include "SPIS_spi_ss0.h"
#endif /* (SPIS_SS0_PIN) */

#if (SPIS_SS1_PIN)
    #include "SPIS_spi_ss1.h"
#endif /* (SPIS_SS1_PIN) */

#if (SPIS_SS2_PIN)
    #include "SPIS_spi_ss2.h"
#endif /* (SPIS_SS2_PIN) */

#if (SPIS_SS3_PIN)
    #include "SPIS_spi_ss3.h"
#endif /* (SPIS_SS3_PIN) */

#if (SPIS_I2C_PINS)
    #include "SPIS_scl.h"
    #include "SPIS_sda.h"
#endif /* (SPIS_I2C_PINS) */

#if (SPIS_SPI_MASTER_PINS)
#if (SPIS_SPI_MASTER_SCLK_PIN)
    #include "SPIS_sclk_m.h"
#endif /* (SPIS_SPI_MASTER_SCLK_PIN) */

#if (SPIS_SPI_MASTER_MOSI_PIN)
    #include "SPIS_mosi_m.h"
#endif /* (SPIS_SPI_MASTER_MOSI_PIN) */

#if (SPIS_SPI_MASTER_MISO_PIN)
    #include "SPIS_miso_m.h"
#endif /*(SPIS_SPI_MASTER_MISO_PIN) */
#endif /* (SPIS_SPI_MASTER_PINS) */

#if (SPIS_SPI_SLAVE_PINS)
    #include "SPIS_sclk_s.h"
    #include "SPIS_ss_s.h"

#if (SPIS_SPI_SLAVE_MOSI_PIN)
    #include "SPIS_mosi_s.h"
#endif /* (SPIS_SPI_SLAVE_MOSI_PIN) */

#if (SPIS_SPI_SLAVE_MISO_PIN)
    #include "SPIS_miso_s.h"
#endif /*(SPIS_SPI_SLAVE_MISO_PIN) */
#endif /* (SPIS_SPI_SLAVE_PINS) */

#if (SPIS_SPI_MASTER_SS0_PIN)
    #include "SPIS_ss0_m.h"
#endif /* (SPIS_SPI_MASTER_SS0_PIN) */

#if (SPIS_SPI_MASTER_SS1_PIN)
    #include "SPIS_ss1_m.h"
#endif /* (SPIS_SPI_MASTER_SS1_PIN) */

#if (SPIS_SPI_MASTER_SS2_PIN)
    #include "SPIS_ss2_m.h"
#endif /* (SPIS_SPI_MASTER_SS2_PIN) */

#if (SPIS_SPI_MASTER_SS3_PIN)
    #include "SPIS_ss3_m.h"
#endif /* (SPIS_SPI_MASTER_SS3_PIN) */

#if (SPIS_UART_TX_PIN)
    #include "SPIS_tx.h"
#endif /* (SPIS_UART_TX_PIN) */

#if (SPIS_UART_RX_TX_PIN)
    #include "SPIS_rx_tx.h"
#endif /* (SPIS_UART_RX_TX_PIN) */

#if (SPIS_UART_RX_PIN)
    #include "SPIS_rx.h"
#endif /* (SPIS_UART_RX_PIN) */

#if (SPIS_UART_RX_WAKE_PIN)
    #include "SPIS_rx_wake.h"
#endif /* (SPIS_UART_RX_WAKE_PIN) */

#if (SPIS_UART_RTS_PIN)
    #include "SPIS_rts.h"
#endif /* (SPIS_UART_RTS_PIN) */

#if (SPIS_UART_CTS_PIN)
    #include "SPIS_cts.h"
#endif /* (SPIS_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (SPIS_RX_WAKE_SCL_MOSI_PIN)
    #define SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIS_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIS_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPIS_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define SPIS_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPIS_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) SPIS_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SPIS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (SPIS_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define SPIS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) SPIS_INTCFG_TYPE_MASK << \
                                      SPIS_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (SPIS_RX_WAKE_SCL_MOSI_PIN) */

#if (SPIS_RX_SCL_MOSI_PIN)
    #define SPIS_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) SPIS_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIS_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SPIS_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SPIS_RX_SCL_MOSI_HSIOM_MASK  (SPIS_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SPIS_RX_SCL_MOSI_HSIOM_POS   (SPIS_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (SPIS_RX_SCL_MOSI_PIN) */

#if (SPIS_TX_SDA_MISO_PIN)
    #define SPIS_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) SPIS_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SPIS_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) SPIS_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SPIS_TX_SDA_MISO_HSIOM_MASK  (SPIS_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define SPIS_TX_SDA_MISO_HSIOM_POS   (SPIS_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (SPIS_TX_SDA_MISO_PIN) */

#if (SPIS_SCLK_PIN)
    #define SPIS_SCLK_HSIOM_REG   (*(reg32 *) SPIS_spi_sclk__0__HSIOM)
    #define SPIS_SCLK_HSIOM_PTR   ( (reg32 *) SPIS_spi_sclk__0__HSIOM)
    #define SPIS_SCLK_HSIOM_MASK  (SPIS_spi_sclk__0__HSIOM_MASK)
    #define SPIS_SCLK_HSIOM_POS   (SPIS_spi_sclk__0__HSIOM_SHIFT)
#endif /* (SPIS_SCLK_PIN) */

#if (SPIS_SS0_PIN)
    #define SPIS_SS0_HSIOM_REG   (*(reg32 *) SPIS_spi_ss0__0__HSIOM)
    #define SPIS_SS0_HSIOM_PTR   ( (reg32 *) SPIS_spi_ss0__0__HSIOM)
    #define SPIS_SS0_HSIOM_MASK  (SPIS_spi_ss0__0__HSIOM_MASK)
    #define SPIS_SS0_HSIOM_POS   (SPIS_spi_ss0__0__HSIOM_SHIFT)
#endif /* (SPIS_SS0_PIN) */

#if (SPIS_SS1_PIN)
    #define SPIS_SS1_HSIOM_REG      (*(reg32 *) SPIS_spi_ss1__0__HSIOM)
    #define SPIS_SS1_HSIOM_PTR      ( (reg32 *) SPIS_spi_ss1__0__HSIOM)
    #define SPIS_SS1_HSIOM_MASK     (SPIS_spi_ss1__0__HSIOM_MASK)
    #define SPIS_SS1_HSIOM_POS      (SPIS_spi_ss1__0__HSIOM_SHIFT)
#endif /* (SPIS_SS1_PIN) */

#if (SPIS_SS2_PIN)
    #define SPIS_SS2_HSIOM_REG     (*(reg32 *) SPIS_spi_ss2__0__HSIOM)
    #define SPIS_SS2_HSIOM_PTR     ( (reg32 *) SPIS_spi_ss2__0__HSIOM)
    #define SPIS_SS2_HSIOM_MASK    (SPIS_spi_ss2__0__HSIOM_MASK)
    #define SPIS_SS2_HSIOM_POS     (SPIS_spi_ss2__0__HSIOM_SHIFT)
#endif /* (SPIS_SS2_PIN) */

#if (SPIS_SS3_PIN)
    #define SPIS_SS3_HSIOM_REG     (*(reg32 *) SPIS_spi_ss3__0__HSIOM)
    #define SPIS_SS3_HSIOM_PTR     ( (reg32 *) SPIS_spi_ss3__0__HSIOM)
    #define SPIS_SS3_HSIOM_MASK    (SPIS_spi_ss3__0__HSIOM_MASK)
    #define SPIS_SS3_HSIOM_POS     (SPIS_spi_ss3__0__HSIOM_SHIFT)
#endif /* (SPIS_SS3_PIN) */

#if (SPIS_I2C_PINS)
    #define SPIS_SCL_HSIOM_REG     (*(reg32 *) SPIS_scl__0__HSIOM)
    #define SPIS_SCL_HSIOM_PTR     ( (reg32 *) SPIS_scl__0__HSIOM)
    #define SPIS_SCL_HSIOM_MASK    (SPIS_scl__0__HSIOM_MASK)
    #define SPIS_SCL_HSIOM_POS     (SPIS_scl__0__HSIOM_SHIFT)

    #define SPIS_SDA_HSIOM_REG     (*(reg32 *) SPIS_sda__0__HSIOM)
    #define SPIS_SDA_HSIOM_PTR     ( (reg32 *) SPIS_sda__0__HSIOM)
    #define SPIS_SDA_HSIOM_MASK    (SPIS_sda__0__HSIOM_MASK)
    #define SPIS_SDA_HSIOM_POS     (SPIS_sda__0__HSIOM_SHIFT)
#endif /* (SPIS_I2C_PINS) */

#if (SPIS_SPI_MASTER_SCLK_PIN)
    #define SPIS_SCLK_M_HSIOM_REG   (*(reg32 *) SPIS_sclk_m__0__HSIOM)
    #define SPIS_SCLK_M_HSIOM_PTR   ( (reg32 *) SPIS_sclk_m__0__HSIOM)
    #define SPIS_SCLK_M_HSIOM_MASK  (SPIS_sclk_m__0__HSIOM_MASK)
    #define SPIS_SCLK_M_HSIOM_POS   (SPIS_sclk_m__0__HSIOM_SHIFT)
#endif /* (SPIS_SPI_MASTER_SCLK_PIN) */

#if (SPIS_SPI_MASTER_SS0_PIN)
    #define SPIS_SS0_M_HSIOM_REG    (*(reg32 *) SPIS_ss0_m__0__HSIOM)
    #define SPIS_SS0_M_HSIOM_PTR    ( (reg32 *) SPIS_ss0_m__0__HSIOM)
    #define SPIS_SS0_M_HSIOM_MASK   (SPIS_ss0_m__0__HSIOM_MASK)
    #define SPIS_SS0_M_HSIOM_POS    (SPIS_ss0_m__0__HSIOM_SHIFT)
#endif /* (SPIS_SPI_MASTER_SS0_PIN) */

#if (SPIS_SPI_MASTER_SS1_PIN)
    #define SPIS_SS1_M_HSIOM_REG    (*(reg32 *) SPIS_ss1_m__0__HSIOM)
    #define SPIS_SS1_M_HSIOM_PTR    ( (reg32 *) SPIS_ss1_m__0__HSIOM)
    #define SPIS_SS1_M_HSIOM_MASK   (SPIS_ss1_m__0__HSIOM_MASK)
    #define SPIS_SS1_M_HSIOM_POS    (SPIS_ss1_m__0__HSIOM_SHIFT)
#endif /* (SPIS_SPI_MASTER_SS1_PIN) */

#if (SPIS_SPI_MASTER_SS2_PIN)
    #define SPIS_SS2_M_HSIOM_REG    (*(reg32 *) SPIS_ss2_m__0__HSIOM)
    #define SPIS_SS2_M_HSIOM_PTR    ( (reg32 *) SPIS_ss2_m__0__HSIOM)
    #define SPIS_SS2_M_HSIOM_MASK   (SPIS_ss2_m__0__HSIOM_MASK)
    #define SPIS_SS2_M_HSIOM_POS    (SPIS_ss2_m__0__HSIOM_SHIFT)
#endif /* (SPIS_SPI_MASTER_SS2_PIN) */

#if (SPIS_SPI_MASTER_SS3_PIN)
    #define SPIS_SS3_M_HSIOM_REG    (*(reg32 *) SPIS_ss3_m__0__HSIOM)
    #define SPIS_SS3_M_HSIOM_PTR    ( (reg32 *) SPIS_ss3_m__0__HSIOM)
    #define SPIS_SS3_M_HSIOM_MASK   (SPIS_ss3_m__0__HSIOM_MASK)
    #define SPIS_SS3_M_HSIOM_POS    (SPIS_ss3_m__0__HSIOM_SHIFT)
#endif /* (SPIS_SPI_MASTER_SS3_PIN) */

#if (SPIS_UART_TX_PIN)
    #define SPIS_TX_HSIOM_REG   (*(reg32 *) SPIS_tx__0__HSIOM)
    #define SPIS_TX_HSIOM_PTR   ( (reg32 *) SPIS_tx_0__HSIOM)
    #define SPIS_TX_HSIOM_MASK  (SPIS_tx__0__HSIOM_MASK)
    #define SPIS_TX_HSIOM_POS   (SPIS_tx__0__HSIOM_SHIFT)
#endif /* (SPIS_UART_TX_PIN) */

#if (SPIS_UART_RTS_PIN)
    #define SPIS_RTS_HSIOM_REG  (*(reg32 *) SPIS_rts__0__HSIOM)
    #define SPIS_RTS_HSIOM_PTR  ( (reg32 *) SPIS_rts__0__HSIOM)
    #define SPIS_RTS_HSIOM_MASK (SPIS_rts__0__HSIOM_MASK)
    #define SPIS_RTS_HSIOM_POS  (SPIS_rts__0__HSIOM_SHIFT)
#endif /* (SPIS_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define SPIS_HSIOM_DEF_SEL      (0x00u)
#define SPIS_HSIOM_GPIO_SEL     (0x00u)
#define SPIS_HSIOM_UART_SEL     (0x09u)
#define SPIS_HSIOM_I2C_SEL      (0x0Eu)
#define SPIS_HSIOM_SPI_SEL      (0x0Fu)

#define SPIS_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define SPIS_RX_SCL_MOSI_PIN_INDEX       (0u)
#define SPIS_TX_SDA_MISO_PIN_INDEX       (1u)
#define SPIS_SCLK_PIN_INDEX       (2u)
#define SPIS_SS0_PIN_INDEX       (3u)
#define SPIS_SS1_PIN_INDEX                  (4u)
#define SPIS_SS2_PIN_INDEX                  (5u)
#define SPIS_SS3_PIN_INDEX                  (6u)

#define SPIS_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << SPIS_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define SPIS_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << SPIS_RX_SCL_MOSI_PIN_INDEX)
#define SPIS_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << SPIS_TX_SDA_MISO_PIN_INDEX)
#define SPIS_SCLK_PIN_MASK     ((uint32) 0x01u << SPIS_SCLK_PIN_INDEX)
#define SPIS_SS0_PIN_MASK     ((uint32) 0x01u << SPIS_SS0_PIN_INDEX)
#define SPIS_SS1_PIN_MASK                ((uint32) 0x01u << SPIS_SS1_PIN_INDEX)
#define SPIS_SS2_PIN_MASK                ((uint32) 0x01u << SPIS_SS2_PIN_INDEX)
#define SPIS_SS3_PIN_MASK                ((uint32) 0x01u << SPIS_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define SPIS_INTCFG_TYPE_MASK           (0x03u)
#define SPIS_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define SPIS_PIN_DM_ALG_HIZ  (0u)
#define SPIS_PIN_DM_DIG_HIZ  (1u)
#define SPIS_PIN_DM_OD_LO    (4u)
#define SPIS_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define SPIS_DM_MASK    (0x7u)
#define SPIS_DM_SIZE    (3)
#define SPIS_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) SPIS_DM_MASK << (SPIS_DM_SIZE * (pos)))) >> \
                                                              (SPIS_DM_SIZE * (pos)) )

#if (SPIS_TX_SDA_MISO_PIN)
    #define SPIS_CHECK_TX_SDA_MISO_PIN_USED \
                (SPIS_PIN_DM_ALG_HIZ != \
                    SPIS_GET_P4_PIN_DM(SPIS_uart_tx_i2c_sda_spi_miso_PC, \
                                                   SPIS_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (SPIS_TX_SDA_MISO_PIN) */

#if (SPIS_SS0_PIN)
    #define SPIS_CHECK_SS0_PIN_USED \
                (SPIS_PIN_DM_ALG_HIZ != \
                    SPIS_GET_P4_PIN_DM(SPIS_spi_ss0_PC, \
                                                   SPIS_spi_ss0_SHIFT))
#endif /* (SPIS_SS0_PIN) */

/* Set bits-mask in register */
#define SPIS_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define SPIS_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define SPIS_SET_HSIOM_SEL(reg, mask, pos, sel) SPIS_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SPIS_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SPIS_SET_REGISTER_BITS(reg, mask, pos, intType)
#define SPIS_SET_INP_DIS(reg, mask, val) SPIS_SET_REGISTER_BIT(reg, mask, val)

/* SPIS_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SPIS_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (SPIS_CY_SCBIP_V0)
#if (SPIS_I2C_PINS)
    #define SPIS_SET_I2C_SCL_DR(val) SPIS_scl_Write(val)

    #define SPIS_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SPIS_SET_HSIOM_SEL(SPIS_SCL_HSIOM_REG,  \
                                                         SPIS_SCL_HSIOM_MASK, \
                                                         SPIS_SCL_HSIOM_POS,  \
                                                         (sel))
    #define SPIS_WAIT_SCL_SET_HIGH  (0u == SPIS_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (SPIS_RX_WAKE_SCL_MOSI_PIN)
    #define SPIS_SET_I2C_SCL_DR(val) \
                            SPIS_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define SPIS_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SPIS_SET_HSIOM_SEL(SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   SPIS_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   SPIS_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define SPIS_WAIT_SCL_SET_HIGH  (0u == SPIS_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (SPIS_RX_SCL_MOSI_PIN)
    #define SPIS_SET_I2C_SCL_DR(val) \
                            SPIS_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define SPIS_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SPIS_SET_HSIOM_SEL(SPIS_RX_SCL_MOSI_HSIOM_REG,  \
                                                           SPIS_RX_SCL_MOSI_HSIOM_MASK, \
                                                           SPIS_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define SPIS_WAIT_SCL_SET_HIGH  (0u == SPIS_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define SPIS_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define SPIS_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define SPIS_WAIT_SCL_SET_HIGH  (0u)
#endif /* (SPIS_I2C_PINS) */

/* SCB I2C: sda signal */
#if (SPIS_I2C_PINS)
    #define SPIS_WAIT_SDA_SET_HIGH  (0u == SPIS_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (SPIS_TX_SDA_MISO_PIN)
    #define SPIS_WAIT_SDA_SET_HIGH  (0u == SPIS_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define SPIS_WAIT_SDA_SET_HIGH  (0u)
#endif /* (SPIS_MOSI_SCL_RX_PIN) */
#endif /* (SPIS_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define SPIS_REMOVE_MOSI_SCL_RX_WAKE_PIN    SPIS_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define SPIS_REMOVE_MOSI_SCL_RX_PIN         SPIS_REMOVE_RX_SCL_MOSI_PIN
#define SPIS_REMOVE_MISO_SDA_TX_PIN         SPIS_REMOVE_TX_SDA_MISO_PIN
#ifndef SPIS_REMOVE_SCLK_PIN
#define SPIS_REMOVE_SCLK_PIN                SPIS_REMOVE_SCLK_PIN
#endif /* SPIS_REMOVE_SCLK_PIN */
#ifndef SPIS_REMOVE_SS0_PIN
#define SPIS_REMOVE_SS0_PIN                 SPIS_REMOVE_SS0_PIN
#endif /* SPIS_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define SPIS_MOSI_SCL_RX_WAKE_PIN   SPIS_RX_WAKE_SCL_MOSI_PIN
#define SPIS_MOSI_SCL_RX_PIN        SPIS_RX_SCL_MOSI_PIN
#define SPIS_MISO_SDA_TX_PIN        SPIS_TX_SDA_MISO_PIN
#ifndef SPIS_SCLK_PIN
#define SPIS_SCLK_PIN               SPIS_SCLK_PIN
#endif /* SPIS_SCLK_PIN */
#ifndef SPIS_SS0_PIN
#define SPIS_SS0_PIN                SPIS_SS0_PIN
#endif /* SPIS_SS0_PIN */

#if (SPIS_MOSI_SCL_RX_WAKE_PIN)
    #define SPIS_MOSI_SCL_RX_WAKE_HSIOM_REG     SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_WAKE_HSIOM_PTR     SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_WAKE_HSIOM_MASK    SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_WAKE_HSIOM_POS     SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPIS_MOSI_SCL_RX_WAKE_INTCFG_REG    SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_WAKE_INTCFG_PTR    SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SPIS_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  SPIS_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (SPIS_RX_WAKE_SCL_MOSI_PIN) */

#if (SPIS_MOSI_SCL_RX_PIN)
    #define SPIS_MOSI_SCL_RX_HSIOM_REG      SPIS_RX_SCL_MOSI_HSIOM_REG
    #define SPIS_MOSI_SCL_RX_HSIOM_PTR      SPIS_RX_SCL_MOSI_HSIOM_PTR
    #define SPIS_MOSI_SCL_RX_HSIOM_MASK     SPIS_RX_SCL_MOSI_HSIOM_MASK
    #define SPIS_MOSI_SCL_RX_HSIOM_POS      SPIS_RX_SCL_MOSI_HSIOM_POS
#endif /* (SPIS_MOSI_SCL_RX_PIN) */

#if (SPIS_MISO_SDA_TX_PIN)
    #define SPIS_MISO_SDA_TX_HSIOM_REG      SPIS_TX_SDA_MISO_HSIOM_REG
    #define SPIS_MISO_SDA_TX_HSIOM_PTR      SPIS_TX_SDA_MISO_HSIOM_REG
    #define SPIS_MISO_SDA_TX_HSIOM_MASK     SPIS_TX_SDA_MISO_HSIOM_REG
    #define SPIS_MISO_SDA_TX_HSIOM_POS      SPIS_TX_SDA_MISO_HSIOM_REG
#endif /* (SPIS_MISO_SDA_TX_PIN_PIN) */

#if (SPIS_SCLK_PIN)
    #ifndef SPIS_SCLK_HSIOM_REG
    #define SPIS_SCLK_HSIOM_REG     SPIS_SCLK_HSIOM_REG
    #define SPIS_SCLK_HSIOM_PTR     SPIS_SCLK_HSIOM_PTR
    #define SPIS_SCLK_HSIOM_MASK    SPIS_SCLK_HSIOM_MASK
    #define SPIS_SCLK_HSIOM_POS     SPIS_SCLK_HSIOM_POS
    #endif /* SPIS_SCLK_HSIOM_REG */
#endif /* (SPIS_SCLK_PIN) */

#if (SPIS_SS0_PIN)
    #ifndef SPIS_SS0_HSIOM_REG
    #define SPIS_SS0_HSIOM_REG      SPIS_SS0_HSIOM_REG
    #define SPIS_SS0_HSIOM_PTR      SPIS_SS0_HSIOM_PTR
    #define SPIS_SS0_HSIOM_MASK     SPIS_SS0_HSIOM_MASK
    #define SPIS_SS0_HSIOM_POS      SPIS_SS0_HSIOM_POS
    #endif /* SPIS_SS0_HSIOM_REG */
#endif /* (SPIS_SS0_PIN) */

#define SPIS_MOSI_SCL_RX_WAKE_PIN_INDEX SPIS_RX_WAKE_SCL_MOSI_PIN_INDEX
#define SPIS_MOSI_SCL_RX_PIN_INDEX      SPIS_RX_SCL_MOSI_PIN_INDEX
#define SPIS_MISO_SDA_TX_PIN_INDEX      SPIS_TX_SDA_MISO_PIN_INDEX
#ifndef SPIS_SCLK_PIN_INDEX
#define SPIS_SCLK_PIN_INDEX             SPIS_SCLK_PIN_INDEX
#endif /* SPIS_SCLK_PIN_INDEX */
#ifndef SPIS_SS0_PIN_INDEX
#define SPIS_SS0_PIN_INDEX              SPIS_SS0_PIN_INDEX
#endif /* SPIS_SS0_PIN_INDEX */

#define SPIS_MOSI_SCL_RX_WAKE_PIN_MASK SPIS_RX_WAKE_SCL_MOSI_PIN_MASK
#define SPIS_MOSI_SCL_RX_PIN_MASK      SPIS_RX_SCL_MOSI_PIN_MASK
#define SPIS_MISO_SDA_TX_PIN_MASK      SPIS_TX_SDA_MISO_PIN_MASK
#ifndef SPIS_SCLK_PIN_MASK
#define SPIS_SCLK_PIN_MASK             SPIS_SCLK_PIN_MASK
#endif /* SPIS_SCLK_PIN_MASK */
#ifndef SPIS_SS0_PIN_MASK
#define SPIS_SS0_PIN_MASK              SPIS_SS0_PIN_MASK
#endif /* SPIS_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_SPIS_H) */


/* [] END OF FILE */
