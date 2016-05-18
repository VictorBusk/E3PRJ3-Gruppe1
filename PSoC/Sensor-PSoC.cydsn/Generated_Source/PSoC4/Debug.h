/*******************************************************************************
* File Name: Debug.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_Debug_H)
#define CY_SCB_Debug_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define Debug_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define Debug_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define Debug_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

#define Debug_SCB_MODE                     (4u)

/* SCB modes enum */
#define Debug_SCB_MODE_I2C                 (0x01u)
#define Debug_SCB_MODE_SPI                 (0x02u)
#define Debug_SCB_MODE_UART                (0x04u)
#define Debug_SCB_MODE_EZI2C               (0x08u)
#define Debug_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define Debug_SCB_MODE_I2C_CONST_CFG       (Debug_SCB_MODE_I2C       == Debug_SCB_MODE)
#define Debug_SCB_MODE_SPI_CONST_CFG       (Debug_SCB_MODE_SPI       == Debug_SCB_MODE)
#define Debug_SCB_MODE_UART_CONST_CFG      (Debug_SCB_MODE_UART      == Debug_SCB_MODE)
#define Debug_SCB_MODE_EZI2C_CONST_CFG     (Debug_SCB_MODE_EZI2C     == Debug_SCB_MODE)
#define Debug_SCB_MODE_UNCONFIG_CONST_CFG  (Debug_SCB_MODE_UNCONFIG  == Debug_SCB_MODE)

/* Condition compilation for includes */
#define Debug_SCB_MODE_I2C_INC      (0u !=(Debug_SCB_MODE_I2C   & Debug_SCB_MODE))
#define Debug_SCB_MODE_EZI2C_INC    (0u !=(Debug_SCB_MODE_EZI2C & Debug_SCB_MODE))
#if (!Debug_CY_SCBIP_V1)
    #define Debug_SCB_MODE_SPI_INC  (0u !=(Debug_SCB_MODE_SPI   & Debug_SCB_MODE))
    #define Debug_SCB_MODE_UART_INC (0u !=(Debug_SCB_MODE_UART  & Debug_SCB_MODE))
#else
    #define Debug_SCB_MODE_SPI_INC  (0u)
    #define Debug_SCB_MODE_UART_INC (0u)
#endif /* (!Debug_CY_SCBIP_V1) */

/* Interrupts remove options */
#define Debug_REMOVE_SCB_IRQ             (1u)
#define Debug_SCB_IRQ_INTERNAL           (0u == Debug_REMOVE_SCB_IRQ)

#define Debug_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define Debug_UART_RX_WAKEUP_IRQ         (0u == Debug_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define Debug_SCB_INTR_MODE_NONE     (0u)
#define Debug_SCB_INTR_MODE_INTERNAL (1u)
#define Debug_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define Debug_REMOVE_SCB_CLK     (0u)
#define Debug_SCB_CLK_INTERNAL   (0u == Debug_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "Debug_PINS.h"

#if (Debug_SCB_CLK_INTERNAL)
    #include "Debug_SCBCLK.h"
#endif /* (Debug_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} Debug_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void Debug_Init(void);
void Debug_Enable(void);
void Debug_Start(void);
void Debug_Stop(void);

/* Sleep and Wakeup APis */
void Debug_Sleep(void);
void Debug_Wakeup(void);

#if (Debug_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void Debug_SetCustomInterruptHandler(void (*func)(void));
#endif /* (Debug_SCB_IRQ_INTERNAL) */

/* Interface to internal interrupt component */
#if (Debug_SCB_IRQ_INTERNAL)
    #define Debug_EnableInt()        CyIntEnable      (Debug_ISR_NUMBER)
    #define Debug_DisableInt()       CyIntDisable     (Debug_ISR_NUMBER)
    #define Debug_ClearPendingInt()  CyIntClearPending(Debug_ISR_NUMBER)
#endif /* (Debug_SCB_IRQ_INTERNAL) */

#if (Debug_UART_RX_WAKEUP_IRQ)
    #define Debug_RxWakeEnableInt()        CyIntEnable      (Debug_RX_WAKE_ISR_NUMBER)
    #define Debug_RxWakeDisableInt()       CyIntDisable     (Debug_RX_WAKE_ISR_NUMBER)
    #define Debug_RxWakeClearPendingInt()  CyIntClearPending(Debug_RX_WAKE_ISR_NUMBER)
#endif /* (Debug_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define Debug_GetInterruptCause()    (Debug_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define Debug_SetRxInterruptMode(interruptMask)     Debug_WRITE_INTR_RX_MASK(interruptMask)
#define Debug_ClearRxInterruptSource(interruptMask) Debug_CLEAR_INTR_RX(interruptMask)
#define Debug_SetRxInterrupt(interruptMask)         Debug_SET_INTR_RX(interruptMask)
#define Debug_GetRxInterruptSource()                (Debug_INTR_RX_REG)
#define Debug_GetRxInterruptMode()                  (Debug_INTR_RX_MASK_REG)
#define Debug_GetRxInterruptSourceMasked()          (Debug_INTR_RX_MASKED_REG)
void Debug_SetRxFifoLevel(uint32 level);

/* APIs to service INTR_TX register */
#define Debug_SetTxInterruptMode(interruptMask)     Debug_WRITE_INTR_TX_MASK(interruptMask)
#define Debug_ClearTxInterruptSource(interruptMask) Debug_CLEAR_INTR_TX(interruptMask)
#define Debug_SetTxInterrupt(interruptMask)         Debug_SET_INTR_TX(interruptMask)
#define Debug_GetTxInterruptSource()                (Debug_INTR_TX_REG)
#define Debug_GetTxInterruptMode()                  (Debug_INTR_TX_MASK_REG)
#define Debug_GetTxInterruptSourceMasked()          (Debug_INTR_TX_MASKED_REG)
void Debug_SetTxFifoLevel(uint32 level);

/* APIs to service INTR_MASTER register */
#define Debug_SetMasterInterruptMode(interruptMask)    Debug_WRITE_INTR_MASTER_MASK(interruptMask)
#define Debug_ClearMasterInterruptSource(interruptMask) Debug_CLEAR_INTR_MASTER(interruptMask)
#define Debug_SetMasterInterrupt(interruptMask)         Debug_SET_INTR_MASTER(interruptMask)
#define Debug_GetMasterInterruptSource()                (Debug_INTR_MASTER_REG)
#define Debug_GetMasterInterruptMode()                  (Debug_INTR_MASTER_MASK_REG)
#define Debug_GetMasterInterruptSourceMasked()          (Debug_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define Debug_SetSlaveInterruptMode(interruptMask)     Debug_WRITE_INTR_SLAVE_MASK(interruptMask)
#define Debug_ClearSlaveInterruptSource(interruptMask) Debug_CLEAR_INTR_SLAVE(interruptMask)
#define Debug_SetSlaveInterrupt(interruptMask)         Debug_SET_INTR_SLAVE(interruptMask)
#define Debug_GetSlaveInterruptSource()                (Debug_INTR_SLAVE_REG)
#define Debug_GetSlaveInterruptMode()                  (Debug_INTR_SLAVE_MASK_REG)
#define Debug_GetSlaveInterruptSourceMasked()          (Debug_INTR_SLAVE_MASKED_REG)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 Debug_initVar;


