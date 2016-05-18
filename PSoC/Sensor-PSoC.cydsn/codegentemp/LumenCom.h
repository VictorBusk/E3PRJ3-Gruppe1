/*******************************************************************************
* File Name: LumenCom.h
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

#if !defined(CY_SCB_LumenCom_H)
#define CY_SCB_LumenCom_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define LumenCom_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define LumenCom_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define LumenCom_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

#define LumenCom_SCB_MODE                     (1u)

/* SCB modes enum */
#define LumenCom_SCB_MODE_I2C                 (0x01u)
#define LumenCom_SCB_MODE_SPI                 (0x02u)
#define LumenCom_SCB_MODE_UART                (0x04u)
#define LumenCom_SCB_MODE_EZI2C               (0x08u)
#define LumenCom_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define LumenCom_SCB_MODE_I2C_CONST_CFG       (LumenCom_SCB_MODE_I2C       == LumenCom_SCB_MODE)
#define LumenCom_SCB_MODE_SPI_CONST_CFG       (LumenCom_SCB_MODE_SPI       == LumenCom_SCB_MODE)
#define LumenCom_SCB_MODE_UART_CONST_CFG      (LumenCom_SCB_MODE_UART      == LumenCom_SCB_MODE)
#define LumenCom_SCB_MODE_EZI2C_CONST_CFG     (LumenCom_SCB_MODE_EZI2C     == LumenCom_SCB_MODE)
#define LumenCom_SCB_MODE_UNCONFIG_CONST_CFG  (LumenCom_SCB_MODE_UNCONFIG  == LumenCom_SCB_MODE)

/* Condition compilation for includes */
#define LumenCom_SCB_MODE_I2C_INC      (0u !=(LumenCom_SCB_MODE_I2C   & LumenCom_SCB_MODE))
#define LumenCom_SCB_MODE_EZI2C_INC    (0u !=(LumenCom_SCB_MODE_EZI2C & LumenCom_SCB_MODE))
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_SCB_MODE_SPI_INC  (0u !=(LumenCom_SCB_MODE_SPI   & LumenCom_SCB_MODE))
    #define LumenCom_SCB_MODE_UART_INC (0u !=(LumenCom_SCB_MODE_UART  & LumenCom_SCB_MODE))
#else
    #define LumenCom_SCB_MODE_SPI_INC  (0u)
    #define LumenCom_SCB_MODE_UART_INC (0u)
#endif /* (!LumenCom_CY_SCBIP_V1) */

/* Interrupts remove options */
#define LumenCom_REMOVE_SCB_IRQ             (0u)
#define LumenCom_SCB_IRQ_INTERNAL           (0u == LumenCom_REMOVE_SCB_IRQ)

#define LumenCom_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define LumenCom_UART_RX_WAKEUP_IRQ         (0u == LumenCom_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define LumenCom_SCB_INTR_MODE_NONE     (0u)
#define LumenCom_SCB_INTR_MODE_INTERNAL (1u)
#define LumenCom_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define LumenCom_REMOVE_SCB_CLK     (0u)
#define LumenCom_SCB_CLK_INTERNAL   (0u == LumenCom_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "LumenCom_PINS.h"

#if (LumenCom_SCB_CLK_INTERNAL)
    #include "LumenCom_SCBCLK.h"
#endif /* (LumenCom_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} LumenCom_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void LumenCom_Init(void);
void LumenCom_Enable(void);
void LumenCom_Start(void);
void LumenCom_Stop(void);

/* Sleep and Wakeup APis */
void LumenCom_Sleep(void);
void LumenCom_Wakeup(void);

#if (LumenCom_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void LumenCom_SetCustomInterruptHandler(void (*func)(void));
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */

/* Interface to internal interrupt component */
#if (LumenCom_SCB_IRQ_INTERNAL)
    #define LumenCom_EnableInt()        CyIntEnable      (LumenCom_ISR_NUMBER)
    #define LumenCom_DisableInt()       CyIntDisable     (LumenCom_ISR_NUMBER)
    #define LumenCom_ClearPendingInt()  CyIntClearPending(LumenCom_ISR_NUMBER)
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */

#if (LumenCom_UART_RX_WAKEUP_IRQ)
    #define LumenCom_RxWakeEnableInt()        CyIntEnable      (LumenCom_RX_WAKE_ISR_NUMBER)
    #define LumenCom_RxWakeDisableInt()       CyIntDisable     (LumenCom_RX_WAKE_ISR_NUMBER)
    #define LumenCom_RxWakeClearPendingInt()  CyIntClearPending(LumenCom_RX_WAKE_ISR_NUMBER)
#endif /* (LumenCom_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define LumenCom_GetInterruptCause()    (LumenCom_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define LumenCom_SetRxInterruptMode(interruptMask)     LumenCom_WRITE_INTR_RX_MASK(interruptMask)
#define LumenCom_ClearRxInterruptSource(interruptMask) LumenCom_CLEAR_INTR_RX(interruptMask)
#define LumenCom_SetRxInterrupt(interruptMask)         LumenCom_SET_INTR_RX(interruptMask)
#define LumenCom_GetRxInterruptSource()                (LumenCom_INTR_RX_REG)
#define LumenCom_GetRxInterruptMode()                  (LumenCom_INTR_RX_MASK_REG)
#define LumenCom_GetRxInterruptSourceMasked()          (LumenCom_INTR_RX_MASKED_REG)
void LumenCom_SetRxFifoLevel(uint32 level);

/* APIs to service INTR_TX register */
#define LumenCom_SetTxInterruptMode(interruptMask)     LumenCom_WRITE_INTR_TX_MASK(interruptMask)
#define LumenCom_ClearTxInterruptSource(interruptMask) LumenCom_CLEAR_INTR_TX(interruptMask)
#define LumenCom_SetTxInterrupt(interruptMask)         LumenCom_SET_INTR_TX(interruptMask)
#define LumenCom_GetTxInterruptSource()                (LumenCom_INTR_TX_REG)
#define LumenCom_GetTxInterruptMode()                  (LumenCom_INTR_TX_MASK_REG)
#define LumenCom_GetTxInterruptSourceMasked()          (LumenCom_INTR_TX_MASKED_REG)
void LumenCom_SetTxFifoLevel(uint32 level);

/* APIs to service INTR_MASTER register */
#define LumenCom_SetMasterInterruptMode(interruptMask)    LumenCom_WRITE_INTR_MASTER_MASK(interruptMask)
#define LumenCom_ClearMasterInterruptSource(interruptMask) LumenCom_CLEAR_INTR_MASTER(interruptMask)
#define LumenCom_SetMasterInterrupt(interruptMask)         LumenCom_SET_INTR_MASTER(interruptMask)
#define LumenCom_GetMasterInterruptSource()                (LumenCom_INTR_MASTER_REG)
#define LumenCom_GetMasterInterruptMode()                  (LumenCom_INTR_MASTER_MASK_REG)
#define LumenCom_GetMasterInterruptSourceMasked()          (LumenCom_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define LumenCom_SetSlaveInterruptMode(interruptMask)     LumenCom_WRITE_INTR_SLAVE_MASK(interruptMask)
#define LumenCom_ClearSlaveInterruptSource(interruptMask) LumenCom_CLEAR_INTR_SLAVE(interruptMask)
#define LumenCom_SetSlaveInterrupt(interruptMask)         LumenCom_SET_INTR_SLAVE(interruptMask)
#define LumenCom_GetSlaveInterruptSource()                (LumenCom_INTR_SLAVE_REG)
#define LumenCom_GetSlaveInterruptMode()                  (LumenCom_INTR_SLAVE_MASK_REG)
#define LumenCom_GetSlaveInterruptSourceMasked()          (LumenCom_INTR_SLAVE_MASKED_REG)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 LumenCom_initVar;


