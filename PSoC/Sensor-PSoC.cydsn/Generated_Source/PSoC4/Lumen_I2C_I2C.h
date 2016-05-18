/*******************************************************************************
* File Name: Lumen_I2C_I2C.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  the I2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_Lumen_I2C_H)
#define CY_SCB_I2C_Lumen_I2C_H

#include "Lumen_I2C.h"


/***************************************
*   Initial Parameter Constants
****************************************/

#define Lumen_I2C_I2C_MODE                   (2u)
#define Lumen_I2C_I2C_OVS_FACTOR_LOW         (8u)
#define Lumen_I2C_I2C_OVS_FACTOR_HIGH        (8u)
#define Lumen_I2C_I2C_MEDIAN_FILTER_ENABLE   (1u)
#define Lumen_I2C_I2C_SLAVE_ADDRESS          (8u)
#define Lumen_I2C_I2C_SLAVE_ADDRESS_MASK     (254u)
#define Lumen_I2C_I2C_ACCEPT_ADDRESS         (0u)
#define Lumen_I2C_I2C_ACCEPT_GENERAL_CALL    (0u)
#define Lumen_I2C_I2C_WAKE_ENABLE            (0u)
#define Lumen_I2C_I2C_DATA_RATE              (100u)
#define Lumen_I2C_I2C_DATA_RATE_ACTUAL       (100u)
#define Lumen_I2C_I2C_CLOCK_FROM_TERM        (0u)
#define Lumen_I2C_I2C_EXTERN_INTR_HANDLER    (0u)
#define Lumen_I2C_I2C_BYTE_MODE_ENABLE       (0u)
#define Lumen_I2C_I2C_MANUAL_OVS_CONTROL     (0u)


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* I2C sub mode enum */
#define Lumen_I2C_I2C_MODE_SLAVE              (0x01u)
#define Lumen_I2C_I2C_MODE_MASTER             (0x02u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER       (0x06u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

#if (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Returns true if slave mode is enabled */
    #define Lumen_I2C_I2C_SLAVE  (0u != (Lumen_I2C_I2C_MODE_SLAVE & Lumen_I2C_mode))

    /* Returns true if master mode is enabled */
    #define Lumen_I2C_I2C_MASTER (0u != (Lumen_I2C_I2C_MODE_MASTER & Lumen_I2C_mode))

    /* Returns true if multi-master mode is enabled */
    #define Lumen_I2C_I2C_MULTI_MASTER \
                            (0u != (Lumen_I2C_I2C_MODE_MULTI_MASTER_MASK & Lumen_I2C_mode))

    /* Returns true if mode is multi-master-slave */
    #define Lumen_I2C_I2C_MULTI_MASTER_SLAVE \
                            (Lumen_I2C_I2C_MODE_MULTI_MASTER_SLAVE == Lumen_I2C_mode)

    /* Returns true if address accepts in RX FIFO */
    #define Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS   (0u != Lumen_I2C_acceptAddr)
    #define Lumen_I2C_CHECK_I2C_GENERAL_CALL \
                (0u != (Lumen_I2C_I2C_CTRL_REG & Lumen_I2C_I2C_CTRL_S_GENERAL_IGNORE))

    #define Lumen_I2C_I2C_WAKE_ENABLE_CONST              (1u)
    #define Lumen_I2C_I2C_SLAVE_CONST                    (1u)
    #define Lumen_I2C_I2C_MASTER_CONST                   (1u)
    #define Lumen_I2C_I2C_MULTI_MASTER_SLAVE_CONST       (1u)
    #define Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST     (1u)
    #define Lumen_I2C_CHECK_I2C_GENERAL_CALL_CONST       (1u)
    #define Lumen_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (1u)

    /* Returns FIFO size */
    #if (Lumen_I2C_CY_SCBIP_V0 || Lumen_I2C_CY_SCBIP_V1)
        #define Lumen_I2C_I2C_FIFO_SIZE      (Lumen_I2C_FIFO_SIZE)
    #else
        #define Lumen_I2C_I2C_FIFO_SIZE      (Lumen_I2C_GET_FIFO_SIZE(Lumen_I2C_CTRL_REG & \
                                                                                    Lumen_I2C_CTRL_BYTE_MODE))
    #endif /* (Lumen_I2C_CY_SCBIP_V0 || Lumen_I2C_CY_SCBIP_V1) */