/***************************************
*              Registers
***************************************/

#define Debug_CTRL_REG               (*(reg32 *) Debug_SCB__CTRL)
#define Debug_CTRL_PTR               ( (reg32 *) Debug_SCB__CTRL)

#define Debug_STATUS_REG             (*(reg32 *) Debug_SCB__STATUS)
#define Debug_STATUS_PTR             ( (reg32 *) Debug_SCB__STATUS)

#if (!Debug_CY_SCBIP_V1)
    #define Debug_SPI_CTRL_REG           (*(reg32 *) Debug_SCB__SPI_CTRL)
    #define Debug_SPI_CTRL_PTR           ( (reg32 *) Debug_SCB__SPI_CTRL)

    #define Debug_SPI_STATUS_REG         (*(reg32 *) Debug_SCB__SPI_STATUS)
    #define Debug_SPI_STATUS_PTR         ( (reg32 *) Debug_SCB__SPI_STATUS)

    #define Debug_UART_CTRL_REG          (*(reg32 *) Debug_SCB__UART_CTRL)
    #define Debug_UART_CTRL_PTR          ( (reg32 *) Debug_SCB__UART_CTRL)

    #define Debug_UART_TX_CTRL_REG       (*(reg32 *) Debug_SCB__UART_TX_CTRL)
    #define Debug_UART_TX_CTRL_PTR       ( (reg32 *) Debug_SCB__UART_TX_CTRL)

    #define Debug_UART_RX_CTRL_REG       (*(reg32 *) Debug_SCB__UART_RX_CTRL)
    #define Debug_UART_RX_CTRL_PTR       ( (reg32 *) Debug_SCB__UART_RX_CTRL)

    #define Debug_UART_RX_STATUS_REG     (*(reg32 *) Debug_SCB__UART_RX_STATUS)
    #define Debug_UART_RX_STATUS_PTR     ( (reg32 *) Debug_SCB__UART_RX_STATUS)
#endif /* (!Debug_CY_SCBIP_V1) */

#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_UART_FLOW_CTRL_REG     (*(reg32 *) Debug_SCB__UART_FLOW_CTRL)
    #define Debug_UART_FLOW_CTRL_PTR     ( (reg32 *) Debug_SCB__UART_FLOW_CTRL)
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#define Debug_I2C_CTRL_REG           (*(reg32 *) Debug_SCB__I2C_CTRL)
#define Debug_I2C_CTRL_PTR           ( (reg32 *) Debug_SCB__I2C_CTRL)

#define Debug_I2C_STATUS_REG         (*(reg32 *) Debug_SCB__I2C_STATUS)
#define Debug_I2C_STATUS_PTR         ( (reg32 *) Debug_SCB__I2C_STATUS)

#define Debug_I2C_MASTER_CMD_REG     (*(reg32 *) Debug_SCB__I2C_M_CMD)
#define Debug_I2C_MASTER_CMD_PTR     ( (reg32 *) Debug_SCB__I2C_M_CMD)

#define Debug_I2C_SLAVE_CMD_REG      (*(reg32 *) Debug_SCB__I2C_S_CMD)
#define Debug_I2C_SLAVE_CMD_PTR      ( (reg32 *) Debug_SCB__I2C_S_CMD)

#define Debug_I2C_CFG_REG            (*(reg32 *) Debug_SCB__I2C_CFG)
#define Debug_I2C_CFG_PTR            ( (reg32 *) Debug_SCB__I2C_CFG)

#define Debug_TX_CTRL_REG            (*(reg32 *) Debug_SCB__TX_CTRL)
#define Debug_TX_CTRL_PTR            ( (reg32 *) Debug_SCB__TX_CTRL)

#define Debug_TX_FIFO_CTRL_REG       (*(reg32 *) Debug_SCB__TX_FIFO_CTRL)
#define Debug_TX_FIFO_CTRL_PTR       ( (reg32 *) Debug_SCB__TX_FIFO_CTRL)

#define Debug_TX_FIFO_STATUS_REG     (*(reg32 *) Debug_SCB__TX_FIFO_STATUS)
#define Debug_TX_FIFO_STATUS_PTR     ( (reg32 *) Debug_SCB__TX_FIFO_STATUS)

#define Debug_TX_FIFO_WR_REG         (*(reg32 *) Debug_SCB__TX_FIFO_WR)
#define Debug_TX_FIFO_WR_PTR         ( (reg32 *) Debug_SCB__TX_FIFO_WR)

#define Debug_RX_CTRL_REG            (*(reg32 *) Debug_SCB__RX_CTRL)
#define Debug_RX_CTRL_PTR            ( (reg32 *) Debug_SCB__RX_CTRL)

#define Debug_RX_FIFO_CTRL_REG       (*(reg32 *) Debug_SCB__RX_FIFO_CTRL)
#define Debug_RX_FIFO_CTRL_PTR       ( (reg32 *) Debug_SCB__RX_FIFO_CTRL)

#define Debug_RX_FIFO_STATUS_REG     (*(reg32 *) Debug_SCB__RX_FIFO_STATUS)
#define Debug_RX_FIFO_STATUS_PTR     ( (reg32 *) Debug_SCB__RX_FIFO_STATUS)

#define Debug_RX_MATCH_REG           (*(reg32 *) Debug_SCB__RX_MATCH)
#define Debug_RX_MATCH_PTR           ( (reg32 *) Debug_SCB__RX_MATCH)

#define Debug_RX_FIFO_RD_REG         (*(reg32 *) Debug_SCB__RX_FIFO_RD)
#define Debug_RX_FIFO_RD_PTR         ( (reg32 *) Debug_SCB__RX_FIFO_RD)

#define Debug_RX_FIFO_RD_SILENT_REG  (*(reg32 *) Debug_SCB__RX_FIFO_RD_SILENT)
#define Debug_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) Debug_SCB__RX_FIFO_RD_SILENT)

#define Debug_EZBUF_DATA00_REG       (*(reg32 *) Debug_SCB__EZ_DATA00)
#define Debug_EZBUF_DATA00_PTR       ( (reg32 *) Debug_SCB__EZ_DATA00)

#define Debug_INTR_CAUSE_REG         (*(reg32 *) Debug_SCB__INTR_CAUSE)
#define Debug_INTR_CAUSE_PTR         ( (reg32 *) Debug_SCB__INTR_CAUSE)

#define Debug_INTR_I2C_EC_REG        (*(reg32 *) Debug_SCB__INTR_I2C_EC)
#define Debug_INTR_I2C_EC_PTR        ( (reg32 *) Debug_SCB__INTR_I2C_EC)

