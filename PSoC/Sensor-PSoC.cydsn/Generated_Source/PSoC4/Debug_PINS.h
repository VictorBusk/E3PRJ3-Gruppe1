/*******************************************************************************
* File Name: Debug_PINS.h
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

#if !defined(CY_SCB_PINS_Debug_H)
#define CY_SCB_PINS_Debug_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define Debug_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define Debug_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define Debug_REMOVE_TX_SDA_MISO_PIN      (1u)
#define Debug_REMOVE_SCLK_PIN      (1u)
#define Debug_REMOVE_SS0_PIN      (1u)
#define Debug_REMOVE_SS1_PIN                 (1u)
#define Debug_REMOVE_SS2_PIN                 (1u)
#define Debug_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define Debug_REMOVE_I2C_PINS                (1u)
#define Debug_REMOVE_SPI_MASTER_PINS         (1u)
#define Debug_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define Debug_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define Debug_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define Debug_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define Debug_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define Debug_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define Debug_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define Debug_REMOVE_SPI_SLAVE_PINS          (1u)
#define Debug_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define Debug_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define Debug_REMOVE_UART_TX_PIN             (0u)
#define Debug_REMOVE_UART_RX_TX_PIN          (1u)
#define Debug_REMOVE_UART_RX_PIN             (0u)
#define Debug_REMOVE_UART_RX_WAKE_PIN        (1u)
#define Debug_REMOVE_UART_RTS_PIN            (1u)
#define Debug_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define Debug_RX_WAKE_SCL_MOSI_PIN (0u == Debug_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define Debug_RX_SCL_MOSI_PIN     (0u == Debug_REMOVE_RX_SCL_MOSI_PIN)
#define Debug_TX_SDA_MISO_PIN     (0u == Debug_REMOVE_TX_SDA_MISO_PIN)
#define Debug_SCLK_PIN     (0u == Debug_REMOVE_SCLK_PIN)
#define Debug_SS0_PIN     (0u == Debug_REMOVE_SS0_PIN)
#define Debug_SS1_PIN                (0u == Debug_REMOVE_SS1_PIN)
#define Debug_SS2_PIN                (0u == Debug_REMOVE_SS2_PIN)
#define Debug_SS3_PIN                (0u == Debug_REMOVE_SS3_PIN)

/* Mode defined pins */
#define Debug_I2C_PINS               (0u == Debug_REMOVE_I2C_PINS)
#define Debug_SPI_MASTER_PINS        (0u == Debug_REMOVE_SPI_MASTER_PINS)
#define Debug_SPI_MASTER_SCLK_PIN    (0u == Debug_REMOVE_SPI_MASTER_SCLK_PIN)
#define Debug_SPI_MASTER_MOSI_PIN    (0u == Debug_REMOVE_SPI_MASTER_MOSI_PIN)
#define Debug_SPI_MASTER_MISO_PIN    (0u == Debug_REMOVE_SPI_MASTER_MISO_PIN)
#define Debug_SPI_MASTER_SS0_PIN     (0u == Debug_REMOVE_SPI_MASTER_SS0_PIN)
#define Debug_SPI_MASTER_SS1_PIN     (0u == Debug_REMOVE_SPI_MASTER_SS1_PIN)
#define Debug_SPI_MASTER_SS2_PIN     (0u == Debug_REMOVE_SPI_MASTER_SS2_PIN)
#define Debug_SPI_MASTER_SS3_PIN     (0u == Debug_REMOVE_SPI_MASTER_SS3_PIN)
#define Debug_SPI_SLAVE_PINS         (0u == Debug_REMOVE_SPI_SLAVE_PINS)
#define Debug_SPI_SLAVE_MOSI_PIN     (0u == Debug_REMOVE_SPI_SLAVE_MOSI_PIN)
#define Debug_SPI_SLAVE_MISO_PIN     (0u == Debug_REMOVE_SPI_SLAVE_MISO_PIN)
#define Debug_UART_TX_PIN            (0u == Debug_REMOVE_UART_TX_PIN)
#define Debug_UART_RX_TX_PIN         (0u == Debug_REMOVE_UART_RX_TX_PIN)
#define Debug_UART_RX_PIN            (0u == Debug_REMOVE_UART_RX_PIN)
#define Debug_UART_RX_WAKE_PIN       (0u == Debug_REMOVE_UART_RX_WAKE_PIN)
#define Debug_UART_RTS_PIN           (0u == Debug_REMOVE_UART_RTS_PIN)
#define Debug_UART_CTS_PIN           (0u == Debug_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (Debug_RX_WAKE_SCL_MOSI_PIN)
    #include "Debug_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (Debug_RX_SCL_MOSI) */