#else

    /* Returns true if slave mode is enabled */
    #define Lumen_I2C_I2C_SLAVE   (0u != (Lumen_I2C_I2C_MODE_SLAVE & Lumen_I2C_I2C_MODE))

    /* Returns true if master mode is enabled */
    #define Lumen_I2C_I2C_MASTER  (0u != (Lumen_I2C_I2C_MODE_MASTER & Lumen_I2C_I2C_MODE))

    /* Returns true if multi-master mode is enabled */
    #define Lumen_I2C_I2C_MULTI_MASTER \
                                    (0u != (Lumen_I2C_I2C_MODE_MULTI_MASTER_MASK & Lumen_I2C_I2C_MODE))

    /* Returns true if mode is multi-master-slave */
    #define Lumen_I2C_I2C_MULTI_MASTER_SLAVE \
                                    (Lumen_I2C_I2C_MODE_MULTI_MASTER_SLAVE == Lumen_I2C_I2C_MODE)

    /* Returns true if address accepts in RX FIFO */
    #define Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS   (0u != Lumen_I2C_I2C_ACCEPT_ADDRESS)
    #define Lumen_I2C_CHECK_I2C_GENERAL_CALL     (0u != Lumen_I2C_I2C_ACCEPT_GENERAL_CALL)

    /* Returns true if wakeup on address match is enabled */
    #define Lumen_I2C_I2C_WAKE_ENABLE_CONST  (0u != Lumen_I2C_I2C_WAKE_ENABLE)

    #define Lumen_I2C_I2C_SLAVE_CONST    (Lumen_I2C_I2C_SLAVE)
    #define Lumen_I2C_I2C_MASTER_CONST   (Lumen_I2C_I2C_MASTER)
    #define Lumen_I2C_I2C_MULTI_MASTER_SLAVE_CONST   (Lumen_I2C_I2C_MULTI_MASTER_SLAVE)
    #define Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST (Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS)
    #define Lumen_I2C_CHECK_I2C_GENERAL_CALL_CONST   (Lumen_I2C_CHECK_I2C_GENERAL_CALL)
    #define Lumen_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST   (Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS_CONST || \
                                                                  Lumen_I2C_CHECK_I2C_GENERAL_CALL_CONST)

    /* I2C: TX or RX FIFO size */
    #if (Lumen_I2C_CY_SCBIP_V0 || Lumen_I2C_CY_SCBIP_V1)
        #define Lumen_I2C_I2C_FIFO_SIZE  (Lumen_I2C_FIFO_SIZE)
    #else
        #define Lumen_I2C_I2C_FIFO_SIZE  Lumen_I2C_GET_FIFO_SIZE(Lumen_I2C_I2C_BYTE_MODE_ENABLE)
    #endif /* (Lumen_I2C_CY_SCBIP_V0 || Lumen_I2C_CY_SCBIP_V1) */

    /* Adjust AF and DF filter settings. Ticket ID#176179 */
    #if ((Lumen_I2C_I2C_MODE_SLAVE == Lumen_I2C_I2C_MODE) ||     \
            ((Lumen_I2C_I2C_MODE_SLAVE != Lumen_I2C_I2C_MODE) && \
             (Lumen_I2C_I2C_DATA_RATE_ACTUAL <= Lumen_I2C_I2C_DATA_RATE_FS_MODE_MAX)))

        #define Lumen_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ       (0u)
        #define Lumen_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    do{;}while(0)
    #else
        #define Lumen_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ       (1u)
        #define Lumen_I2C_I2C_CFG_ANALOG_FITER_ENABLE_ADJ    Lumen_I2C_I2C_CFG_ANALOG_FITER_DISABLE
    #endif

    /* Select oversampling factor low and high */
    #define Lumen_I2C_I2C_OVS_FACTOR_LOW_MIN     ((0u != Lumen_I2C_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (8u) : (8u))

    #define Lumen_I2C_I2C_OVS_FACTOR_HIGH_MIN    ((0u != Lumen_I2C_I2C_MANUAL_OVS_CONTROL) ? \
                                                            (8u) : (8u))