#define Debug_INTR_I2C_EC_MASK_REG   (*(reg32 *) Debug_SCB__INTR_I2C_EC_MASK)
#define Debug_INTR_I2C_EC_MASK_PTR   ( (reg32 *) Debug_SCB__INTR_I2C_EC_MASK)

#define Debug_INTR_I2C_EC_MASKED_REG (*(reg32 *) Debug_SCB__INTR_I2C_EC_MASKED)
#define Debug_INTR_I2C_EC_MASKED_PTR ( (reg32 *) Debug_SCB__INTR_I2C_EC_MASKED)

#if (!Debug_CY_SCBIP_V1)
    #define Debug_INTR_SPI_EC_REG        (*(reg32 *) Debug_SCB__INTR_SPI_EC)
    #define Debug_INTR_SPI_EC_PTR        ( (reg32 *) Debug_SCB__INTR_SPI_EC)

    #define Debug_INTR_SPI_EC_MASK_REG   (*(reg32 *) Debug_SCB__INTR_SPI_EC_MASK)
    #define Debug_INTR_SPI_EC_MASK_PTR   ( (reg32 *) Debug_SCB__INTR_SPI_EC_MASK)

    #define Debug_INTR_SPI_EC_MASKED_REG (*(reg32 *) Debug_SCB__INTR_SPI_EC_MASKED)
    #define Debug_INTR_SPI_EC_MASKED_PTR ( (reg32 *) Debug_SCB__INTR_SPI_EC_MASKED)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_INTR_MASTER_REG        (*(reg32 *) Debug_SCB__INTR_M)
#define Debug_INTR_MASTER_PTR        ( (reg32 *) Debug_SCB__INTR_M)

#define Debug_INTR_MASTER_SET_REG    (*(reg32 *) Debug_SCB__INTR_M_SET)
#define Debug_INTR_MASTER_SET_PTR    ( (reg32 *) Debug_SCB__INTR_M_SET)

#define Debug_INTR_MASTER_MASK_REG   (*(reg32 *) Debug_SCB__INTR_M_MASK)
#define Debug_INTR_MASTER_MASK_PTR   ( (reg32 *) Debug_SCB__INTR_M_MASK)

#define Debug_INTR_MASTER_MASKED_REG (*(reg32 *) Debug_SCB__INTR_M_MASKED)
#define Debug_INTR_MASTER_MASKED_PTR ( (reg32 *) Debug_SCB__INTR_M_MASKED)

#define Debug_INTR_SLAVE_REG         (*(reg32 *) Debug_SCB__INTR_S)
#define Debug_INTR_SLAVE_PTR         ( (reg32 *) Debug_SCB__INTR_S)

#define Debug_INTR_SLAVE_SET_REG     (*(reg32 *) Debug_SCB__INTR_S_SET)
#define Debug_INTR_SLAVE_SET_PTR     ( (reg32 *) Debug_SCB__INTR_S_SET)

#define Debug_INTR_SLAVE_MASK_REG    (*(reg32 *) Debug_SCB__INTR_S_MASK)
#define Debug_INTR_SLAVE_MASK_PTR    ( (reg32 *) Debug_SCB__INTR_S_MASK)

#define Debug_INTR_SLAVE_MASKED_REG  (*(reg32 *) Debug_SCB__INTR_S_MASKED)
#define Debug_INTR_SLAVE_MASKED_PTR  ( (reg32 *) Debug_SCB__INTR_S_MASKED)

#define Debug_INTR_TX_REG            (*(reg32 *) Debug_SCB__INTR_TX)
#define Debug_INTR_TX_PTR            ( (reg32 *) Debug_SCB__INTR_TX)

#define Debug_INTR_TX_SET_REG        (*(reg32 *) Debug_SCB__INTR_TX_SET)
#define Debug_INTR_TX_SET_PTR        ( (reg32 *) Debug_SCB__INTR_TX_SET)

#define Debug_INTR_TX_MASK_REG       (*(reg32 *) Debug_SCB__INTR_TX_MASK)
#define Debug_INTR_TX_MASK_PTR       ( (reg32 *) Debug_SCB__INTR_TX_MASK)

#define Debug_INTR_TX_MASKED_REG     (*(reg32 *) Debug_SCB__INTR_TX_MASKED)
#define Debug_INTR_TX_MASKED_PTR     ( (reg32 *) Debug_SCB__INTR_TX_MASKED)

#define Debug_INTR_RX_REG            (*(reg32 *) Debug_SCB__INTR_RX)
#define Debug_INTR_RX_PTR            ( (reg32 *) Debug_SCB__INTR_RX)

#define Debug_INTR_RX_SET_REG        (*(reg32 *) Debug_SCB__INTR_RX_SET)
#define Debug_INTR_RX_SET_PTR        ( (reg32 *) Debug_SCB__INTR_RX_SET)

#define Debug_INTR_RX_MASK_REG       (*(reg32 *) Debug_SCB__INTR_RX_MASK)
#define Debug_INTR_RX_MASK_PTR       ( (reg32 *) Debug_SCB__INTR_RX_MASK)

#define Debug_INTR_RX_MASKED_REG     (*(reg32 *) Debug_SCB__INTR_RX_MASKED)
#define Debug_INTR_RX_MASKED_PTR     ( (reg32 *) Debug_SCB__INTR_RX_MASKED)

#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* FF_DATA_NR_LOG2_PLUS1 = 4, MASK = 2^4 - 1 = 15 */
    #define Debug_FF_DATA_NR_LOG2_MASK       (0x07u) /* FF_DATA_NR_LOG2 = 3, MASK = 2^3 - 1 = 7 */
#else
    #define Debug_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* FF_DATA_NR_LOG2_PLUS1 = 5, MASK = 2^5 - 1 = 31 */
    #define Debug_FF_DATA_NR_LOG2_MASK       (0x0Fu) /* FF_DATA_NR_LOG2 = 4, MASK = 2^4 - 1 = 15 */
#endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */


/***************************************
*        Registers Constants
***************************************/

#if (Debug_SCB_IRQ_INTERNAL)
    #define Debug_ISR_NUMBER     ((uint8) Debug_SCB_IRQ__INTC_NUMBER)
    #define Debug_ISR_PRIORITY   ((uint8) Debug_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (Debug_SCB_IRQ_INTERNAL) */

#if (Debug_UART_RX_WAKEUP_IRQ)
    #define Debug_RX_WAKE_ISR_NUMBER     ((uint8) Debug_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define Debug_RX_WAKE_ISR_PRIORITY   ((uint8) Debug_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (Debug_UART_RX_WAKEUP_IRQ) */