/***************************************
*              Registers
***************************************/

#define LumenCom_CTRL_REG               (*(reg32 *) LumenCom_SCB__CTRL)
#define LumenCom_CTRL_PTR               ( (reg32 *) LumenCom_SCB__CTRL)

#define LumenCom_STATUS_REG             (*(reg32 *) LumenCom_SCB__STATUS)
#define LumenCom_STATUS_PTR             ( (reg32 *) LumenCom_SCB__STATUS)

#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_SPI_CTRL_REG           (*(reg32 *) LumenCom_SCB__SPI_CTRL)
    #define LumenCom_SPI_CTRL_PTR           ( (reg32 *) LumenCom_SCB__SPI_CTRL)

    #define LumenCom_SPI_STATUS_REG         (*(reg32 *) LumenCom_SCB__SPI_STATUS)
    #define LumenCom_SPI_STATUS_PTR         ( (reg32 *) LumenCom_SCB__SPI_STATUS)

    #define LumenCom_UART_CTRL_REG          (*(reg32 *) LumenCom_SCB__UART_CTRL)
    #define LumenCom_UART_CTRL_PTR          ( (reg32 *) LumenCom_SCB__UART_CTRL)

    #define LumenCom_UART_TX_CTRL_REG       (*(reg32 *) LumenCom_SCB__UART_TX_CTRL)
    #define LumenCom_UART_TX_CTRL_PTR       ( (reg32 *) LumenCom_SCB__UART_TX_CTRL)

    #define LumenCom_UART_RX_CTRL_REG       (*(reg32 *) LumenCom_SCB__UART_RX_CTRL)
    #define LumenCom_UART_RX_CTRL_PTR       ( (reg32 *) LumenCom_SCB__UART_RX_CTRL)

    #define LumenCom_UART_RX_STATUS_REG     (*(reg32 *) LumenCom_SCB__UART_RX_STATUS)
    #define LumenCom_UART_RX_STATUS_PTR     ( (reg32 *) LumenCom_SCB__UART_RX_STATUS)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_UART_FLOW_CTRL_REG     (*(reg32 *) LumenCom_SCB__UART_FLOW_CTRL)
    #define LumenCom_UART_FLOW_CTRL_PTR     ( (reg32 *) LumenCom_SCB__UART_FLOW_CTRL)
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

#define LumenCom_I2C_CTRL_REG           (*(reg32 *) LumenCom_SCB__I2C_CTRL)
#define LumenCom_I2C_CTRL_PTR           ( (reg32 *) LumenCom_SCB__I2C_CTRL)

#define LumenCom_I2C_STATUS_REG         (*(reg32 *) LumenCom_SCB__I2C_STATUS)
#define LumenCom_I2C_STATUS_PTR         ( (reg32 *) LumenCom_SCB__I2C_STATUS)

#define LumenCom_I2C_MASTER_CMD_REG     (*(reg32 *) LumenCom_SCB__I2C_M_CMD)
#define LumenCom_I2C_MASTER_CMD_PTR     ( (reg32 *) LumenCom_SCB__I2C_M_CMD)

#define LumenCom_I2C_SLAVE_CMD_REG      (*(reg32 *) LumenCom_SCB__I2C_S_CMD)
#define LumenCom_I2C_SLAVE_CMD_PTR      ( (reg32 *) LumenCom_SCB__I2C_S_CMD)

#define LumenCom_I2C_CFG_REG            (*(reg32 *) LumenCom_SCB__I2C_CFG)
#define LumenCom_I2C_CFG_PTR            ( (reg32 *) LumenCom_SCB__I2C_CFG)

#define LumenCom_TX_CTRL_REG            (*(reg32 *) LumenCom_SCB__TX_CTRL)
#define LumenCom_TX_CTRL_PTR            ( (reg32 *) LumenCom_SCB__TX_CTRL)

#define LumenCom_TX_FIFO_CTRL_REG       (*(reg32 *) LumenCom_SCB__TX_FIFO_CTRL)
#define LumenCom_TX_FIFO_CTRL_PTR       ( (reg32 *) LumenCom_SCB__TX_FIFO_CTRL)

#define LumenCom_TX_FIFO_STATUS_REG     (*(reg32 *) LumenCom_SCB__TX_FIFO_STATUS)
#define LumenCom_TX_FIFO_STATUS_PTR     ( (reg32 *) LumenCom_SCB__TX_FIFO_STATUS)

#define LumenCom_TX_FIFO_WR_REG         (*(reg32 *) LumenCom_SCB__TX_FIFO_WR)
#define LumenCom_TX_FIFO_WR_PTR         ( (reg32 *) LumenCom_SCB__TX_FIFO_WR)

#define LumenCom_RX_CTRL_REG            (*(reg32 *) LumenCom_SCB__RX_CTRL)
#define LumenCom_RX_CTRL_PTR            ( (reg32 *) LumenCom_SCB__RX_CTRL)

#define LumenCom_RX_FIFO_CTRL_REG       (*(reg32 *) LumenCom_SCB__RX_FIFO_CTRL)
#define LumenCom_RX_FIFO_CTRL_PTR       ( (reg32 *) LumenCom_SCB__RX_FIFO_CTRL)

#define LumenCom_RX_FIFO_STATUS_REG     (*(reg32 *) LumenCom_SCB__RX_FIFO_STATUS)
#define LumenCom_RX_FIFO_STATUS_PTR     ( (reg32 *) LumenCom_SCB__RX_FIFO_STATUS)

#define LumenCom_RX_MATCH_REG           (*(reg32 *) LumenCom_SCB__RX_MATCH)
#define LumenCom_RX_MATCH_PTR           ( (reg32 *) LumenCom_SCB__RX_MATCH)

#define LumenCom_RX_FIFO_RD_REG         (*(reg32 *) LumenCom_SCB__RX_FIFO_RD)
#define LumenCom_RX_FIFO_RD_PTR         ( (reg32 *) LumenCom_SCB__RX_FIFO_RD)

#define LumenCom_RX_FIFO_RD_SILENT_REG  (*(reg32 *) LumenCom_SCB__RX_FIFO_RD_SILENT)
#define LumenCom_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) LumenCom_SCB__RX_FIFO_RD_SILENT)

#define LumenCom_EZBUF_DATA00_REG       (*(reg32 *) LumenCom_SCB__EZ_DATA00)
#define LumenCom_EZBUF_DATA00_PTR       ( (reg32 *) LumenCom_SCB__EZ_DATA00)

#define LumenCom_INTR_CAUSE_REG         (*(reg32 *) LumenCom_SCB__INTR_CAUSE)
#define LumenCom_INTR_CAUSE_PTR         ( (reg32 *) LumenCom_SCB__INTR_CAUSE)

#define LumenCom_INTR_I2C_EC_REG        (*(reg32 *) LumenCom_SCB__INTR_I2C_EC)
#define LumenCom_INTR_I2C_EC_PTR        ( (reg32 *) LumenCom_SCB__INTR_I2C_EC)

#define LumenCom_INTR_I2C_EC_MASK_REG   (*(reg32 *) LumenCom_SCB__INTR_I2C_EC_MASK)
#define LumenCom_INTR_I2C_EC_MASK_PTR   ( (reg32 *) LumenCom_SCB__INTR_I2C_EC_MASK)