#endif /* (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#define Lumen_I2C_I2C_CUSTOM_ADDRESS_HANDLER (Lumen_I2C_CHECK_I2C_GENERAL_CALL || \
                                                     Lumen_I2C_CHECK_I2C_ACCEPT_ADDRESS)


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint32 mode;
    uint32 oversampleLow;
    uint32 oversampleHigh;
    uint32 enableMedianFilter;
    uint32 slaveAddr;
    uint32 slaveAddrMask;
    uint32 acceptAddr;
    uint32 enableWake;
    uint8  enableByteMode;
    uint16 dataRate;
    uint8  acceptGeneralAddr;
} Lumen_I2C_I2C_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Common functions */
#if(Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    void Lumen_I2C_I2CInit(const Lumen_I2C_I2C_INIT_STRUCT *config);
#endif /* (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (Lumen_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    void Lumen_I2C_SetI2cAddressCustomInterruptHandler(uint32 (*func) (void));
#endif /* (Lumen_I2C_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/* I2C Master functions prototypes */
#if(Lumen_I2C_I2C_MASTER_CONST)
    /* Read and Clear status functions */
    uint32 Lumen_I2C_I2CMasterStatus(void);
    uint32 Lumen_I2C_I2CMasterClearStatus(void);

    /* Interrupt based operation functions */
    uint32 Lumen_I2C_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode);
    uint32 Lumen_I2C_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode);
    uint32 Lumen_I2C_I2CMasterGetReadBufSize(void);
    uint32 Lumen_I2C_I2CMasterGetWriteBufSize(void);
    void   Lumen_I2C_I2CMasterClearReadBuf(void);
    void   Lumen_I2C_I2CMasterClearWriteBuf(void);

    /* Manual operation functions */
    uint32 Lumen_I2C_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW);
    uint32 Lumen_I2C_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW);
    uint32 Lumen_I2C_I2CMasterSendStop(void);
    uint32 Lumen_I2C_I2CMasterWriteByte(uint32 theByte);
    uint32 Lumen_I2C_I2CMasterReadByte(uint32 ackNack);
#endif /* (Lumen_I2C_I2C_MASTER_CONST) */

/* I2C Slave functions prototypes */
#if(Lumen_I2C_I2C_SLAVE_CONST)
    /* Read and Clear status functions */
    uint32 Lumen_I2C_I2CSlaveStatus(void);
    uint32 Lumen_I2C_I2CSlaveClearReadStatus(void);
    uint32 Lumen_I2C_I2CSlaveClearWriteStatus(void);

    /* Set Slave address and mask */
    void   Lumen_I2C_I2CSlaveSetAddress(uint32 address);
    void   Lumen_I2C_I2CSlaveSetAddressMask(uint32 addressMask);

    /* Interrupt based operation functions */
    void   Lumen_I2C_I2CSlaveInitReadBuf(uint8 * rdBuf, uint32 bufSize);
    void   Lumen_I2C_I2CSlaveInitWriteBuf(uint8 * wrBuf, uint32 bufSize);
    uint32 Lumen_I2C_I2CSlaveGetReadBufSize(void);
    uint32 Lumen_I2C_I2CSlaveGetWriteBufSize(void);
    void   Lumen_I2C_I2CSlaveClearReadBuf(void);
    void   Lumen_I2C_I2CSlaveClearWriteBuf(void);