/* Debug_CTRL_REG */
#define Debug_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define Debug_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define Debug_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define Debug_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
#define Debug_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define Debug_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define Debug_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define Debug_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define Debug_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define Debug_CTRL_EC_AM_MODE        ((uint32) 0x01u << Debug_CTRL_EC_AM_MODE_POS)
#define Debug_CTRL_EC_OP_MODE        ((uint32) 0x01u << Debug_CTRL_EC_OP_MODE_POS)
#define Debug_CTRL_EZBUF_MODE        ((uint32) 0x01u << Debug_CTRL_EZBUF_MODE_POS)
#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_CTRL_BYTE_MODE ((uint32) 0x01u << Debug_CTRL_BYTE_MODE_POS)
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
#define Debug_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << Debug_CTRL_ADDR_ACCEPT_POS)
#define Debug_CTRL_BLOCK             ((uint32) 0x01u << Debug_CTRL_BLOCK_POS)
#define Debug_CTRL_MODE_MASK         ((uint32) 0x03u << Debug_CTRL_MODE_POS)
#define Debug_CTRL_MODE_I2C          ((uint32) 0x00u)
#define Debug_CTRL_MODE_SPI          ((uint32) 0x01u << Debug_CTRL_MODE_POS)
#define Debug_CTRL_MODE_UART         ((uint32) 0x02u << Debug_CTRL_MODE_POS)
#define Debug_CTRL_ENABLED           ((uint32) 0x01u << Debug_CTRL_ENABLED_POS)

/* Debug_STATUS_REG */
#define Debug_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define Debug_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* Debug_SPI_CTRL_REG  */
#define Debug_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define Debug_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define Debug_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define Debug_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define Debug_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define Debug_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define Debug_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define Debug_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define Debug_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */
#define Debug_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define Debug_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define Debug_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define Debug_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define Debug_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define Debug_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << Debug_SPI_CTRL_SELECT_PRECEDE_POS)
#define Debug_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << Debug_SPI_CTRL_CPHA_POS)
#define Debug_SPI_CTRL_CPHA                  ((uint32) 0x01u << Debug_SPI_CTRL_CPHA_POS)
#define Debug_SPI_CTRL_CPOL                  ((uint32) 0x01u << Debug_SPI_CTRL_CPOL_POS)
#define Debug_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    Debug_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << Debug_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define Debug_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << Debug_SPI_CTRL_SSEL0_POLARITY_POS)
    #define Debug_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << Debug_SPI_CTRL_SSEL1_POLARITY_POS)
    #define Debug_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << Debug_SPI_CTRL_SSEL2_POLARITY_POS)
    #define Debug_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << Debug_SPI_CTRL_SSEL3_POLARITY_POS)
    #define Debug_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << Debug_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#define Debug_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << Debug_SPI_CTRL_LOOPBACK_POS)
#define Debug_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << Debug_SPI_CTRL_MODE_POS)
#define Debug_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define Debug_SPI_CTRL_MODE_TI               ((uint32) 0x01u << Debug_CTRL_MODE_POS)
#define Debug_SPI_CTRL_MODE_NS               ((uint32) 0x02u << Debug_CTRL_MODE_POS)
#define Debug_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << Debug_SPI_CTRL_SLAVE_SELECT_POS)
#define Debug_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define Debug_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << Debug_SPI_CTRL_SLAVE_SELECT_POS)
#define Debug_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << Debug_SPI_CTRL_SLAVE_SELECT_POS)
#define Debug_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << Debug_SPI_CTRL_SLAVE_SELECT_POS)
#define Debug_SPI_CTRL_MASTER                ((uint32) 0x01u << Debug_SPI_CTRL_MASTER_MODE_POS)
#define Debug_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* Debug_SPI_STATUS_REG  */
#define Debug_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define Debug_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define Debug_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define Debug_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << Debug_I2C_STATUS_EZBUF_ADDR_POS)

/* Debug_UART_CTRL */
#define Debug_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define Debug_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define Debug_UART_CTRL_LOOPBACK             ((uint32) 0x01u << Debug_UART_CTRL_LOOPBACK_POS)
#define Debug_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define Debug_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << Debug_UART_CTRL_MODE_POS)
#define Debug_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << Debug_UART_CTRL_MODE_POS)
#define Debug_UART_CTRL_MODE_MASK            ((uint32) 0x03u << Debug_UART_CTRL_MODE_POS)

/* Debug_UART_TX_CTRL */
#define Debug_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define Debug_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define Debug_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define Debug_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define Debug_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define Debug_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define Debug_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define Debug_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define Debug_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    Debug_UART_TX_CTRL_PARITY_POS)
#define Debug_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    Debug_UART_TX_CTRL_PARITY_ENABLED_POS)
#define Debug_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    Debug_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* Debug_UART_RX_CTRL */
#define Debug_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define Debug_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define Debug_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define Debug_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define Debug_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define Debug_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define Debug_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define Debug_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define Debug_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define Debug_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define Debug_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define Debug_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define Debug_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define Debug_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define Debug_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_PARITY_POS)
#define Debug_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_PARITY_ENABLED_POS)
#define Debug_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_POLARITY_POS)
#define Debug_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   Debug_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define Debug_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define Debug_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_MP_MODE_POS)
#define Debug_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_LIN_MODE_POS)
#define Debug_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    Debug_UART_RX_CTRL_SKIP_START_POS)
#define Debug_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    Debug_UART_RX_CTRL_BREAK_WIDTH_POS)
/* Debug_UART_RX_STATUS_REG */
#define Debug_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define Debug_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    /* Debug_UART_FLOW_CTRL_REG */
    #define Debug_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define Debug_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define Debug_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define Debug_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define Debug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) Debug_FF_DATA_NR_LOG2_MASK)
    #define Debug_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       Debug_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define Debug_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       Debug_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define Debug_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       Debug_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

/* Debug_I2C_CTRL */
#define Debug_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define Debug_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define Debug_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define Debug_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define Debug_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define Debug_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define Debug_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define Debug_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define Debug_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define Debug_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define Debug_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define Debug_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define Debug_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define Debug_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                Debug_I2C_CTRL_LOW_PHASE_OVS_POS)
#define Debug_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_M_READY_DATA_ACK_POS)
#define Debug_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define Debug_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define Debug_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define Debug_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_S_READY_DATA_ACK_POS)
#define Debug_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define Debug_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define Debug_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_LOOPBACK_POS)
#define Debug_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_SLAVE_MODE_POS)
#define Debug_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                Debug_I2C_CTRL_MASTER_MODE_POS)
#define Debug_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                Debug_I2C_CTRL_SLAVE_MODE_POS)

/* Debug_I2C_STATUS_REG  */
#define Debug_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define Debug_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define Debug_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define Debug_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define Debug_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define Debug_I2C_STATUS_S_READ          ((uint32) 0x01u << Debug_I2C_STATUS_S_READ_POS)
#define Debug_I2C_STATUS_M_READ          ((uint32) 0x01u << Debug_I2C_STATUS_M_READ_POS)
#define Debug_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << Debug_I2C_STATUS_EZBUF_ADDR_POS)