#define LumenCom_INTR_I2C_EC_MASKED_REG (*(reg32 *) LumenCom_SCB__INTR_I2C_EC_MASKED)
#define LumenCom_INTR_I2C_EC_MASKED_PTR ( (reg32 *) LumenCom_SCB__INTR_I2C_EC_MASKED)

#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_INTR_SPI_EC_REG        (*(reg32 *) LumenCom_SCB__INTR_SPI_EC)
    #define LumenCom_INTR_SPI_EC_PTR        ( (reg32 *) LumenCom_SCB__INTR_SPI_EC)

    #define LumenCom_INTR_SPI_EC_MASK_REG   (*(reg32 *) LumenCom_SCB__INTR_SPI_EC_MASK)
    #define LumenCom_INTR_SPI_EC_MASK_PTR   ( (reg32 *) LumenCom_SCB__INTR_SPI_EC_MASK)

    #define LumenCom_INTR_SPI_EC_MASKED_REG (*(reg32 *) LumenCom_SCB__INTR_SPI_EC_MASKED)
    #define LumenCom_INTR_SPI_EC_MASKED_PTR ( (reg32 *) LumenCom_SCB__INTR_SPI_EC_MASKED)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_INTR_MASTER_REG        (*(reg32 *) LumenCom_SCB__INTR_M)
#define LumenCom_INTR_MASTER_PTR        ( (reg32 *) LumenCom_SCB__INTR_M)

#define LumenCom_INTR_MASTER_SET_REG    (*(reg32 *) LumenCom_SCB__INTR_M_SET)
#define LumenCom_INTR_MASTER_SET_PTR    ( (reg32 *) LumenCom_SCB__INTR_M_SET)

#define LumenCom_INTR_MASTER_MASK_REG   (*(reg32 *) LumenCom_SCB__INTR_M_MASK)
#define LumenCom_INTR_MASTER_MASK_PTR   ( (reg32 *) LumenCom_SCB__INTR_M_MASK)

#define LumenCom_INTR_MASTER_MASKED_REG (*(reg32 *) LumenCom_SCB__INTR_M_MASKED)
#define LumenCom_INTR_MASTER_MASKED_PTR ( (reg32 *) LumenCom_SCB__INTR_M_MASKED)

#define LumenCom_INTR_SLAVE_REG         (*(reg32 *) LumenCom_SCB__INTR_S)
#define LumenCom_INTR_SLAVE_PTR         ( (reg32 *) LumenCom_SCB__INTR_S)

#define LumenCom_INTR_SLAVE_SET_REG     (*(reg32 *) LumenCom_SCB__INTR_S_SET)
#define LumenCom_INTR_SLAVE_SET_PTR     ( (reg32 *) LumenCom_SCB__INTR_S_SET)

#define LumenCom_INTR_SLAVE_MASK_REG    (*(reg32 *) LumenCom_SCB__INTR_S_MASK)
#define LumenCom_INTR_SLAVE_MASK_PTR    ( (reg32 *) LumenCom_SCB__INTR_S_MASK)

#define LumenCom_INTR_SLAVE_MASKED_REG  (*(reg32 *) LumenCom_SCB__INTR_S_MASKED)
#define LumenCom_INTR_SLAVE_MASKED_PTR  ( (reg32 *) LumenCom_SCB__INTR_S_MASKED)

#define LumenCom_INTR_TX_REG            (*(reg32 *) LumenCom_SCB__INTR_TX)
#define LumenCom_INTR_TX_PTR            ( (reg32 *) LumenCom_SCB__INTR_TX)

#define LumenCom_INTR_TX_SET_REG        (*(reg32 *) LumenCom_SCB__INTR_TX_SET)
#define LumenCom_INTR_TX_SET_PTR        ( (reg32 *) LumenCom_SCB__INTR_TX_SET)

#define LumenCom_INTR_TX_MASK_REG       (*(reg32 *) LumenCom_SCB__INTR_TX_MASK)
#define LumenCom_INTR_TX_MASK_PTR       ( (reg32 *) LumenCom_SCB__INTR_TX_MASK)

#define LumenCom_INTR_TX_MASKED_REG     (*(reg32 *) LumenCom_SCB__INTR_TX_MASKED)
#define LumenCom_INTR_TX_MASKED_PTR     ( (reg32 *) LumenCom_SCB__INTR_TX_MASKED)

#define LumenCom_INTR_RX_REG            (*(reg32 *) LumenCom_SCB__INTR_RX)
#define LumenCom_INTR_RX_PTR            ( (reg32 *) LumenCom_SCB__INTR_RX)

#define LumenCom_INTR_RX_SET_REG        (*(reg32 *) LumenCom_SCB__INTR_RX_SET)
#define LumenCom_INTR_RX_SET_PTR        ( (reg32 *) LumenCom_SCB__INTR_RX_SET)

#define LumenCom_INTR_RX_MASK_REG       (*(reg32 *) LumenCom_SCB__INTR_RX_MASK)
#define LumenCom_INTR_RX_MASK_PTR       ( (reg32 *) LumenCom_SCB__INTR_RX_MASK)

#define LumenCom_INTR_RX_MASKED_REG     (*(reg32 *) LumenCom_SCB__INTR_RX_MASKED)
#define LumenCom_INTR_RX_MASKED_PTR     ( (reg32 *) LumenCom_SCB__INTR_RX_MASKED)

#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* FF_DATA_NR_LOG2_PLUS1 = 4, MASK = 2^4 - 1 = 15 */
    #define LumenCom_FF_DATA_NR_LOG2_MASK       (0x07u) /* FF_DATA_NR_LOG2 = 3, MASK = 2^3 - 1 = 7 */
#else
    #define LumenCom_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* FF_DATA_NR_LOG2_PLUS1 = 5, MASK = 2^5 - 1 = 31 */
    #define LumenCom_FF_DATA_NR_LOG2_MASK       (0x0Fu) /* FF_DATA_NR_LOG2 = 4, MASK = 2^4 - 1 = 15 */
#endif /* (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */


/***************************************
*        Registers Constants
***************************************/

#if (LumenCom_SCB_IRQ_INTERNAL)
    #define LumenCom_ISR_NUMBER     ((uint8) LumenCom_SCB_IRQ__INTC_NUMBER)
    #define LumenCom_ISR_PRIORITY   ((uint8) LumenCom_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (LumenCom_SCB_IRQ_INTERNAL) */

#if (LumenCom_UART_RX_WAKEUP_IRQ)
    #define LumenCom_RX_WAKE_ISR_NUMBER     ((uint8) LumenCom_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define LumenCom_RX_WAKE_ISR_PRIORITY   ((uint8) LumenCom_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (LumenCom_UART_RX_WAKEUP_IRQ) */