#if (Debug_RX_SCL_MOSI_PIN)
    #include "Debug_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (Debug_RX_SCL_MOSI) */

#if (Debug_TX_SDA_MISO_PIN)
    #include "Debug_uart_tx_i2c_sda_spi_miso.h"
#endif /* (Debug_TX_SDA_MISO) */

#if (Debug_SCLK_PIN)
    #include "Debug_spi_sclk.h"
#endif /* (Debug_SCLK) */

#if (Debug_SS0_PIN)
    #include "Debug_spi_ss0.h"
#endif /* (Debug_SS0_PIN) */

#if (Debug_SS1_PIN)
    #include "Debug_spi_ss1.h"
#endif /* (Debug_SS1_PIN) */

#if (Debug_SS2_PIN)
    #include "Debug_spi_ss2.h"
#endif /* (Debug_SS2_PIN) */

#if (Debug_SS3_PIN)
    #include "Debug_spi_ss3.h"
#endif /* (Debug_SS3_PIN) */

#if (Debug_I2C_PINS)
    #include "Debug_scl.h"
    #include "Debug_sda.h"
#endif /* (Debug_I2C_PINS) */

#if (Debug_SPI_MASTER_PINS)
#if (Debug_SPI_MASTER_SCLK_PIN)
    #include "Debug_sclk_m.h"
#endif /* (Debug_SPI_MASTER_SCLK_PIN) */

#if (Debug_SPI_MASTER_MOSI_PIN)
    #include "Debug_mosi_m.h"
#endif /* (Debug_SPI_MASTER_MOSI_PIN) */

#if (Debug_SPI_MASTER_MISO_PIN)
    #include "Debug_miso_m.h"
#endif /*(Debug_SPI_MASTER_MISO_PIN) */
#endif /* (Debug_SPI_MASTER_PINS) */

#if (Debug_SPI_SLAVE_PINS)
    #include "Debug_sclk_s.h"
    #include "Debug_ss_s.h"

#if (Debug_SPI_SLAVE_MOSI_PIN)
    #include "Debug_mosi_s.h"
#endif /* (Debug_SPI_SLAVE_MOSI_PIN) */

#if (Debug_SPI_SLAVE_MISO_PIN)
    #include "Debug_miso_s.h"
#endif /*(Debug_SPI_SLAVE_MISO_PIN) */
#endif /* (Debug_SPI_SLAVE_PINS) */

#if (Debug_SPI_MASTER_SS0_PIN)
    #include "Debug_ss0_m.h"
#endif /* (Debug_SPI_MASTER_SS0_PIN) */

#if (Debug_SPI_MASTER_SS1_PIN)
    #include "Debug_ss1_m.h"
#endif /* (Debug_SPI_MASTER_SS1_PIN) */

#if (Debug_SPI_MASTER_SS2_PIN)
    #include "Debug_ss2_m.h"
#endif /* (Debug_SPI_MASTER_SS2_PIN) */

#if (Debug_SPI_MASTER_SS3_PIN)
    #include "Debug_ss3_m.h"
#endif /* (Debug_SPI_MASTER_SS3_PIN) */

#if (Debug_UART_TX_PIN)
    #include "Debug_tx.h"
#endif /* (Debug_UART_TX_PIN) */

#if (Debug_UART_RX_TX_PIN)
    #include "Debug_rx_tx.h"
#endif /* (Debug_UART_RX_TX_PIN) */

#if (Debug_UART_RX_PIN)
    #include "Debug_rx.h"
#endif /* (Debug_UART_RX_PIN) */

#if (Debug_UART_RX_WAKE_PIN)
    #include "Debug_rx_wake.h"
#endif /* (Debug_UART_RX_WAKE_PIN) */