/* Debug_I2C_MASTER_CMD_REG */
#define Debug_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define Debug_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define Debug_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define Debug_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define Debug_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define Debug_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define Debug_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   Debug_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define Debug_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   Debug_I2C_MASTER_CMD_M_ACK_POS)
#define Debug_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    Debug_I2C_MASTER_CMD_M_NACK_POS)
#define Debug_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    Debug_I2C_MASTER_CMD_M_STOP_POS)

/* Debug_I2C_SLAVE_CMD_REG  */
#define Debug_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define Debug_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define Debug_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define Debug_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << Debug_I2C_SLAVE_CMD_S_NACK_POS)

#define Debug_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define Debug_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define Debug_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define Debug_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << Debug_I2C_SLAVE_CMD_S_NACK_POS)

/* Debug_I2C_CFG_REG */
#if (Debug_CY_SCBIP_V0)
#define Debug_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define Debug_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define Debug_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define Debug_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define Debug_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define Debug_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define Debug_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define Debug_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define Debug_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define Debug_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define Debug_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define Debug_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define Debug_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define Debug_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                Debug_I2C_CFG_SDA_FILT_TRIM_POS)
#define Debug_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                Debug_I2C_CFG_SCL_FILT_HYS_POS)
#define Debug_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                Debug_I2C_CFG_SCL_FILT_TRIM_POS)
#define Debug_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                Debug_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define Debug_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                Debug_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define Debug_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SDA_FILT_HS_POS)
#define Debug_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SDA_FILT_ENABLED_POS)
#define Debug_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SCL_FILT_HS_POS)
#define Debug_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SCL_FILT_ENABLED_POS)
#define Debug_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define Debug_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                Debug_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define Debug_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define Debug_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define Debug_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define Debug_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define Debug_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define Debug_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define Debug_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define Debug_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define Debug_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define Debug_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << Debug_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define Debug_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            Debug_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define Debug_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << Debug_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define Debug_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            Debug_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define Debug_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            Debug_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define Debug_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            Debug_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define Debug_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            Debug_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (Debug_CY_SCBIP_V0) */


/* Debug_TX_CTRL_REG */
#define Debug_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define Debug_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define Debug_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define Debug_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define Debug_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << Debug_TX_CTRL_MSB_FIRST_POS)
#define Debug_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define Debug_TX_CTRL_ENABLED            ((uint32) 0x01u << Debug_TX_CTRL_ENABLED_POS)

/* Debug_TX_CTRL_FIFO_REG */
#define Debug_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define Debug_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define Debug_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define Debug_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) Debug_FF_DATA_NR_LOG2_MASK)
#define Debug_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << Debug_TX_FIFO_CTRL_CLEAR_POS)
#define Debug_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << Debug_TX_FIFO_CTRL_FREEZE_POS)

/* Debug_TX_FIFO_STATUS_REG */
#define Debug_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define Debug_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define Debug_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define Debug_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define Debug_TX_FIFO_STATUS_USED_MASK   ((uint32) Debug_FF_DATA_NR_LOG2_PLUS1_MASK)
#define Debug_TX_FIFO_SR_VALID           ((uint32) 0x01u << Debug_TX_FIFO_SR_VALID_POS)
#define Debug_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) Debug_FF_DATA_NR_LOG2_MASK << \
                                                                    Debug_TX_FIFO_STATUS_RD_PTR_POS)
#define Debug_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) Debug_FF_DATA_NR_LOG2_MASK << \
                                                                    Debug_TX_FIFO_STATUS_WR_PTR_POS)

/* Debug_TX_FIFO_WR_REG */
#define Debug_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define Debug_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* Debug_RX_CTRL_REG */
#define Debug_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define Debug_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define Debug_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define Debug_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define Debug_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define Debug_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << Debug_RX_CTRL_MSB_FIRST_POS)
#define Debug_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define Debug_RX_CTRL_MEDIAN             ((uint32) 0x01u << Debug_RX_CTRL_MEDIAN_POS)
#define Debug_RX_CTRL_ENABLED            ((uint32) 0x01u << Debug_RX_CTRL_ENABLED_POS)


/* Debug_RX_FIFO_CTRL_REG */
#define Debug_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define Debug_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define Debug_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define Debug_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) Debug_FF_DATA_NR_LOG2_MASK)
#define Debug_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << Debug_RX_FIFO_CTRL_CLEAR_POS)
#define Debug_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << Debug_RX_FIFO_CTRL_FREEZE_POS)

/* Debug_RX_FIFO_STATUS_REG */
#define Debug_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define Debug_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define Debug_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define Debug_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define Debug_RX_FIFO_STATUS_USED_MASK   ((uint32) Debug_FF_DATA_NR_LOG2_PLUS1_MASK)
#define Debug_RX_FIFO_SR_VALID           ((uint32) 0x01u << Debug_RX_FIFO_SR_VALID_POS)
#define Debug_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) Debug_FF_DATA_NR_LOG2_MASK << \
                                                                    Debug_RX_FIFO_STATUS_RD_PTR_POS)
#define Debug_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) Debug_FF_DATA_NR_LOG2_MASK << \
                                                                    Debug_RX_FIFO_STATUS_WR_PTR_POS)

/* Debug_RX_MATCH_REG */
#define Debug_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define Debug_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define Debug_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define Debug_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << Debug_RX_MATCH_MASK_POS)

/* Debug_RX_FIFO_WR_REG */
#define Debug_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define Debug_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* Debug_RX_FIFO_RD_SILENT_REG */
#define Debug_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define Debug_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* Debug_RX_FIFO_RD_SILENT_REG */
#define Debug_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define Debug_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* Debug_EZBUF_DATA_REG */
#define Debug_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define Debug_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  Debug_INTR_CAUSE_REG */
#define Debug_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define Debug_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define Debug_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define Debug_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define Debug_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define Debug_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define Debug_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define Debug_INTR_CAUSE_SLAVE       ((uint32) 0x01u << Debug_INTR_CAUSE_SLAVE_POS)
#define Debug_INTR_CAUSE_TX          ((uint32) 0x01u << Debug_INTR_CAUSE_TX_POS)
#define Debug_INTR_CAUSE_RX          ((uint32) 0x01u << Debug_INTR_CAUSE_RX_POS)
#define Debug_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << Debug_INTR_CAUSE_I2C_EC_POS)
#define Debug_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << Debug_INTR_CAUSE_SPI_EC_POS)

/* Debug_INTR_SPI_EC_REG, Debug_INTR_SPI_EC_MASK_REG, Debug_INTR_SPI_EC_MASKED_REG */
#define Debug_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define Debug_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define Debug_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define Debug_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define Debug_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    Debug_INTR_SPI_EC_EZBUF_STOP_POS)
#define Debug_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    Debug_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* Debug_INTR_I2C_EC, Debug_INTR_I2C_EC_MASK, Debug_INTR_I2C_EC_MASKED */
#define Debug_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define Debug_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define Debug_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define Debug_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define Debug_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    Debug_INTR_I2C_EC_EZBUF_STOP_POS)
#define Debug_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    Debug_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* Debug_INTR_MASTER, Debug_INTR_MASTER_SET,
   Debug_INTR_MASTER_MASK, Debug_INTR_MASTER_MASKED */