/* LumenCom_CTRL_REG */
#define LumenCom_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define LumenCom_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define LumenCom_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define LumenCom_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */
#define LumenCom_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define LumenCom_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define LumenCom_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define LumenCom_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define LumenCom_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define LumenCom_CTRL_EC_AM_MODE        ((uint32) 0x01u << LumenCom_CTRL_EC_AM_MODE_POS)
#define LumenCom_CTRL_EC_OP_MODE        ((uint32) 0x01u << LumenCom_CTRL_EC_OP_MODE_POS)
#define LumenCom_CTRL_EZBUF_MODE        ((uint32) 0x01u << LumenCom_CTRL_EZBUF_MODE_POS)
#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_CTRL_BYTE_MODE ((uint32) 0x01u << LumenCom_CTRL_BYTE_MODE_POS)
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */
#define LumenCom_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << LumenCom_CTRL_ADDR_ACCEPT_POS)
#define LumenCom_CTRL_BLOCK             ((uint32) 0x01u << LumenCom_CTRL_BLOCK_POS)
#define LumenCom_CTRL_MODE_MASK         ((uint32) 0x03u << LumenCom_CTRL_MODE_POS)
#define LumenCom_CTRL_MODE_I2C          ((uint32) 0x00u)
#define LumenCom_CTRL_MODE_SPI          ((uint32) 0x01u << LumenCom_CTRL_MODE_POS)
#define LumenCom_CTRL_MODE_UART         ((uint32) 0x02u << LumenCom_CTRL_MODE_POS)
#define LumenCom_CTRL_ENABLED           ((uint32) 0x01u << LumenCom_CTRL_ENABLED_POS)

/* LumenCom_STATUS_REG */
#define LumenCom_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define LumenCom_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* LumenCom_SPI_CTRL_REG  */
#define LumenCom_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define LumenCom_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define LumenCom_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define LumenCom_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define LumenCom_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define LumenCom_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define LumenCom_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define LumenCom_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define LumenCom_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */
#define LumenCom_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define LumenCom_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define LumenCom_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define LumenCom_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define LumenCom_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define LumenCom_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << LumenCom_SPI_CTRL_SELECT_PRECEDE_POS)
#define LumenCom_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << LumenCom_SPI_CTRL_CPHA_POS)
#define LumenCom_SPI_CTRL_CPHA                  ((uint32) 0x01u << LumenCom_SPI_CTRL_CPHA_POS)
#define LumenCom_SPI_CTRL_CPOL                  ((uint32) 0x01u << LumenCom_SPI_CTRL_CPOL_POS)
#define LumenCom_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    LumenCom_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << LumenCom_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define LumenCom_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << LumenCom_SPI_CTRL_SSEL0_POLARITY_POS)
    #define LumenCom_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << LumenCom_SPI_CTRL_SSEL1_POLARITY_POS)
    #define LumenCom_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << LumenCom_SPI_CTRL_SSEL2_POLARITY_POS)
    #define LumenCom_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << LumenCom_SPI_CTRL_SSEL3_POLARITY_POS)
    #define LumenCom_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << LumenCom_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

#define LumenCom_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << LumenCom_SPI_CTRL_LOOPBACK_POS)
#define LumenCom_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << LumenCom_SPI_CTRL_MODE_POS)
#define LumenCom_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define LumenCom_SPI_CTRL_MODE_TI               ((uint32) 0x01u << LumenCom_CTRL_MODE_POS)
#define LumenCom_SPI_CTRL_MODE_NS               ((uint32) 0x02u << LumenCom_CTRL_MODE_POS)
#define LumenCom_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << LumenCom_SPI_CTRL_SLAVE_SELECT_POS)
#define LumenCom_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define LumenCom_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << LumenCom_SPI_CTRL_SLAVE_SELECT_POS)
#define LumenCom_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << LumenCom_SPI_CTRL_SLAVE_SELECT_POS)
#define LumenCom_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << LumenCom_SPI_CTRL_SLAVE_SELECT_POS)
#define LumenCom_SPI_CTRL_MASTER                ((uint32) 0x01u << LumenCom_SPI_CTRL_MASTER_MODE_POS)
#define LumenCom_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* LumenCom_SPI_STATUS_REG  */
#define LumenCom_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define LumenCom_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define LumenCom_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LumenCom_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LumenCom_I2C_STATUS_EZBUF_ADDR_POS)

/* LumenCom_UART_CTRL */
#define LumenCom_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define LumenCom_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define LumenCom_UART_CTRL_LOOPBACK             ((uint32) 0x01u << LumenCom_UART_CTRL_LOOPBACK_POS)
#define LumenCom_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define LumenCom_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << LumenCom_UART_CTRL_MODE_POS)
#define LumenCom_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << LumenCom_UART_CTRL_MODE_POS)
#define LumenCom_UART_CTRL_MODE_MASK            ((uint32) 0x03u << LumenCom_UART_CTRL_MODE_POS)

/* LumenCom_UART_TX_CTRL */
#define LumenCom_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define LumenCom_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define LumenCom_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define LumenCom_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define LumenCom_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define LumenCom_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define LumenCom_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define LumenCom_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define LumenCom_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    LumenCom_UART_TX_CTRL_PARITY_POS)
#define LumenCom_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    LumenCom_UART_TX_CTRL_PARITY_ENABLED_POS)
#define LumenCom_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    LumenCom_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* LumenCom_UART_RX_CTRL */
#define LumenCom_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define LumenCom_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define LumenCom_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define LumenCom_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define LumenCom_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define LumenCom_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define LumenCom_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define LumenCom_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define LumenCom_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define LumenCom_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define LumenCom_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define LumenCom_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define LumenCom_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define LumenCom_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define LumenCom_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_PARITY_POS)
#define LumenCom_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_PARITY_ENABLED_POS)
#define LumenCom_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_POLARITY_POS)
#define LumenCom_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   LumenCom_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define LumenCom_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define LumenCom_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_MP_MODE_POS)
#define LumenCom_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_LIN_MODE_POS)
#define LumenCom_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    LumenCom_UART_RX_CTRL_SKIP_START_POS)
#define LumenCom_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    LumenCom_UART_RX_CTRL_BREAK_WIDTH_POS)
/* LumenCom_UART_RX_STATUS_REG */
#define LumenCom_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define LumenCom_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    /* LumenCom_UART_FLOW_CTRL_REG */
    #define LumenCom_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define LumenCom_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define LumenCom_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define LumenCom_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define LumenCom_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK)
    #define LumenCom_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       LumenCom_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define LumenCom_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       LumenCom_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define LumenCom_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       LumenCom_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

/* LumenCom_I2C_CTRL */
#define LumenCom_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define LumenCom_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define LumenCom_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define LumenCom_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define LumenCom_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define LumenCom_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define LumenCom_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define LumenCom_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define LumenCom_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define LumenCom_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define LumenCom_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define LumenCom_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                LumenCom_I2C_CTRL_LOW_PHASE_OVS_POS)
#define LumenCom_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_M_READY_DATA_ACK_POS)
#define LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define LumenCom_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define LumenCom_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define LumenCom_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_S_READY_DATA_ACK_POS)
#define LumenCom_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define LumenCom_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_LOOPBACK_POS)
#define LumenCom_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_SLAVE_MODE_POS)
#define LumenCom_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                LumenCom_I2C_CTRL_MASTER_MODE_POS)
#define LumenCom_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                LumenCom_I2C_CTRL_SLAVE_MODE_POS)

/* LumenCom_I2C_STATUS_REG  */
#define LumenCom_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define LumenCom_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define LumenCom_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define LumenCom_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define LumenCom_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define LumenCom_I2C_STATUS_S_READ          ((uint32) 0x01u << LumenCom_I2C_STATUS_S_READ_POS)
#define LumenCom_I2C_STATUS_M_READ          ((uint32) 0x01u << LumenCom_I2C_STATUS_M_READ_POS)
#define LumenCom_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << LumenCom_I2C_STATUS_EZBUF_ADDR_POS)