#endif /* (Lumen_I2C_I2C_SLAVE_CONST) */

CY_ISR_PROTO(Lumen_I2C_I2C_ISR);


/***************************************
*            API Constants
***************************************/

/* I2C sub mode enum */
#define Lumen_I2C_I2C_MODE_SLAVE              (0x01u)
#define Lumen_I2C_I2C_MODE_MASTER             (0x02u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER       (0x06u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define Lumen_I2C_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

/* Master/Slave control constants */
#define Lumen_I2C_I2C_WRITE_XFER_MODE    (0u)    /* Write    */
#define Lumen_I2C_I2C_READ_XFER_MODE     (1u)    /* Read     */
#define Lumen_I2C_I2C_ACK_ADDR           (0u)    /* Send ACK to address */
#define Lumen_I2C_I2C_NAK_ADDR           (1u)    /* Send NAK to address */
#define Lumen_I2C_I2C_ACK_DATA           (0u)    /* Send ACK to data */
#define Lumen_I2C_I2C_NAK_DATA           (1u)    /* Send NAK to data */

/* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
#define Lumen_I2C_I2C_MODE_COMPLETE_XFER     (0x00u)    /* Full transfer with Start and Stop       */
#define Lumen_I2C_I2C_MODE_REPEAT_START      (0x01u)    /* Begin with a ReStart instead of a Start */
#define Lumen_I2C_I2C_MODE_NO_STOP           (0x02u)    /* Complete the transfer without a Stop    */

/* Master status */
#define Lumen_I2C_I2C_MSTAT_CLEAR            ((uint16) 0x00u)   /* Clear (init) status value */

#define Lumen_I2C_I2C_MSTAT_RD_CMPLT         ((uint16) 0x01u)   /* Read complete               */
#define Lumen_I2C_I2C_MSTAT_WR_CMPLT         ((uint16) 0x02u)   /* Write complete              */
#define Lumen_I2C_I2C_MSTAT_XFER_INP         ((uint16) 0x04u)   /* Master transfer in progress */
#define Lumen_I2C_I2C_MSTAT_XFER_HALT        ((uint16) 0x08u)   /* Transfer is halted          */

#define Lumen_I2C_I2C_MSTAT_ERR_MASK         ((uint16) 0x3F0u) /* Mask for all errors                          */
#define Lumen_I2C_I2C_MSTAT_ERR_SHORT_XFER   ((uint16) 0x10u)  /* Master NAKed before end of packet            */
#define Lumen_I2C_I2C_MSTAT_ERR_ADDR_NAK     ((uint16) 0x20u)  /* Slave did not ACK                            */
#define Lumen_I2C_I2C_MSTAT_ERR_ARB_LOST     ((uint16) 0x40u)  /* Master lost arbitration during communication */
#define Lumen_I2C_I2C_MSTAT_ERR_ABORT_XFER   ((uint16) 0x80u)  /* The Slave was addressed before the Start gen */
#define Lumen_I2C_I2C_MSTAT_ERR_BUS_ERROR    ((uint16) 0x100u) /* The misplaced Start or Stop was occurred     */
#define Lumen_I2C_I2C_MSTAT_ERR_XFER         ((uint16) 0x200u) /* Error during transfer                        */