#if (Debug_UART_RTS_PIN)
    #include "Debug_rts.h"
#endif /* (Debug_UART_RTS_PIN) */

#if (Debug_UART_CTS_PIN)
    #include "Debug_cts.h"
#endif /* (Debug_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (Debug_RX_WAKE_SCL_MOSI_PIN)
    #define Debug_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) Debug_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Debug_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) Debug_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define Debug_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (Debug_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Debug_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (Debug_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define Debug_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) Debug_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Debug_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) Debug_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define Debug_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (Debug_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define Debug_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) Debug_INTCFG_TYPE_MASK << \
                                      Debug_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (Debug_RX_WAKE_SCL_MOSI_PIN) */

#if (Debug_RX_SCL_MOSI_PIN)
    #define Debug_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) Debug_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Debug_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) Debug_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define Debug_RX_SCL_MOSI_HSIOM_MASK  (Debug_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define Debug_RX_SCL_MOSI_HSIOM_POS   (Debug_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (Debug_RX_SCL_MOSI_PIN) */

#if (Debug_TX_SDA_MISO_PIN)
    #define Debug_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) Debug_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Debug_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) Debug_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define Debug_TX_SDA_MISO_HSIOM_MASK  (Debug_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define Debug_TX_SDA_MISO_HSIOM_POS   (Debug_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (Debug_TX_SDA_MISO_PIN) */

#if (Debug_SCLK_PIN)
    #define Debug_SCLK_HSIOM_REG   (*(reg32 *) Debug_spi_sclk__0__HSIOM)
    #define Debug_SCLK_HSIOM_PTR   ( (reg32 *) Debug_spi_sclk__0__HSIOM)
    #define Debug_SCLK_HSIOM_MASK  (Debug_spi_sclk__0__HSIOM_MASK)
    #define Debug_SCLK_HSIOM_POS   (Debug_spi_sclk__0__HSIOM_SHIFT)
#endif /* (Debug_SCLK_PIN) */

#if (Debug_SS0_PIN)
    #define Debug_SS0_HSIOM_REG   (*(reg32 *) Debug_spi_ss0__0__HSIOM)
    #define Debug_SS0_HSIOM_PTR   ( (reg32 *) Debug_spi_ss0__0__HSIOM)
    #define Debug_SS0_HSIOM_MASK  (Debug_spi_ss0__0__HSIOM_MASK)
    #define Debug_SS0_HSIOM_POS   (Debug_spi_ss0__0__HSIOM_SHIFT)
#endif /* (Debug_SS0_PIN) */

#if (Debug_SS1_PIN)
    #define Debug_SS1_HSIOM_REG      (*(reg32 *) Debug_spi_ss1__0__HSIOM)
    #define Debug_SS1_HSIOM_PTR      ( (reg32 *) Debug_spi_ss1__0__HSIOM)
    #define Debug_SS1_HSIOM_MASK     (Debug_spi_ss1__0__HSIOM_MASK)
    #define Debug_SS1_HSIOM_POS      (Debug_spi_ss1__0__HSIOM_SHIFT)
#endif /* (Debug_SS1_PIN) */

#if (Debug_SS2_PIN)
    #define Debug_SS2_HSIOM_REG     (*(reg32 *) Debug_spi_ss2__0__HSIOM)
    #define Debug_SS2_HSIOM_PTR     ( (reg32 *) Debug_spi_ss2__0__HSIOM)
    #define Debug_SS2_HSIOM_MASK    (Debug_spi_ss2__0__HSIOM_MASK)
    #define Debug_SS2_HSIOM_POS     (Debug_spi_ss2__0__HSIOM_SHIFT)
#endif /* (Debug_SS2_PIN) */

#if (Debug_SS3_PIN)
    #define Debug_SS3_HSIOM_REG     (*(reg32 *) Debug_spi_ss3__0__HSIOM)
    #define Debug_SS3_HSIOM_PTR     ( (reg32 *) Debug_spi_ss3__0__HSIOM)
    #define Debug_SS3_HSIOM_MASK    (Debug_spi_ss3__0__HSIOM_MASK)
    #define Debug_SS3_HSIOM_POS     (Debug_spi_ss3__0__HSIOM_SHIFT)
#endif /* (Debug_SS3_PIN) */