/* LumenCom_I2C_MASTER_CMD_REG */
#define LumenCom_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define LumenCom_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define LumenCom_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define LumenCom_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define LumenCom_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define LumenCom_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define LumenCom_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   LumenCom_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define LumenCom_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   LumenCom_I2C_MASTER_CMD_M_ACK_POS)
#define LumenCom_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    LumenCom_I2C_MASTER_CMD_M_NACK_POS)
#define LumenCom_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    LumenCom_I2C_MASTER_CMD_M_STOP_POS)

/* LumenCom_I2C_SLAVE_CMD_REG  */
#define LumenCom_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LumenCom_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LumenCom_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LumenCom_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LumenCom_I2C_SLAVE_CMD_S_NACK_POS)

#define LumenCom_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define LumenCom_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define LumenCom_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define LumenCom_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << LumenCom_I2C_SLAVE_CMD_S_NACK_POS)

/* LumenCom_I2C_CFG_REG */
#if (LumenCom_CY_SCBIP_V0)
#define LumenCom_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define LumenCom_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define LumenCom_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define LumenCom_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define LumenCom_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define LumenCom_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define LumenCom_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define LumenCom_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define LumenCom_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define LumenCom_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define LumenCom_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define LumenCom_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define LumenCom_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define LumenCom_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_TRIM_POS)
#define LumenCom_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                LumenCom_I2C_CFG_SCL_FILT_HYS_POS)
#define LumenCom_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                LumenCom_I2C_CFG_SCL_FILT_TRIM_POS)
#define LumenCom_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define LumenCom_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define LumenCom_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_HS_POS)
#define LumenCom_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_ENABLED_POS)
#define LumenCom_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SCL_FILT_HS_POS)
#define LumenCom_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SCL_FILT_ENABLED_POS)
#define LumenCom_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define LumenCom_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                LumenCom_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define LumenCom_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define LumenCom_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define LumenCom_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define LumenCom_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define LumenCom_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define LumenCom_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define LumenCom_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define LumenCom_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define LumenCom_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define LumenCom_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << LumenCom_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define LumenCom_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            LumenCom_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define LumenCom_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << LumenCom_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define LumenCom_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            LumenCom_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define LumenCom_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            LumenCom_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define LumenCom_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            LumenCom_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define LumenCom_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            LumenCom_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (LumenCom_CY_SCBIP_V0) */


/* LumenCom_TX_CTRL_REG */
#define LumenCom_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LumenCom_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LumenCom_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define LumenCom_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LumenCom_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << LumenCom_TX_CTRL_MSB_FIRST_POS)
#define LumenCom_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LumenCom_TX_CTRL_ENABLED            ((uint32) 0x01u << LumenCom_TX_CTRL_ENABLED_POS)

/* LumenCom_TX_CTRL_FIFO_REG */
#define LumenCom_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define LumenCom_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define LumenCom_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define LumenCom_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK)
#define LumenCom_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LumenCom_TX_FIFO_CTRL_CLEAR_POS)
#define LumenCom_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LumenCom_TX_FIFO_CTRL_FREEZE_POS)

/* LumenCom_TX_FIFO_STATUS_REG */
#define LumenCom_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define LumenCom_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define LumenCom_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define LumenCom_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define LumenCom_TX_FIFO_STATUS_USED_MASK   ((uint32) LumenCom_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LumenCom_TX_FIFO_SR_VALID           ((uint32) 0x01u << LumenCom_TX_FIFO_SR_VALID_POS)
#define LumenCom_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK << \
                                                                    LumenCom_TX_FIFO_STATUS_RD_PTR_POS)
#define LumenCom_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK << \
                                                                    LumenCom_TX_FIFO_STATUS_WR_PTR_POS)

/* LumenCom_TX_FIFO_WR_REG */
#define LumenCom_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define LumenCom_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* LumenCom_RX_CTRL_REG */
#define LumenCom_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define LumenCom_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define LumenCom_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define LumenCom_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define LumenCom_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define LumenCom_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << LumenCom_RX_CTRL_MSB_FIRST_POS)
#define LumenCom_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define LumenCom_RX_CTRL_MEDIAN             ((uint32) 0x01u << LumenCom_RX_CTRL_MEDIAN_POS)
#define LumenCom_RX_CTRL_ENABLED            ((uint32) 0x01u << LumenCom_RX_CTRL_ENABLED_POS)


/* LumenCom_RX_FIFO_CTRL_REG */
#define LumenCom_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define LumenCom_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define LumenCom_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define LumenCom_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK)
#define LumenCom_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << LumenCom_RX_FIFO_CTRL_CLEAR_POS)
#define LumenCom_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << LumenCom_RX_FIFO_CTRL_FREEZE_POS)

/* LumenCom_RX_FIFO_STATUS_REG */
#define LumenCom_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define LumenCom_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define LumenCom_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define LumenCom_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define LumenCom_RX_FIFO_STATUS_USED_MASK   ((uint32) LumenCom_FF_DATA_NR_LOG2_PLUS1_MASK)
#define LumenCom_RX_FIFO_SR_VALID           ((uint32) 0x01u << LumenCom_RX_FIFO_SR_VALID_POS)
#define LumenCom_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK << \
                                                                    LumenCom_RX_FIFO_STATUS_RD_PTR_POS)
#define LumenCom_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) LumenCom_FF_DATA_NR_LOG2_MASK << \
                                                                    LumenCom_RX_FIFO_STATUS_WR_PTR_POS)

/* LumenCom_RX_MATCH_REG */
#define LumenCom_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define LumenCom_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define LumenCom_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define LumenCom_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << LumenCom_RX_MATCH_MASK_POS)

/* LumenCom_RX_FIFO_WR_REG */
#define LumenCom_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define LumenCom_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* LumenCom_RX_FIFO_RD_SILENT_REG */
#define LumenCom_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LumenCom_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LumenCom_RX_FIFO_RD_SILENT_REG */
#define LumenCom_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define LumenCom_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* LumenCom_EZBUF_DATA_REG */
#define LumenCom_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define LumenCom_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  LumenCom_INTR_CAUSE_REG */
#define LumenCom_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define LumenCom_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define LumenCom_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define LumenCom_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define LumenCom_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define LumenCom_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define LumenCom_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define LumenCom_INTR_CAUSE_SLAVE       ((uint32) 0x01u << LumenCom_INTR_CAUSE_SLAVE_POS)
#define LumenCom_INTR_CAUSE_TX          ((uint32) 0x01u << LumenCom_INTR_CAUSE_TX_POS)
#define LumenCom_INTR_CAUSE_RX          ((uint32) 0x01u << LumenCom_INTR_CAUSE_RX_POS)
#define LumenCom_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << LumenCom_INTR_CAUSE_I2C_EC_POS)
#define LumenCom_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << LumenCom_INTR_CAUSE_SPI_EC_POS)

/* LumenCom_INTR_SPI_EC_REG, LumenCom_INTR_SPI_EC_MASK_REG, LumenCom_INTR_SPI_EC_MASKED_REG */
#define LumenCom_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LumenCom_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LumenCom_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LumenCom_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define LumenCom_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SPI_EC_EZBUF_STOP_POS)
#define LumenCom_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* LumenCom_INTR_I2C_EC, LumenCom_INTR_I2C_EC_MASK, LumenCom_INTR_I2C_EC_MASKED */
#define LumenCom_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define LumenCom_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define LumenCom_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define LumenCom_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define LumenCom_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_I2C_EC_EZBUF_STOP_POS)
#define LumenCom_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    LumenCom_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* LumenCom_INTR_MASTER, LumenCom_INTR_MASTER_SET,
   LumenCom_INTR_MASTER_MASK, LumenCom_INTR_MASTER_MASKED */