#define Debug_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define Debug_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define Debug_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define Debug_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define Debug_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define Debug_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define Debug_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define Debug_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << Debug_INTR_MASTER_I2C_NACK_POS)
#define Debug_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << Debug_INTR_MASTER_I2C_ACK_POS)
#define Debug_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << Debug_INTR_MASTER_I2C_STOP_POS)
#define Debug_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    Debug_INTR_MASTER_I2C_BUS_ERROR_POS)
#define Debug_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << Debug_INTR_MASTER_SPI_DONE_POS)

/*
* Debug_INTR_SLAVE, Debug_INTR_SLAVE_SET,
* Debug_INTR_SLAVE_MASK, Debug_INTR_SLAVE_MASKED
*/
#define Debug_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define Debug_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define Debug_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define Debug_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define Debug_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define Debug_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define Debug_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define Debug_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define Debug_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define Debug_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define Debug_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define Debug_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define Debug_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define Debug_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_NACK_POS)
#define Debug_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_ACK_POS)
#define Debug_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define Debug_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_STOP_POS)
#define Debug_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_START_POS)
#define Debug_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define Debug_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_GENERAL_POS)
#define Debug_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define Debug_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   Debug_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define Debug_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define Debug_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    Debug_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* Debug_INTR_TX, Debug_INTR_TX_SET,
* Debug_INTR_TX_MASK, Debug_INTR_TX_MASKED
*/
#define Debug_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define Debug_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define Debug_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define Debug_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define Debug_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define Debug_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define Debug_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define Debug_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define Debug_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define Debug_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define Debug_INTR_TX_FIFO_LEVEL         (Debug_INTR_TX_TRIGGER)
#define Debug_INTR_TX_NOT_FULL           ((uint32) 0x01u << Debug_INTR_TX_NOT_FULL_POS)
#define Debug_INTR_TX_EMPTY              ((uint32) 0x01u << Debug_INTR_TX_EMPTY_POS)
#define Debug_INTR_TX_OVERFLOW           ((uint32) 0x01u << Debug_INTR_TX_OVERFLOW_POS)
#define Debug_INTR_TX_UNDERFLOW          ((uint32) 0x01u << Debug_INTR_TX_UNDERFLOW_POS)
#define Debug_INTR_TX_BLOCKED            ((uint32) 0x01u << Debug_INTR_TX_BLOCKED_POS)
#define Debug_INTR_TX_UART_NACK          ((uint32) 0x01u << Debug_INTR_TX_UART_NACK_POS)
#define Debug_INTR_TX_UART_DONE          ((uint32) 0x01u << Debug_INTR_TX_UART_DONE_POS)
#define Debug_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << Debug_INTR_TX_UART_ARB_LOST_POS)

/*
* Debug_INTR_RX, Debug_INTR_RX_SET,
* Debug_INTR_RX_MASK, Debug_INTR_RX_MASKED
*/
#define Debug_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define Debug_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define Debug_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define Debug_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define Debug_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define Debug_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define Debug_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define Debug_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define Debug_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define Debug_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define Debug_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define Debug_INTR_RX_FIFO_LEVEL         (Debug_INTR_RX_TRIGGER)
#define Debug_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << Debug_INTR_RX_NOT_EMPTY_POS)
#define Debug_INTR_RX_FULL               ((uint32) 0x01u << Debug_INTR_RX_FULL_POS)
#define Debug_INTR_RX_OVERFLOW           ((uint32) 0x01u << Debug_INTR_RX_OVERFLOW_POS)
#define Debug_INTR_RX_UNDERFLOW          ((uint32) 0x01u << Debug_INTR_RX_UNDERFLOW_POS)
#define Debug_INTR_RX_BLOCKED            ((uint32) 0x01u << Debug_INTR_RX_BLOCKED_POS)
#define Debug_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << Debug_INTR_RX_FRAME_ERROR_POS)
#define Debug_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << Debug_INTR_RX_PARITY_ERROR_POS)
#define Debug_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << Debug_INTR_RX_BAUD_DETECT_POS)
#define Debug_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << Debug_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define Debug_INTR_I2C_EC_ALL    (Debug_INTR_I2C_EC_WAKE_UP    | \
                                             Debug_INTR_I2C_EC_EZBUF_STOP | \
                                             Debug_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define Debug_INTR_SPI_EC_ALL    (Debug_INTR_SPI_EC_WAKE_UP    | \
                                             Debug_INTR_SPI_EC_EZBUF_STOP | \
                                             Debug_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define Debug_INTR_MASTER_ALL    (Debug_INTR_MASTER_I2C_ARB_LOST  | \
                                             Debug_INTR_MASTER_I2C_NACK      | \
                                             Debug_INTR_MASTER_I2C_ACK       | \
                                             Debug_INTR_MASTER_I2C_STOP      | \
                                             Debug_INTR_MASTER_I2C_BUS_ERROR | \
                                             Debug_INTR_MASTER_SPI_DONE)

#define Debug_INTR_SLAVE_ALL     (Debug_INTR_SLAVE_I2C_ARB_LOST      | \
                                             Debug_INTR_SLAVE_I2C_NACK          | \
                                             Debug_INTR_SLAVE_I2C_ACK           | \
                                             Debug_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             Debug_INTR_SLAVE_I2C_STOP          | \
                                             Debug_INTR_SLAVE_I2C_START         | \
                                             Debug_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             Debug_INTR_SLAVE_I2C_GENERAL       | \
                                             Debug_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             Debug_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             Debug_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             Debug_INTR_SLAVE_SPI_BUS_ERROR)

#define Debug_INTR_TX_ALL        (Debug_INTR_TX_TRIGGER   | \
                                             Debug_INTR_TX_NOT_FULL  | \
                                             Debug_INTR_TX_EMPTY     | \
                                             Debug_INTR_TX_OVERFLOW  | \
                                             Debug_INTR_TX_UNDERFLOW | \
                                             Debug_INTR_TX_BLOCKED   | \
                                             Debug_INTR_TX_UART_NACK | \
                                             Debug_INTR_TX_UART_DONE | \
                                             Debug_INTR_TX_UART_ARB_LOST)