/* Master API returns */
#define Lumen_I2C_I2C_MSTR_NO_ERROR          (0x00u)  /* Function complete without error                       */
#define Lumen_I2C_I2C_MSTR_ERR_ARB_LOST      (0x01u)  /* Master lost arbitration: INTR_MASTER_I2C_ARB_LOST     */
#define Lumen_I2C_I2C_MSTR_ERR_LB_NAK        (0x02u)  /* Last Byte Naked: INTR_MASTER_I2C_NACK                 */
#define Lumen_I2C_I2C_MSTR_NOT_READY         (0x04u)  /* Master on the bus or Slave operation is in progress   */
#define Lumen_I2C_I2C_MSTR_BUS_BUSY          (0x08u)  /* Bus is busy, process not started                      */
#define Lumen_I2C_I2C_MSTR_ERR_ABORT_START   (0x10u)  /* Slave was addressed before master begin Start gen     */
#define Lumen_I2C_I2C_MSTR_ERR_BUS_ERR       (0x100u) /* Bus error has: INTR_MASTER_I2C_BUS_ERROR              */

/* Slave Status Constants */
#define Lumen_I2C_I2C_SSTAT_RD_CMPLT         (0x01u)    /* Read transfer complete                        */
#define Lumen_I2C_I2C_SSTAT_RD_BUSY          (0x02u)    /* Read transfer in progress                     */
#define Lumen_I2C_I2C_SSTAT_RD_OVFL          (0x04u)    /* Read overflow: master reads above buffer size */
#define Lumen_I2C_I2C_SSTAT_RD_ERR           (0x08u)    /* Read was interrupted by misplaced Start/Stop  */
#define Lumen_I2C_I2C_SSTAT_RD_MASK          (0x0Fu)    /* Read Status Mask                              */
#define Lumen_I2C_I2C_SSTAT_RD_NO_ERR        (0x00u)    /* Read no Error                                 */

#define Lumen_I2C_I2C_SSTAT_WR_CMPLT         (0x10u)    /* Write transfer complete                         */
#define Lumen_I2C_I2C_SSTAT_WR_BUSY          (0x20u)    /* Write transfer in progress                      */
#define Lumen_I2C_I2C_SSTAT_WR_OVFL          (0x40u)    /* Write overflow: master writes above buffer size */
#define Lumen_I2C_I2C_SSTAT_WR_ERR           (0x80u)    /* Write was interrupted by misplaced Start/Stop   */
#define Lumen_I2C_I2C_SSTAT_WR_MASK          (0xF0u)    /* Write Status Mask                               */
#define Lumen_I2C_I2C_SSTAT_WR_NO_ERR        (0x00u)    /* Write no Error                                  */

#define Lumen_I2C_I2C_SSTAT_RD_CLEAR         (0x0Du)    /* Read Status clear: do not clear */
#define Lumen_I2C_I2C_SSTAT_WR_CLEAR         (0xD0u)    /* Write Status Clear */

/* Internal I2C component constants */
#define Lumen_I2C_I2C_READ_FLAG              (0x01u)     /* Read flag of the Address */
#define Lumen_I2C_I2C_SLAVE_OVFL_RETURN      (0xFFu)     /* Return by slave when overflow */

#define Lumen_I2C_I2C_RESET_ERROR            (0x01u)     /* Flag to re-enable SCB IP */


/***************************************
*     Vars with External Linkage
***************************************/

#if(Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const Lumen_I2C_I2C_INIT_STRUCT Lumen_I2C_configI2C;
#endif /* (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*           FSM states
***************************************/

#define Lumen_I2C_I2C_FSM_EXIT_IDLE      (0x00u) /* Master and Slave are not active, need to exit to IDLE */

/* Slave mode FSM states */
#define Lumen_I2C_I2C_FSM_IDLE           (0x10u) /* Idle I2C state                */
#define Lumen_I2C_I2C_FSM_SLAVE          (0x10u) /* Slave mask for all its states */

#define Lumen_I2C_I2C_FSM_SL_WR          (0x11u) /* Slave write states */
#define Lumen_I2C_I2C_FSM_SL_RD          (0x12u) /* Slave read  states */