#define LumenCom_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define LumenCom_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define LumenCom_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define LumenCom_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define LumenCom_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define LumenCom_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define LumenCom_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define LumenCom_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << LumenCom_INTR_MASTER_I2C_NACK_POS)
#define LumenCom_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << LumenCom_INTR_MASTER_I2C_ACK_POS)
#define LumenCom_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << LumenCom_INTR_MASTER_I2C_STOP_POS)
#define LumenCom_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    LumenCom_INTR_MASTER_I2C_BUS_ERROR_POS)
#define LumenCom_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << LumenCom_INTR_MASTER_SPI_DONE_POS)

/*
* LumenCom_INTR_SLAVE, LumenCom_INTR_SLAVE_SET,
* LumenCom_INTR_SLAVE_MASK, LumenCom_INTR_SLAVE_MASKED
*/
#define LumenCom_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define LumenCom_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define LumenCom_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define LumenCom_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define LumenCom_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define LumenCom_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define LumenCom_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define LumenCom_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define LumenCom_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define LumenCom_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define LumenCom_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define LumenCom_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define LumenCom_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define LumenCom_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_NACK_POS)
#define LumenCom_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_ACK_POS)
#define LumenCom_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define LumenCom_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_STOP_POS)
#define LumenCom_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_START_POS)
#define LumenCom_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define LumenCom_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_GENERAL_POS)
#define LumenCom_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define LumenCom_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   LumenCom_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define LumenCom_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define LumenCom_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    LumenCom_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* LumenCom_INTR_TX, LumenCom_INTR_TX_SET,
* LumenCom_INTR_TX_MASK, LumenCom_INTR_TX_MASKED
*/
#define LumenCom_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define LumenCom_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define LumenCom_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define LumenCom_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define LumenCom_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define LumenCom_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define LumenCom_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define LumenCom_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define LumenCom_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define LumenCom_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define LumenCom_INTR_TX_FIFO_LEVEL         (LumenCom_INTR_TX_TRIGGER)
#define LumenCom_INTR_TX_NOT_FULL           ((uint32) 0x01u << LumenCom_INTR_TX_NOT_FULL_POS)
#define LumenCom_INTR_TX_EMPTY              ((uint32) 0x01u << LumenCom_INTR_TX_EMPTY_POS)
#define LumenCom_INTR_TX_OVERFLOW           ((uint32) 0x01u << LumenCom_INTR_TX_OVERFLOW_POS)
#define LumenCom_INTR_TX_UNDERFLOW          ((uint32) 0x01u << LumenCom_INTR_TX_UNDERFLOW_POS)
#define LumenCom_INTR_TX_BLOCKED            ((uint32) 0x01u << LumenCom_INTR_TX_BLOCKED_POS)
#define LumenCom_INTR_TX_UART_NACK          ((uint32) 0x01u << LumenCom_INTR_TX_UART_NACK_POS)
#define LumenCom_INTR_TX_UART_DONE          ((uint32) 0x01u << LumenCom_INTR_TX_UART_DONE_POS)
#define LumenCom_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << LumenCom_INTR_TX_UART_ARB_LOST_POS)

/*
* LumenCom_INTR_RX, LumenCom_INTR_RX_SET,
* LumenCom_INTR_RX_MASK, LumenCom_INTR_RX_MASKED
*/
#define LumenCom_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define LumenCom_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define LumenCom_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define LumenCom_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define LumenCom_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define LumenCom_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define LumenCom_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define LumenCom_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define LumenCom_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define LumenCom_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define LumenCom_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define LumenCom_INTR_RX_FIFO_LEVEL         (LumenCom_INTR_RX_TRIGGER)
#define LumenCom_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << LumenCom_INTR_RX_NOT_EMPTY_POS)
#define LumenCom_INTR_RX_FULL               ((uint32) 0x01u << LumenCom_INTR_RX_FULL_POS)
#define LumenCom_INTR_RX_OVERFLOW           ((uint32) 0x01u << LumenCom_INTR_RX_OVERFLOW_POS)
#define LumenCom_INTR_RX_UNDERFLOW          ((uint32) 0x01u << LumenCom_INTR_RX_UNDERFLOW_POS)
#define LumenCom_INTR_RX_BLOCKED            ((uint32) 0x01u << LumenCom_INTR_RX_BLOCKED_POS)
#define LumenCom_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << LumenCom_INTR_RX_FRAME_ERROR_POS)
#define LumenCom_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << LumenCom_INTR_RX_PARITY_ERROR_POS)
#define LumenCom_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << LumenCom_INTR_RX_BAUD_DETECT_POS)
#define LumenCom_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << LumenCom_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define LumenCom_INTR_I2C_EC_ALL    (LumenCom_INTR_I2C_EC_WAKE_UP    | \
                                             LumenCom_INTR_I2C_EC_EZBUF_STOP | \
                                             LumenCom_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define LumenCom_INTR_SPI_EC_ALL    (LumenCom_INTR_SPI_EC_WAKE_UP    | \
                                             LumenCom_INTR_SPI_EC_EZBUF_STOP | \
                                             LumenCom_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define LumenCom_INTR_MASTER_ALL    (LumenCom_INTR_MASTER_I2C_ARB_LOST  | \
                                             LumenCom_INTR_MASTER_I2C_NACK      | \
                                             LumenCom_INTR_MASTER_I2C_ACK       | \
                                             LumenCom_INTR_MASTER_I2C_STOP      | \
                                             LumenCom_INTR_MASTER_I2C_BUS_ERROR | \
                                             LumenCom_INTR_MASTER_SPI_DONE)

#define LumenCom_INTR_SLAVE_ALL     (LumenCom_INTR_SLAVE_I2C_ARB_LOST      | \
                                             LumenCom_INTR_SLAVE_I2C_NACK          | \
                                             LumenCom_INTR_SLAVE_I2C_ACK           | \
                                             LumenCom_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             LumenCom_INTR_SLAVE_I2C_STOP          | \
                                             LumenCom_INTR_SLAVE_I2C_START         | \
                                             LumenCom_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             LumenCom_INTR_SLAVE_I2C_GENERAL       | \
                                             LumenCom_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             LumenCom_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             LumenCom_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             LumenCom_INTR_SLAVE_SPI_BUS_ERROR)

#define LumenCom_INTR_TX_ALL        (LumenCom_INTR_TX_TRIGGER   | \
                                             LumenCom_INTR_TX_NOT_FULL  | \
                                             LumenCom_INTR_TX_EMPTY     | \
                                             LumenCom_INTR_TX_OVERFLOW  | \
                                             LumenCom_INTR_TX_UNDERFLOW | \
                                             LumenCom_INTR_TX_BLOCKED   | \
                                             LumenCom_INTR_TX_UART_NACK | \
                                             LumenCom_INTR_TX_UART_DONE | \
                                             LumenCom_INTR_TX_UART_ARB_LOST)