#if (Debug_I2C_PINS)
    #define Debug_SCL_HSIOM_REG     (*(reg32 *) Debug_scl__0__HSIOM)
    #define Debug_SCL_HSIOM_PTR     ( (reg32 *) Debug_scl__0__HSIOM)
    #define Debug_SCL_HSIOM_MASK    (Debug_scl__0__HSIOM_MASK)
    #define Debug_SCL_HSIOM_POS     (Debug_scl__0__HSIOM_SHIFT)

    #define Debug_SDA_HSIOM_REG     (*(reg32 *) Debug_sda__0__HSIOM)
    #define Debug_SDA_HSIOM_PTR     ( (reg32 *) Debug_sda__0__HSIOM)
    #define Debug_SDA_HSIOM_MASK    (Debug_sda__0__HSIOM_MASK)
    #define Debug_SDA_HSIOM_POS     (Debug_sda__0__HSIOM_SHIFT)
#endif /* (Debug_I2C_PINS) */

#if (Debug_SPI_MASTER_SCLK_PIN)
    #define Debug_SCLK_M_HSIOM_REG   (*(reg32 *) Debug_sclk_m__0__HSIOM)
    #define Debug_SCLK_M_HSIOM_PTR   ( (reg32 *) Debug_sclk_m__0__HSIOM)
    #define Debug_SCLK_M_HSIOM_MASK  (Debug_sclk_m__0__HSIOM_MASK)
    #define Debug_SCLK_M_HSIOM_POS   (Debug_sclk_m__0__HSIOM_SHIFT)
#endif /* (Debug_SPI_MASTER_SCLK_PIN) */

#if (Debug_SPI_MASTER_SS0_PIN)
    #define Debug_SS0_M_HSIOM_REG    (*(reg32 *) Debug_ss0_m__0__HSIOM)
    #define Debug_SS0_M_HSIOM_PTR    ( (reg32 *) Debug_ss0_m__0__HSIOM)
    #define Debug_SS0_M_HSIOM_MASK   (Debug_ss0_m__0__HSIOM_MASK)
    #define Debug_SS0_M_HSIOM_POS    (Debug_ss0_m__0__HSIOM_SHIFT)
#endif /* (Debug_SPI_MASTER_SS0_PIN) */

#if (Debug_SPI_MASTER_SS1_PIN)
    #define Debug_SS1_M_HSIOM_REG    (*(reg32 *) Debug_ss1_m__0__HSIOM)
    #define Debug_SS1_M_HSIOM_PTR    ( (reg32 *) Debug_ss1_m__0__HSIOM)
    #define Debug_SS1_M_HSIOM_MASK   (Debug_ss1_m__0__HSIOM_MASK)
    #define Debug_SS1_M_HSIOM_POS    (Debug_ss1_m__0__HSIOM_SHIFT)
#endif /* (Debug_SPI_MASTER_SS1_PIN) */

#if (Debug_SPI_MASTER_SS2_PIN)
    #define Debug_SS2_M_HSIOM_REG    (*(reg32 *) Debug_ss2_m__0__HSIOM)
    #define Debug_SS2_M_HSIOM_PTR    ( (reg32 *) Debug_ss2_m__0__HSIOM)
    #define Debug_SS2_M_HSIOM_MASK   (Debug_ss2_m__0__HSIOM_MASK)
    #define Debug_SS2_M_HSIOM_POS    (Debug_ss2_m__0__HSIOM_SHIFT)
#endif /* (Debug_SPI_MASTER_SS2_PIN) */

#if (Debug_SPI_MASTER_SS3_PIN)
    #define Debug_SS3_M_HSIOM_REG    (*(reg32 *) Debug_ss3_m__0__HSIOM)
    #define Debug_SS3_M_HSIOM_PTR    ( (reg32 *) Debug_ss3_m__0__HSIOM)
    #define Debug_SS3_M_HSIOM_MASK   (Debug_ss3_m__0__HSIOM_MASK)
    #define Debug_SS3_M_HSIOM_POS    (Debug_ss3_m__0__HSIOM_SHIFT)
#endif /* (Debug_SPI_MASTER_SS3_PIN) */