#define Debug_INTR_RX_ALL        (Debug_INTR_RX_TRIGGER      | \
                                             Debug_INTR_RX_NOT_EMPTY    | \
                                             Debug_INTR_RX_FULL         | \
                                             Debug_INTR_RX_OVERFLOW     | \
                                             Debug_INTR_RX_UNDERFLOW    | \
                                             Debug_INTR_RX_BLOCKED      | \
                                             Debug_INTR_RX_FRAME_ERROR  | \
                                             Debug_INTR_RX_PARITY_ERROR | \
                                             Debug_INTR_RX_BAUD_DETECT  | \
                                             Debug_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define Debug_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define Debug_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define Debug_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define Debug_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define Debug_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define Debug_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define Debug_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define Debug_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define Debug_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define Debug_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define Debug_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define Debug_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define Debug_CTRL_OVS_IRDA_OVS16        (Debug_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define Debug_SCB_SW_RESET \
                        do{           \
                            Debug_CTRL_REG &= ((uint32) ~Debug_CTRL_ENABLED); \
                            Debug_CTRL_REG |= ((uint32)  Debug_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define Debug_CLEAR_TX_FIFO \
                            do{        \
                                Debug_TX_FIFO_CTRL_REG |= ((uint32)  Debug_TX_FIFO_CTRL_CLEAR); \
                                Debug_TX_FIFO_CTRL_REG &= ((uint32) ~Debug_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define Debug_GET_TX_FIFO_ENTRIES    (Debug_TX_FIFO_STATUS_REG & \
                                                 Debug_TX_FIFO_STATUS_USED_MASK)

#define Debug_GET_TX_FIFO_SR_VALID   ((0u != (Debug_TX_FIFO_STATUS_REG & \
                                                         Debug_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define Debug_CLEAR_RX_FIFO \
                            do{        \
                                Debug_RX_FIFO_CTRL_REG |= ((uint32)  Debug_RX_FIFO_CTRL_CLEAR); \
                                Debug_RX_FIFO_CTRL_REG &= ((uint32) ~Debug_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define Debug_GET_RX_FIFO_ENTRIES    (Debug_RX_FIFO_STATUS_REG & \
                                                    Debug_RX_FIFO_STATUS_USED_MASK)

#define Debug_GET_RX_FIFO_SR_VALID   ((0u != (Debug_RX_FIFO_STATUS_REG & \
                                                         Debug_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in Debug_INTR_X_MASK_REG */
#define Debug_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    Debug_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!Debug_CY_SCBIP_V1)
    #define Debug_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    Debug_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    Debug_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    Debug_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    Debug_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    Debug_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in Debug_INTR_X_MASK_REG */
#define Debug_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    Debug_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!Debug_CY_SCBIP_V1)
    #define Debug_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    Debug_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    Debug_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define Debug_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    Debug_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define Debug_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    Debug_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define Debug_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    Debug_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in Debug_INTR_X_MASK_REG */
#define Debug_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    Debug_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!Debug_CY_SCBIP_V1)
    #define Debug_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    Debug_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                Debug_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define Debug_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    Debug_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define Debug_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    Debug_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define Debug_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    Debug_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in Debug_INTR_X_SET_REG */
#define Debug_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    Debug_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    Debug_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    Debug_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    Debug_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in Debug_INTR_X_REG */
#define Debug_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    Debug_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!Debug_CY_SCBIP_V1)
    #define Debug_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    Debug_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    Debug_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    Debug_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    Debug_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define Debug_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    Debug_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in Debug_INTR_CAUSE_REG */
#define Debug_CHECK_CAUSE_INTR(sourceMask)    (0u != (Debug_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define Debug_CHECK_INTR_I2C_EC(sourceMask)  (0u != (Debug_INTR_I2C_EC_REG & (sourceMask)))
#if (!Debug_CY_SCBIP_V1)
    #define Debug_CHECK_INTR_SPI_EC(sourceMask)  (0u != (Debug_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!Debug_CY_SCBIP_V1) */
#define Debug_CHECK_INTR_MASTER(sourceMask)  (0u != (Debug_INTR_MASTER_REG & (sourceMask)))
#define Debug_CHECK_INTR_SLAVE(sourceMask)   (0u != (Debug_INTR_SLAVE_REG  & (sourceMask)))
#define Debug_CHECK_INTR_TX(sourceMask)      (0u != (Debug_INTR_TX_REG     & (sourceMask)))
#define Debug_CHECK_INTR_RX(sourceMask)      (0u != (Debug_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in Debug_INTR_X_MASKED_REG */
#define Debug_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (Debug_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!Debug_CY_SCBIP_V1)
    #define Debug_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (Debug_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!Debug_CY_SCBIP_V1) */
#define Debug_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (Debug_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define Debug_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (Debug_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define Debug_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (Debug_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define Debug_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (Debug_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in Debug_CTRL_REG: generally is used to check enable bit */
#define Debug_GET_CTRL_ENABLED    (0u != (Debug_CTRL_REG & Debug_CTRL_ENABLED))

#define Debug_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (Debug_I2C_CTRL_REG & \
                                                                Debug_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define Debug_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                Debug_I2C_CTRL_REG |= Debug_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define Debug_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                Debug_I2C_CTRL_REG |= Debug_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define Debug_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                Debug_I2C_CTRL_REG |= Debug_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define Debug_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                Debug_I2C_CTRL_REG |= Debug_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define Debug_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                Debug_I2C_CTRL_REG |= Debug_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define Debug_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                Debug_I2C_CTRL_REG &= ~Debug_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define Debug_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                Debug_I2C_CTRL_REG &= ~Debug_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define Debug_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                Debug_I2C_CTRL_REG &= ~Debug_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define Debug_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                Debug_I2C_CTRL_REG &= ~Debug_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define Debug_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                Debug_I2C_CTRL_REG &= ~Debug_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define Debug_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                Debug_I2C_CTRL_REG |= (Debug_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  Debug_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define Debug_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                Debug_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(Debug_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    Debug_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define Debug_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                Debug_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(Debug_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    Debug_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define Debug_I2C_MASTER_GENERATE_START \
                            do{                    \
                                Debug_I2C_MASTER_CMD_REG = Debug_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define Debug_I2C_MASTER_CLEAR_START \
                            do{                 \
                                Debug_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define Debug_I2C_MASTER_GENERATE_RESTART Debug_I2CReStartGeneration()

#define Debug_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                Debug_I2C_MASTER_CMD_REG =                                            \
                                    (Debug_I2C_MASTER_CMD_M_STOP |                                    \
                                        (Debug_CHECK_I2C_STATUS(Debug_I2C_STATUS_M_READ) ? \
                                            (Debug_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define Debug_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                Debug_I2C_MASTER_CMD_REG = Debug_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define Debug_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                Debug_I2C_MASTER_CMD_REG = Debug_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define Debug_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                Debug_I2C_SLAVE_CMD_REG = Debug_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void Debug_I2CSlaveNackGeneration(void);
    #define Debug_I2C_SLAVE_GENERATE_NACK Debug_I2CSlaveNackGeneration()

#else
    #define Debug_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                Debug_I2C_SLAVE_CMD_REG = Debug_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#define Debug_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                Debug_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define Debug_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    Debug_I2C_SLAVE_ADDR_POS)) & \
                                                                        Debug_I2C_SLAVE_ADDR_MASK)

#define Debug_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> Debug_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define Debug_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define Debug_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (Debug_CY_SCBIP_V0)
    #define Debug_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            Debug_I2C_CFG_REG =                  \
                            ((Debug_I2C_CFG_REG & (uint32) ~Debug_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<Debug_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (Debug_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define Debug_DIGITAL_FILTER_DISABLE    (0u)
#define Debug_DIGITAL_FILTER_ENABLE     (1u)
#define Debug_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (Debug_CY_SCBIP_V0)
    /* Debug_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define Debug_I2C_CFG_FILT_MASK  (Debug_I2C_CFG_SDA_FILT_ENABLED | \
                                                 Debug_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* Debug_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define Debug_I2C_CFG_FILT_MASK  (Debug_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 Debug_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (Debug_CY_SCBIP_V0) */

#define Debug_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            Debug_I2C_CFG_REG &= (uint32) ~Debug_I2C_CFG_FILT_MASK; \
        }while(0)

#define Debug_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            Debug_I2C_CFG_REG |= (uint32)  Debug_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define Debug_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    Debug_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        Debug_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in Debug_I2C_STATUS_REG */
#define Debug_CHECK_I2C_STATUS(sourceMask)   (0u != (Debug_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in Debug_SPI_STATUS_REG */
#define Debug_CHECK_SPI_STATUS(sourceMask)   (0u != (Debug_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on Debug_CTRL_BYTE_MODE bit */
#define Debug_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * Debug_FIFO_SIZE) : (Debug_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* Debug_CTRL */
#define Debug_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & Debug_CTRL_OVS_MASK)

#define Debug_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (Debug_CTRL_EC_OP_MODE)  : (0u))

#define Debug_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (Debug_CTRL_EC_AM_MODE)  : (0u))

#define Debug_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (Debug_CTRL_BLOCK)       : (0u))

#define Debug_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (Debug_CTRL_ADDR_ACCEPT) : (0u))

#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define Debug_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (Debug_CTRL_BYTE_MODE) : (0u))
#endif /* (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

/* Debug_I2C_CTRL */
#define Debug_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        Debug_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define Debug_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    Debug_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    Debug_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define Debug_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (Debug_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define Debug_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (Debug_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define Debug_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << Debug_I2C_CTRL_SLAVE_MODE_POS)

/* Debug_SPI_CTRL */
#define Debug_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (Debug_SPI_CTRL_CONTINUOUS) : (0u))

#define Debug_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (Debug_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define Debug_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        Debug_SPI_CTRL_CPHA_POS) & \
                                                                        Debug_SPI_CTRL_SCLK_MODE_MASK)

#define Debug_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (Debug_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define Debug_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define Debug_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (Debug_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define Debug_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     Debug_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     Debug_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

#define Debug_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << Debug_SPI_CTRL_MODE_POS) & \
                                                                                 Debug_SPI_CTRL_MODE_MASK)

#define Debug_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      Debug_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      Debug_SPI_CTRL_SLAVE_SELECT_MASK)

#define Debug_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (Debug_SPI_CTRL_MASTER) : (0u))

/* Debug_UART_CTRL */
#define Debug_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            Debug_UART_CTRL_MODE_POS) & \
                                                                            Debug_UART_CTRL_MODE_MASK)

/* Debug_UART_RX_CTRL */
#define Debug_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        Debug_UART_RX_CTRL_STOP_BITS_MASK)

#define Debug_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (Debug_UART_RX_CTRL_PARITY) : (0u))

#define Debug_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (Debug_UART_RX_CTRL_POLARITY) : (0u))

#define Debug_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (Debug_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define Debug_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (Debug_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define Debug_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (Debug_UART_RX_CTRL_MP_MODE) : (0u))

/* Debug_UART_TX_CTRL */
#define Debug_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                Debug_UART_RX_CTRL_STOP_BITS_MASK)

#define Debug_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (Debug_UART_TX_CTRL_PARITY) : (0u))

#define Debug_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (Debug_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* Debug_UART_FLOW_CTRL */
#if !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
    #define Debug_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 Debug_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define Debug_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (Debug_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define Debug_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (Debug_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define Debug_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (Debug_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

/* Debug_RX_CTRL */
#define Debug_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                Debug_RX_CTRL_DATA_WIDTH_MASK)

#define Debug_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (Debug_RX_CTRL_MSB_FIRST) : (0u))

#define Debug_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (Debug_RX_CTRL_MEDIAN) : (0u))

/* Debug_RX_MATCH */
#define Debug_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & Debug_RX_MATCH_ADDR_MASK)
#define Debug_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            Debug_RX_MATCH_MASK_POS) & \
                                                            Debug_RX_MATCH_MASK_MASK)

/* Debug_RX_FIFO_CTRL */
#define Debug_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    Debug_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Debug_TX_CTRL */
#define Debug_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                Debug_RX_CTRL_DATA_WIDTH_MASK)

#define Debug_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (Debug_TX_CTRL_MSB_FIRST) : (0u))

/* Debug_TX_FIFO_CTRL */
#define Debug_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    Debug_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* Debug_INTR_SLAVE_I2C_GENERAL */
#define Debug_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (Debug_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled Debug_SPI_CTRL_REG */
#define Debug_CHECK_SPI_MASTER   (0u != (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define Debug_GET_SPI_SCLK_INACTIVE \
            ((0u == (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1)
#define Debug_GET_SPI_SS0_INACTIVE       (1u)
#define Debug_GET_SPI_SS1_INACTIVE       (1u)
#define Debug_GET_SPI_SS2_INACTIVE       (1u)
#define Debug_GET_SPI_SS3_INACTIVE       (1u)
#define Debug_GET_UART_RTS_INACTIVE      (1u)

#else
#define Debug_GET_SPI_SS0_INACTIVE  \
        ((0u != (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define Debug_GET_SPI_SS1_INACTIVE  \
        ((0u != (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define Debug_GET_SPI_SS2_INACTIVE  \
        ((0u != (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define Debug_GET_SPI_SS3_INACTIVE  \
        ((0u != (Debug_SPI_CTRL_REG & Debug_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define Debug_GET_UART_RTS_INACTIVE \
        ((0u == (Debug_UART_FLOW_CTRL_REG & Debug_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(Debug_CY_SCBIP_V0 || Debug_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define Debug_CLEAR_REG          ((uint32) (0u))
#define Debug_NO_INTR_SOURCES    ((uint32) (0u))
#define Debug_DUMMY_PARAM        ((uint32) (0u))
#define Debug_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define Debug_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define Debug_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define Debug_CHECK_INTR_EC_I2C(sourceMask)  Debug_CHECK_INTR_I2C_EC(sourceMask)
#if (!Debug_CY_SCBIP_V1)
    #define Debug_CHECK_INTR_EC_SPI(sourceMask)  Debug_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!Debug_CY_SCBIP_V1) */

#define Debug_CY_SCBIP_V1_I2C_ONLY   (Debug_CY_SCBIP_V1)

#endif /* (CY_SCB_Debug_H) */


/* [] END OF FILE */