#define LumenCom_INTR_RX_ALL        (LumenCom_INTR_RX_TRIGGER      | \
                                             LumenCom_INTR_RX_NOT_EMPTY    | \
                                             LumenCom_INTR_RX_FULL         | \
                                             LumenCom_INTR_RX_OVERFLOW     | \
                                             LumenCom_INTR_RX_UNDERFLOW    | \
                                             LumenCom_INTR_RX_BLOCKED      | \
                                             LumenCom_INTR_RX_FRAME_ERROR  | \
                                             LumenCom_INTR_RX_PARITY_ERROR | \
                                             LumenCom_INTR_RX_BAUD_DETECT  | \
                                             LumenCom_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define LumenCom_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define LumenCom_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define LumenCom_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define LumenCom_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define LumenCom_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define LumenCom_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define LumenCom_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define LumenCom_CTRL_OVS_IRDA_OVS16        (LumenCom_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define LumenCom_SCB_SW_RESET \
                        do{           \
                            LumenCom_CTRL_REG &= ((uint32) ~LumenCom_CTRL_ENABLED); \
                            LumenCom_CTRL_REG |= ((uint32)  LumenCom_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define LumenCom_CLEAR_TX_FIFO \
                            do{        \
                                LumenCom_TX_FIFO_CTRL_REG |= ((uint32)  LumenCom_TX_FIFO_CTRL_CLEAR); \
                                LumenCom_TX_FIFO_CTRL_REG &= ((uint32) ~LumenCom_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LumenCom_GET_TX_FIFO_ENTRIES    (LumenCom_TX_FIFO_STATUS_REG & \
                                                 LumenCom_TX_FIFO_STATUS_USED_MASK)

#define LumenCom_GET_TX_FIFO_SR_VALID   ((0u != (LumenCom_TX_FIFO_STATUS_REG & \
                                                         LumenCom_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define LumenCom_CLEAR_RX_FIFO \
                            do{        \
                                LumenCom_RX_FIFO_CTRL_REG |= ((uint32)  LumenCom_RX_FIFO_CTRL_CLEAR); \
                                LumenCom_RX_FIFO_CTRL_REG &= ((uint32) ~LumenCom_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define LumenCom_GET_RX_FIFO_ENTRIES    (LumenCom_RX_FIFO_STATUS_REG & \
                                                    LumenCom_RX_FIFO_STATUS_USED_MASK)

#define LumenCom_GET_RX_FIFO_SR_VALID   ((0u != (LumenCom_RX_FIFO_STATUS_REG & \
                                                         LumenCom_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in LumenCom_INTR_X_MASK_REG */
#define LumenCom_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    LumenCom_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    LumenCom_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    LumenCom_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    LumenCom_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    LumenCom_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    LumenCom_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in LumenCom_INTR_X_MASK_REG */
#define LumenCom_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    LumenCom_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    LumenCom_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    LumenCom_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    LumenCom_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    LumenCom_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    LumenCom_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in LumenCom_INTR_X_MASK_REG */
#define LumenCom_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    LumenCom_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    LumenCom_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                LumenCom_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LumenCom_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    LumenCom_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define LumenCom_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    LumenCom_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define LumenCom_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    LumenCom_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in LumenCom_INTR_X_SET_REG */
#define LumenCom_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    LumenCom_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    LumenCom_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    LumenCom_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    LumenCom_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in LumenCom_INTR_X_REG */
#define LumenCom_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    LumenCom_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    LumenCom_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    LumenCom_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    LumenCom_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    LumenCom_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define LumenCom_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    LumenCom_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in LumenCom_INTR_CAUSE_REG */
#define LumenCom_CHECK_CAUSE_INTR(sourceMask)    (0u != (LumenCom_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define LumenCom_CHECK_INTR_I2C_EC(sourceMask)  (0u != (LumenCom_INTR_I2C_EC_REG & (sourceMask)))
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_CHECK_INTR_SPI_EC(sourceMask)  (0u != (LumenCom_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!LumenCom_CY_SCBIP_V1) */
#define LumenCom_CHECK_INTR_MASTER(sourceMask)  (0u != (LumenCom_INTR_MASTER_REG & (sourceMask)))
#define LumenCom_CHECK_INTR_SLAVE(sourceMask)   (0u != (LumenCom_INTR_SLAVE_REG  & (sourceMask)))
#define LumenCom_CHECK_INTR_TX(sourceMask)      (0u != (LumenCom_INTR_TX_REG     & (sourceMask)))
#define LumenCom_CHECK_INTR_RX(sourceMask)      (0u != (LumenCom_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in LumenCom_INTR_X_MASKED_REG */
#define LumenCom_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (LumenCom_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (LumenCom_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!LumenCom_CY_SCBIP_V1) */
#define LumenCom_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (LumenCom_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define LumenCom_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (LumenCom_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define LumenCom_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (LumenCom_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define LumenCom_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (LumenCom_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in LumenCom_CTRL_REG: generally is used to check enable bit */
#define LumenCom_GET_CTRL_ENABLED    (0u != (LumenCom_CTRL_REG & LumenCom_CTRL_ENABLED))

#define LumenCom_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (LumenCom_I2C_CTRL_REG & \
                                                                LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define LumenCom_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                LumenCom_I2C_CTRL_REG |= LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LumenCom_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                LumenCom_I2C_CTRL_REG |= LumenCom_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LumenCom_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                LumenCom_I2C_CTRL_REG |= LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LumenCom_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                LumenCom_I2C_CTRL_REG |= LumenCom_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LumenCom_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                LumenCom_I2C_CTRL_REG |= LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define LumenCom_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                LumenCom_I2C_CTRL_REG &= ~LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LumenCom_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                LumenCom_I2C_CTRL_REG &= ~LumenCom_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define LumenCom_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                LumenCom_I2C_CTRL_REG &= ~LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define LumenCom_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                LumenCom_I2C_CTRL_REG &= ~LumenCom_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define LumenCom_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                LumenCom_I2C_CTRL_REG &= ~LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define LumenCom_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                LumenCom_I2C_CTRL_REG |= (LumenCom_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define LumenCom_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                LumenCom_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LumenCom_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    LumenCom_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define LumenCom_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                LumenCom_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(LumenCom_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    LumenCom_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define LumenCom_I2C_MASTER_GENERATE_START \
                            do{                    \
                                LumenCom_I2C_MASTER_CMD_REG = LumenCom_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define LumenCom_I2C_MASTER_CLEAR_START \
                            do{                 \
                                LumenCom_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define LumenCom_I2C_MASTER_GENERATE_RESTART LumenCom_I2CReStartGeneration()

#define LumenCom_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                LumenCom_I2C_MASTER_CMD_REG =                                            \
                                    (LumenCom_I2C_MASTER_CMD_M_STOP |                                    \
                                        (LumenCom_CHECK_I2C_STATUS(LumenCom_I2C_STATUS_M_READ) ? \
                                            (LumenCom_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define LumenCom_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                LumenCom_I2C_MASTER_CMD_REG = LumenCom_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define LumenCom_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                LumenCom_I2C_MASTER_CMD_REG = LumenCom_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define LumenCom_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                LumenCom_I2C_SLAVE_CMD_REG = LumenCom_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void LumenCom_I2CSlaveNackGeneration(void);
    #define LumenCom_I2C_SLAVE_GENERATE_NACK LumenCom_I2CSlaveNackGeneration()

#else
    #define LumenCom_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                LumenCom_I2C_SLAVE_CMD_REG = LumenCom_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

#define LumenCom_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                LumenCom_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define LumenCom_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    LumenCom_I2C_SLAVE_ADDR_POS)) & \
                                                                        LumenCom_I2C_SLAVE_ADDR_MASK)

#define LumenCom_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> LumenCom_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define LumenCom_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define LumenCom_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (LumenCom_CY_SCBIP_V0)
    #define LumenCom_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            LumenCom_I2C_CFG_REG =                  \
                            ((LumenCom_I2C_CFG_REG & (uint32) ~LumenCom_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<LumenCom_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (LumenCom_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define LumenCom_DIGITAL_FILTER_DISABLE    (0u)
#define LumenCom_DIGITAL_FILTER_ENABLE     (1u)
#define LumenCom_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (LumenCom_CY_SCBIP_V0)
    /* LumenCom_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define LumenCom_I2C_CFG_FILT_MASK  (LumenCom_I2C_CFG_SDA_FILT_ENABLED | \
                                                 LumenCom_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* LumenCom_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define LumenCom_I2C_CFG_FILT_MASK  (LumenCom_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 LumenCom_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (LumenCom_CY_SCBIP_V0) */

#define LumenCom_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            LumenCom_I2C_CFG_REG &= (uint32) ~LumenCom_I2C_CFG_FILT_MASK; \
        }while(0)

#define LumenCom_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            LumenCom_I2C_CFG_REG |= (uint32)  LumenCom_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define LumenCom_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    LumenCom_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        LumenCom_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in LumenCom_I2C_STATUS_REG */
#define LumenCom_CHECK_I2C_STATUS(sourceMask)   (0u != (LumenCom_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in LumenCom_SPI_STATUS_REG */
#define LumenCom_CHECK_SPI_STATUS(sourceMask)   (0u != (LumenCom_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on LumenCom_CTRL_BYTE_MODE bit */
#define LumenCom_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * LumenCom_FIFO_SIZE) : (LumenCom_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* LumenCom_CTRL */
#define LumenCom_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & LumenCom_CTRL_OVS_MASK)

#define LumenCom_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (LumenCom_CTRL_EC_OP_MODE)  : (0u))

#define LumenCom_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (LumenCom_CTRL_EC_AM_MODE)  : (0u))

#define LumenCom_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (LumenCom_CTRL_BLOCK)       : (0u))

#define LumenCom_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (LumenCom_CTRL_ADDR_ACCEPT) : (0u))

#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define LumenCom_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (LumenCom_CTRL_BYTE_MODE) : (0u))
#endif /* (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

/* LumenCom_I2C_CTRL */
#define LumenCom_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        LumenCom_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define LumenCom_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    LumenCom_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    LumenCom_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define LumenCom_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (LumenCom_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define LumenCom_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (LumenCom_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define LumenCom_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << LumenCom_I2C_CTRL_SLAVE_MODE_POS)

/* LumenCom_SPI_CTRL */
#define LumenCom_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (LumenCom_SPI_CTRL_CONTINUOUS) : (0u))

#define LumenCom_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (LumenCom_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define LumenCom_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        LumenCom_SPI_CTRL_CPHA_POS) & \
                                                                        LumenCom_SPI_CTRL_SCLK_MODE_MASK)

#define LumenCom_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (LumenCom_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define LumenCom_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define LumenCom_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (LumenCom_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define LumenCom_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     LumenCom_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     LumenCom_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

#define LumenCom_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << LumenCom_SPI_CTRL_MODE_POS) & \
                                                                                 LumenCom_SPI_CTRL_MODE_MASK)

#define LumenCom_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      LumenCom_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      LumenCom_SPI_CTRL_SLAVE_SELECT_MASK)

#define LumenCom_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (LumenCom_SPI_CTRL_MASTER) : (0u))

/* LumenCom_UART_CTRL */
#define LumenCom_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            LumenCom_UART_CTRL_MODE_POS) & \
                                                                            LumenCom_UART_CTRL_MODE_MASK)

/* LumenCom_UART_RX_CTRL */
#define LumenCom_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        LumenCom_UART_RX_CTRL_STOP_BITS_MASK)

#define LumenCom_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (LumenCom_UART_RX_CTRL_PARITY) : (0u))

#define LumenCom_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (LumenCom_UART_RX_CTRL_POLARITY) : (0u))

#define LumenCom_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LumenCom_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define LumenCom_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (LumenCom_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define LumenCom_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (LumenCom_UART_RX_CTRL_MP_MODE) : (0u))

/* LumenCom_UART_TX_CTRL */
#define LumenCom_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                LumenCom_UART_RX_CTRL_STOP_BITS_MASK)

#define LumenCom_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (LumenCom_UART_TX_CTRL_PARITY) : (0u))

#define LumenCom_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (LumenCom_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* LumenCom_UART_FLOW_CTRL */
#if !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
    #define LumenCom_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 LumenCom_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define LumenCom_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LumenCom_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define LumenCom_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (LumenCom_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define LumenCom_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (LumenCom_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

/* LumenCom_RX_CTRL */
#define LumenCom_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LumenCom_RX_CTRL_DATA_WIDTH_MASK)

#define LumenCom_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LumenCom_RX_CTRL_MSB_FIRST) : (0u))

#define LumenCom_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (LumenCom_RX_CTRL_MEDIAN) : (0u))

/* LumenCom_RX_MATCH */
#define LumenCom_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & LumenCom_RX_MATCH_ADDR_MASK)
#define LumenCom_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            LumenCom_RX_MATCH_MASK_POS) & \
                                                            LumenCom_RX_MATCH_MASK_MASK)

/* LumenCom_RX_FIFO_CTRL */
#define LumenCom_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LumenCom_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LumenCom_TX_CTRL */
#define LumenCom_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                LumenCom_RX_CTRL_DATA_WIDTH_MASK)

#define LumenCom_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (LumenCom_TX_CTRL_MSB_FIRST) : (0u))

/* LumenCom_TX_FIFO_CTRL */
#define LumenCom_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    LumenCom_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* LumenCom_INTR_SLAVE_I2C_GENERAL */
#define LumenCom_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (LumenCom_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled LumenCom_SPI_CTRL_REG */
#define LumenCom_CHECK_SPI_MASTER   (0u != (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define LumenCom_GET_SPI_SCLK_INACTIVE \
            ((0u == (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1)
#define LumenCom_GET_SPI_SS0_INACTIVE       (1u)
#define LumenCom_GET_SPI_SS1_INACTIVE       (1u)
#define LumenCom_GET_SPI_SS2_INACTIVE       (1u)
#define LumenCom_GET_SPI_SS3_INACTIVE       (1u)
#define LumenCom_GET_UART_RTS_INACTIVE      (1u)

#else
#define LumenCom_GET_SPI_SS0_INACTIVE  \
        ((0u != (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define LumenCom_GET_SPI_SS1_INACTIVE  \
        ((0u != (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define LumenCom_GET_SPI_SS2_INACTIVE  \
        ((0u != (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define LumenCom_GET_SPI_SS3_INACTIVE  \
        ((0u != (LumenCom_SPI_CTRL_REG & LumenCom_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define LumenCom_GET_UART_RTS_INACTIVE \
        ((0u == (LumenCom_UART_FLOW_CTRL_REG & LumenCom_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(LumenCom_CY_SCBIP_V0 || LumenCom_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define LumenCom_CLEAR_REG          ((uint32) (0u))
#define LumenCom_NO_INTR_SOURCES    ((uint32) (0u))
#define LumenCom_DUMMY_PARAM        ((uint32) (0u))
#define LumenCom_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define LumenCom_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define LumenCom_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define LumenCom_CHECK_INTR_EC_I2C(sourceMask)  LumenCom_CHECK_INTR_I2C_EC(sourceMask)
#if (!LumenCom_CY_SCBIP_V1)
    #define LumenCom_CHECK_INTR_EC_SPI(sourceMask)  LumenCom_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!LumenCom_CY_SCBIP_V1) */

#define LumenCom_CY_SCBIP_V1_I2C_ONLY   (LumenCom_CY_SCBIP_V1)

#endif /* (CY_SCB_LumenCom_H) */


/* [] END OF FILE */