#if (Debug_UART_TX_PIN)
    #define Debug_TX_HSIOM_REG   (*(reg32 *) Debug_tx__0__HSIOM)
    #define Debug_TX_HSIOM_PTR   ( (reg32 *) Debug_tx_0__HSIOM)
    #define Debug_TX_HSIOM_MASK  (Debug_tx__0__HSIOM_MASK)
    #define Debug_TX_HSIOM_POS   (Debug_tx__0__HSIOM_SHIFT)
#endif /* (Debug_UART_TX_PIN) */

#if (Debug_UART_RTS_PIN)
    #define Debug_RTS_HSIOM_REG  (*(reg32 *) Debug_rts__0__HSIOM)
    #define Debug_RTS_HSIOM_PTR  ( (reg32 *) Debug_rts__0__HSIOM)
    #define Debug_RTS_HSIOM_MASK (Debug_rts__0__HSIOM_MASK)
    #define Debug_RTS_HSIOM_POS  (Debug_rts__0__HSIOM_SHIFT)
#endif /* (Debug_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define Debug_HSIOM_DEF_SEL      (0x00u)
#define Debug_HSIOM_GPIO_SEL     (0x00u)
#define Debug_HSIOM_UART_SEL     (0x09u)
#define Debug_HSIOM_I2C_SEL      (0x0Eu)
#define Debug_HSIOM_SPI_SEL      (0x0Fu)

#define Debug_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define Debug_RX_SCL_MOSI_PIN_INDEX       (0u)
#define Debug_TX_SDA_MISO_PIN_INDEX       (1u)
#define Debug_SCLK_PIN_INDEX       (2u)
#define Debug_SS0_PIN_INDEX       (3u)
#define Debug_SS1_PIN_INDEX                  (4u)
#define Debug_SS2_PIN_INDEX                  (5u)
#define Debug_SS3_PIN_INDEX                  (6u)

#define Debug_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << Debug_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define Debug_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << Debug_RX_SCL_MOSI_PIN_INDEX)
#define Debug_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << Debug_TX_SDA_MISO_PIN_INDEX)
#define Debug_SCLK_PIN_MASK     ((uint32) 0x01u << Debug_SCLK_PIN_INDEX)
#define Debug_SS0_PIN_MASK     ((uint32) 0x01u << Debug_SS0_PIN_INDEX)
#define Debug_SS1_PIN_MASK                ((uint32) 0x01u << Debug_SS1_PIN_INDEX)
#define Debug_SS2_PIN_MASK                ((uint32) 0x01u << Debug_SS2_PIN_INDEX)
#define Debug_SS3_PIN_MASK                ((uint32) 0x01u << Debug_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define Debug_INTCFG_TYPE_MASK           (0x03u)
#define Debug_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define Debug_PIN_DM_ALG_HIZ  (0u)
#define Debug_PIN_DM_DIG_HIZ  (1u)
#define Debug_PIN_DM_OD_LO    (4u)
#define Debug_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define Debug_DM_MASK    (0x7u)
#define Debug_DM_SIZE    (3)
#define Debug_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) Debug_DM_MASK << (Debug_DM_SIZE * (pos)))) >> \
                                                              (Debug_DM_SIZE * (pos)) )