/* Master mode FSM states */
#define Lumen_I2C_I2C_FSM_MASTER         (0x20u) /* Master mask for all its states */
#define Lumen_I2C_I2C_FSM_MSTR_ADDR      (0x08u) /* Master address phase           */
#define Lumen_I2C_I2C_FSM_MSTR_DATA      (0x04u) /* Master data phase              */
#define Lumen_I2C_I2C_FSM_MSTR_RD        (0x01u) /* Master read phase              */

#define Lumen_I2C_I2C_FSM_MSTR_WR_ADDR   (0x28u) /* FSM master transmit address with write          */
#define Lumen_I2C_I2C_FSM_MSTR_RD_ADDR   (0x29u) /* FSM master transmit address with read           */
#define Lumen_I2C_I2C_FSM_MSTR_WR_DATA   (0x24u) /* FSM master writes data into the slave           */
#define Lumen_I2C_I2C_FSM_MSTR_RD_DATA   (0x25u) /* FSM master reads data from the slave            */
#define Lumen_I2C_I2C_FSM_MSTR_HALT      (0x60u) /* FSM master halt state: wait for Stop or ReStart */

/* Requests to complete any on-going transfer */
#define Lumen_I2C_I2C_CMPLT_ANY_TRANSFER     (0x01u)

/* Returns true if FSM is in any Master state */
#define Lumen_I2C_CHECK_I2C_FSM_MASTER   (0u != (Lumen_I2C_I2C_FSM_MASTER & Lumen_I2C_state))

/* Returns true if FSM is in any Slave state */
#define Lumen_I2C_CHECK_I2C_FSM_SLAVE    (0u != (Lumen_I2C_I2C_FSM_SLAVE  & Lumen_I2C_state))

/* Returns true if FSM is in Master send address state */
#define Lumen_I2C_CHECK_I2C_FSM_ADDR (0u != (Lumen_I2C_I2C_FSM_MSTR_ADDR & Lumen_I2C_state))

/* Returns true if FSM is in Master send or receive data state */
#define Lumen_I2C_CHECK_I2C_FSM_DATA (0u != (Lumen_I2C_I2C_FSM_MSTR_DATA  & Lumen_I2C_state))

/* Returns true if FSM is in any of read states: applied for Slave and Master */
#define Lumen_I2C_CHECK_I2C_FSM_RD   (0u != (Lumen_I2C_I2C_FSM_MSTR_RD  & Lumen_I2C_state))

/* Returns true if FSM is in IDLE state */
#define Lumen_I2C_CHECK_I2C_FSM_IDLE (Lumen_I2C_I2C_FSM_IDLE == Lumen_I2C_state)

/* Returns true if FSM is HALT state */
#define Lumen_I2C_CHECK_I2C_FSM_HALT (Lumen_I2C_I2C_FSM_MSTR_HALT == Lumen_I2C_state)

/* Set Master read or write completion depends on state */
#define Lumen_I2C_GET_I2C_MSTAT_CMPLT (Lumen_I2C_CHECK_I2C_FSM_RD ?           \
                                                    (Lumen_I2C_I2C_MSTAT_RD_CMPLT) : \
                                                    (Lumen_I2C_I2C_MSTAT_WR_CMPLT))


/***************************************
*       Macro Definitions
***************************************/

/* Returns TRUE if sourceMask is set in Lumen_I2C_I2C_MASTER_CMD_REG: used to check if Start was generated */
#define Lumen_I2C_CHECK_I2C_MASTER_CMD(sourceMask)   (0u != (Lumen_I2C_I2C_MASTER_CMD_REG & (sourceMask)))

/* Returns TRUE if Lumen_I2C_MODE_NO_STOP is set in Lumen_I2C_mstrControl: detects NoStop condition */
#define Lumen_I2C_CHECK_I2C_MODE_NO_STOP(mode)   (0u != (Lumen_I2C_I2C_MODE_NO_STOP & (mode)))

/* Returns TRUE if Lumen_I2C_MODE_REPEAT_START is set: used to detect when generate ReStart condition */
#define Lumen_I2C_CHECK_I2C_MODE_RESTART(mode)   (0u != (Lumen_I2C_I2C_MODE_REPEAT_START  & (mode)))

/* Returns TRUE if Lumen_I2C_state is in one of master states */
#define Lumen_I2C_CHECK_I2C_MASTER_ACTIVE    (Lumen_I2C_CHECK_I2C_FSM_MASTER)


/***************************************
*      Common Register Settings
***************************************/

#define Lumen_I2C_CTRL_I2C       (Lumen_I2C_CTRL_MODE_I2C)

#define Lumen_I2C_I2C_CTRL       (Lumen_I2C_I2C_CTRL_S_GENERAL_IGNORE)

#define Lumen_I2C_I2C_RX_CTRL    ((Lumen_I2C_FIFO_SIZE - 1u)  | \
                                         Lumen_I2C_RX_CTRL_MSB_FIRST | \
                                         Lumen_I2C_RX_CTRL_ENABLED)

#define Lumen_I2C_I2C_TX_CTRL    ((Lumen_I2C_FIFO_SIZE - 1u)  | \
                                         Lumen_I2C_TX_CTRL_MSB_FIRST | \
                                         Lumen_I2C_TX_CTRL_ENABLED)

#define Lumen_I2C_I2C_INTR_SLAVE_MASK    (Lumen_I2C_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                 Lumen_I2C_INTR_SLAVE_I2C_NACK       | \
                                                 Lumen_I2C_INTR_SLAVE_I2C_WRITE_STOP | \
                                                 Lumen_I2C_INTR_SLAVE_I2C_BUS_ERROR  | \
                                                 Lumen_I2C_INTR_SLAVE_I2C_ARB_LOST)

#define Lumen_I2C_I2C_INTR_MASTER_MASK   (Lumen_I2C_INTR_MASTER_I2C_ARB_LOST | \
                                                 Lumen_I2C_INTR_MASTER_I2C_NACK     | \
                                                 Lumen_I2C_INTR_MASTER_I2C_STOP     | \
                                                 Lumen_I2C_INTR_MASTER_I2C_BUS_ERROR)

/* Calculates tLOW in uS units */
#define Lumen_I2C_I2C_TLOW_TIME  ((1000u / Lumen_I2C_I2C_DATA_RATE) + \
                                            ((0u != (1000u % Lumen_I2C_I2C_DATA_RATE)) ? (1u) : (0u)))
/* tHIGH = tLOW */
#define Lumen_I2C_I2C_THIGH_TIME (Lumen_I2C_I2C_TLOW_TIME)

#define Lumen_I2C_I2C_SCL_LOW    (0u)
#define Lumen_I2C_I2C_SCL_HIGH   (1u)

#define Lumen_I2C_I2C_IGNORE_GENERAL_CALL    ((uint32) (0u == Lumen_I2C_I2C_ACCEPT_GENERAL_CALL))


/***************************************
*    Initialization Register Settings
***************************************/