#if (Debug_TX_SDA_MISO_PIN)
    #define Debug_CHECK_TX_SDA_MISO_PIN_USED \
                (Debug_PIN_DM_ALG_HIZ != \
                    Debug_GET_P4_PIN_DM(Debug_uart_tx_i2c_sda_spi_miso_PC, \
                                                   Debug_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (Debug_TX_SDA_MISO_PIN) */

#if (Debug_SS0_PIN)
    #define Debug_CHECK_SS0_PIN_USED \
                (Debug_PIN_DM_ALG_HIZ != \
                    Debug_GET_P4_PIN_DM(Debug_spi_ss0_PC, \
                                                   Debug_spi_ss0_SHIFT))
#endif /* (Debug_SS0_PIN) */

/* Set bits-mask in register */
#define Debug_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define Debug_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define Debug_SET_HSIOM_SEL(reg, mask, pos, sel) Debug_SET_REGISTER_BITS(reg, mask, pos, sel)
#define Debug_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        Debug_SET_REGISTER_BITS(reg, mask, pos, intType)
#define Debug_SET_INP_DIS(reg, mask, val) Debug_SET_REGISTER_BIT(reg, mask, val)

/* Debug_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  Debug_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (Debug_CY_SCBIP_V0)
#if (Debug_I2C_PINS)
    #define Debug_SET_I2C_SCL_DR(val) Debug_scl_Write(val)

    #define Debug_SET_I2C_SCL_HSIOM_SEL(sel) \
                          Debug_SET_HSIOM_SEL(Debug_SCL_HSIOM_REG,  \
                                                         Debug_SCL_HSIOM_MASK, \
                                                         Debug_SCL_HSIOM_POS,  \
                                                         (sel))
    #define Debug_WAIT_SCL_SET_HIGH  (0u == Debug_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (Debug_RX_WAKE_SCL_MOSI_PIN)
    #define Debug_SET_I2C_SCL_DR(val) \
                            Debug_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define Debug_SET_I2C_SCL_HSIOM_SEL(sel) \
                    Debug_SET_HSIOM_SEL(Debug_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   Debug_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   Debug_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define Debug_WAIT_SCL_SET_HIGH  (0u == Debug_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (Debug_RX_SCL_MOSI_PIN)
    #define Debug_SET_I2C_SCL_DR(val) \
                            Debug_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define Debug_SET_I2C_SCL_HSIOM_SEL(sel) \
                            Debug_SET_HSIOM_SEL(Debug_RX_SCL_MOSI_HSIOM_REG,  \
                                                           Debug_RX_SCL_MOSI_HSIOM_MASK, \
                                                           Debug_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define Debug_WAIT_SCL_SET_HIGH  (0u == Debug_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define Debug_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define Debug_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define Debug_WAIT_SCL_SET_HIGH  (0u)
#endif /* (Debug_I2C_PINS) */

/* SCB I2C: sda signal */
#if (Debug_I2C_PINS)
    #define Debug_WAIT_SDA_SET_HIGH  (0u == Debug_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (Debug_TX_SDA_MISO_PIN)
    #define Debug_WAIT_SDA_SET_HIGH  (0u == Debug_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define Debug_WAIT_SDA_SET_HIGH  (0u)
#endif /* (Debug_MOSI_SCL_RX_PIN) */
#endif /* (Debug_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define Debug_REMOVE_MOSI_SCL_RX_WAKE_PIN    Debug_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define Debug_REMOVE_MOSI_SCL_RX_PIN         Debug_REMOVE_RX_SCL_MOSI_PIN
#define Debug_REMOVE_MISO_SDA_TX_PIN         Debug_REMOVE_TX_SDA_MISO_PIN
#ifndef Debug_REMOVE_SCLK_PIN
#define Debug_REMOVE_SCLK_PIN                Debug_REMOVE_SCLK_PIN
#endif /* Debug_REMOVE_SCLK_PIN */
#ifndef Debug_REMOVE_SS0_PIN
#define Debug_REMOVE_SS0_PIN                 Debug_REMOVE_SS0_PIN
#endif /* Debug_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define Debug_MOSI_SCL_RX_WAKE_PIN   Debug_RX_WAKE_SCL_MOSI_PIN
#define Debug_MOSI_SCL_RX_PIN        Debug_RX_SCL_MOSI_PIN
#define Debug_MISO_SDA_TX_PIN        Debug_TX_SDA_MISO_PIN
#ifndef Debug_SCLK_PIN
#define Debug_SCLK_PIN               Debug_SCLK_PIN
#endif /* Debug_SCLK_PIN */
#ifndef Debug_SS0_PIN
#define Debug_SS0_PIN                Debug_SS0_PIN
#endif /* Debug_SS0_PIN */

#if (Debug_MOSI_SCL_RX_WAKE_PIN)
    #define Debug_MOSI_SCL_RX_WAKE_HSIOM_REG     Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_WAKE_HSIOM_PTR     Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_WAKE_HSIOM_MASK    Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_WAKE_HSIOM_POS     Debug_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Debug_MOSI_SCL_RX_WAKE_INTCFG_REG    Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_WAKE_INTCFG_PTR    Debug_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define Debug_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  Debug_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (Debug_RX_WAKE_SCL_MOSI_PIN) */

#if (Debug_MOSI_SCL_RX_PIN)
    #define Debug_MOSI_SCL_RX_HSIOM_REG      Debug_RX_SCL_MOSI_HSIOM_REG
    #define Debug_MOSI_SCL_RX_HSIOM_PTR      Debug_RX_SCL_MOSI_HSIOM_PTR
    #define Debug_MOSI_SCL_RX_HSIOM_MASK     Debug_RX_SCL_MOSI_HSIOM_MASK
    #define Debug_MOSI_SCL_RX_HSIOM_POS      Debug_RX_SCL_MOSI_HSIOM_POS
#endif /* (Debug_MOSI_SCL_RX_PIN) */

#if (Debug_MISO_SDA_TX_PIN)
    #define Debug_MISO_SDA_TX_HSIOM_REG      Debug_TX_SDA_MISO_HSIOM_REG
    #define Debug_MISO_SDA_TX_HSIOM_PTR      Debug_TX_SDA_MISO_HSIOM_REG
    #define Debug_MISO_SDA_TX_HSIOM_MASK     Debug_TX_SDA_MISO_HSIOM_REG
    #define Debug_MISO_SDA_TX_HSIOM_POS      Debug_TX_SDA_MISO_HSIOM_REG
#endif /* (Debug_MISO_SDA_TX_PIN_PIN) */

#if (Debug_SCLK_PIN)
    #ifndef Debug_SCLK_HSIOM_REG
    #define Debug_SCLK_HSIOM_REG     Debug_SCLK_HSIOM_REG
    #define Debug_SCLK_HSIOM_PTR     Debug_SCLK_HSIOM_PTR
    #define Debug_SCLK_HSIOM_MASK    Debug_SCLK_HSIOM_MASK
    #define Debug_SCLK_HSIOM_POS     Debug_SCLK_HSIOM_POS
    #endif /* Debug_SCLK_HSIOM_REG */
#endif /* (Debug_SCLK_PIN) */

#if (Debug_SS0_PIN)
    #ifndef Debug_SS0_HSIOM_REG
    #define Debug_SS0_HSIOM_REG      Debug_SS0_HSIOM_REG
    #define Debug_SS0_HSIOM_PTR      Debug_SS0_HSIOM_PTR
    #define Debug_SS0_HSIOM_MASK     Debug_SS0_HSIOM_MASK
    #define Debug_SS0_HSIOM_POS      Debug_SS0_HSIOM_POS
    #endif /* Debug_SS0_HSIOM_REG */
#endif /* (Debug_SS0_PIN) */

#define Debug_MOSI_SCL_RX_WAKE_PIN_INDEX Debug_RX_WAKE_SCL_MOSI_PIN_INDEX
#define Debug_MOSI_SCL_RX_PIN_INDEX      Debug_RX_SCL_MOSI_PIN_INDEX
#define Debug_MISO_SDA_TX_PIN_INDEX      Debug_TX_SDA_MISO_PIN_INDEX
#ifndef Debug_SCLK_PIN_INDEX
#define Debug_SCLK_PIN_INDEX             Debug_SCLK_PIN_INDEX
#endif /* Debug_SCLK_PIN_INDEX */
#ifndef Debug_SS0_PIN_INDEX
#define Debug_SS0_PIN_INDEX              Debug_SS0_PIN_INDEX
#endif /* Debug_SS0_PIN_INDEX */

#define Debug_MOSI_SCL_RX_WAKE_PIN_MASK Debug_RX_WAKE_SCL_MOSI_PIN_MASK
#define Debug_MOSI_SCL_RX_PIN_MASK      Debug_RX_SCL_MOSI_PIN_MASK
#define Debug_MISO_SDA_TX_PIN_MASK      Debug_TX_SDA_MISO_PIN_MASK
#ifndef Debug_SCLK_PIN_MASK
#define Debug_SCLK_PIN_MASK             Debug_SCLK_PIN_MASK
#endif /* Debug_SCLK_PIN_MASK */
#ifndef Debug_SS0_PIN_MASK
#define Debug_SS0_PIN_MASK              Debug_SS0_PIN_MASK
#endif /* Debug_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_Debug_H) */


/* [] END OF FILE */