#if(Lumen_I2C_SCB_MODE_I2C_CONST_CFG)

    #if (!Lumen_I2C_CY_SCBIP_V0)
        #define Lumen_I2C_I2C_WAKE_ENABLE_ADJ    (Lumen_I2C_I2C_MULTI_MASTER_SLAVE ? \
                                                            (0u) : (Lumen_I2C_I2C_WAKE_ENABLE))
    #else
        #define Lumen_I2C_I2C_WAKE_ENABLE_ADJ    (Lumen_I2C_I2C_WAKE_ENABLE)
    #endif /* (!Lumen_I2C_CY_SCBIP_V0) */

    #define Lumen_I2C_I2C_MODE_MASKED    (Lumen_I2C_I2C_MODE & \
                                                (Lumen_I2C_I2C_MODE_SLAVE | Lumen_I2C_I2C_MODE_MASTER))

    #define Lumen_I2C_I2C_DEFAULT_CTRL \
                                (Lumen_I2C_GET_CTRL_BYTE_MODE  (Lumen_I2C_I2C_BYTE_MODE_ENABLE) | \
                                 Lumen_I2C_GET_CTRL_ADDR_ACCEPT(Lumen_I2C_I2C_ACCEPT_ADDRESS)   | \
                                 Lumen_I2C_GET_CTRL_EC_AM_MODE (Lumen_I2C_I2C_WAKE_ENABLE_ADJ))

    #define Lumen_I2C_I2C_DEFAULT_I2C_CTRL \
                    (Lumen_I2C_GET_I2C_CTRL_HIGH_PHASE_OVS(Lumen_I2C_I2C_OVS_FACTOR_HIGH_MIN)   | \
                     Lumen_I2C_GET_I2C_CTRL_LOW_PHASE_OVS (Lumen_I2C_I2C_OVS_FACTOR_LOW_MIN)    | \
                     Lumen_I2C_GET_I2C_CTRL_S_GENERAL_IGNORE(Lumen_I2C_I2C_IGNORE_GENERAL_CALL) | \
                     Lumen_I2C_GET_I2C_CTRL_SL_MSTR_MODE  (Lumen_I2C_I2C_MODE_MASKED))

    #define Lumen_I2C_I2C_DEFAULT_RX_MATCH ((Lumen_I2C_I2C_SLAVE) ? \
                                (Lumen_I2C_GET_I2C_8BIT_ADDRESS(Lumen_I2C_I2C_SLAVE_ADDRESS) | \
                                 Lumen_I2C_GET_RX_MATCH_MASK   (Lumen_I2C_I2C_SLAVE_ADDRESS_MASK)) : (0u))

    #define Lumen_I2C_I2C_DEFAULT_RX_CTRL \
                                (Lumen_I2C_GET_RX_CTRL_MEDIAN(Lumen_I2C_I2C_MEDIAN_FILTER_ENABLE_ADJ) | \
                                 Lumen_I2C_I2C_RX_CTRL)

    #define Lumen_I2C_I2C_DEFAULT_TX_CTRL  (Lumen_I2C_I2C_TX_CTRL)

    #define Lumen_I2C_I2C_DEFAULT_RX_FIFO_CTRL (0u)
    #define Lumen_I2C_I2C_DEFAULT_TX_FIFO_CTRL (0u)

    /* Interrupt sources */
    #define Lumen_I2C_I2C_DEFAULT_INTR_I2C_EC_MASK   (Lumen_I2C_NO_INTR_SOURCES)
    #define Lumen_I2C_I2C_DEFAULT_INTR_SPI_EC_MASK   (Lumen_I2C_NO_INTR_SOURCES)
    #define Lumen_I2C_I2C_DEFAULT_INTR_RX_MASK       (Lumen_I2C_NO_INTR_SOURCES)
    #define Lumen_I2C_I2C_DEFAULT_INTR_TX_MASK       (Lumen_I2C_NO_INTR_SOURCES)

    #define Lumen_I2C_I2C_DEFAULT_INTR_SLAVE_MASK    ((Lumen_I2C_I2C_SLAVE) ? \
                (Lumen_I2C_I2C_INTR_SLAVE_MASK | \
                 Lumen_I2C_GET_INTR_SLAVE_I2C_GENERAL(Lumen_I2C_I2C_ACCEPT_GENERAL_CALL)) : (0u))

    #define Lumen_I2C_I2C_DEFAULT_INTR_MASTER_MASK   ((Lumen_I2C_I2C_MASTER) ? \
                                                                (Lumen_I2C_I2C_INTR_MASTER_MASK) : (0u))

#endif /* (Lumen_I2C_SCB_MODE_I2C_CONST_CFG) */

#endif /* (CY_SCB_I2C_Lumen_I2C_H) */


/* [] END OF FILE */
