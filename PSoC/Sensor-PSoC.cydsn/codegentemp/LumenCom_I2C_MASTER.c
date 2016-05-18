/*******************************************************************************
* File Name: LumenCom_I2C_MASTER.c
* Version 3.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  I2C Master mode.
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

#if(LumenCom_I2C_MASTER_CONST)

/***************************************
*      I2C Master Private Vars
***************************************/

/* Master variables */
volatile uint16 LumenCom_mstrStatus;      /* Master Status byte  */
volatile uint8  LumenCom_mstrControl;     /* Master Control byte */

/* Receive buffer variables */
volatile uint8 * LumenCom_mstrRdBufPtr;   /* Pointer to Master Read buffer */
volatile uint32  LumenCom_mstrRdBufSize;  /* Master Read buffer size       */
volatile uint32  LumenCom_mstrRdBufIndex; /* Master Read buffer Index      */

/* Transmit buffer variables */
volatile uint8 * LumenCom_mstrWrBufPtr;   /* Pointer to Master Write buffer */
volatile uint32  LumenCom_mstrWrBufSize;  /* Master Write buffer size       */
volatile uint32  LumenCom_mstrWrBufIndex; /* Master Write buffer Index      */
volatile uint32  LumenCom_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */

#if (!LumenCom_CY_SCBIP_V0 && \
    LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
    static void LumenCom_I2CMasterDisableEcAm(void);
#endif /* (!LumenCom_CY_SCBIP_V0) */


/*******************************************************************************
* Function Name: LumenCom_I2CMasterWriteBuf
********************************************************************************
*
* Summary:
* Automatically writes an entire buffer of data to a slave device.
* Once the data transfer is initiated by this function, further data transfer
* is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_WR_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer of data to be sent.
*  cnt:       Size of buffer to send.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  LumenCom_mstrStatus  - used to store current status of I2C Master.
*  LumenCom_state       - used to store current state of software FSM.
*  LumenCom_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  LumenCom_mstrWrBufPtr - used to store pointer to master write buffer.
*  LumenCom_mstrWrBufIndex - used to current index within master write
*  buffer.
*  LumenCom_mstrWrBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    if(NULL != wrData)  /* Check buffer pointer */
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(LumenCom_CHECK_I2C_FSM_IDLE)
        {
            LumenCom_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = LumenCom_CHECK_I2C_STATUS(LumenCom_I2C_STATUS_BUS_BUSY) ?
                            LumenCom_I2C_MSTR_BUS_BUSY : LumenCom_I2C_MSTR_NO_ERROR;
        }
        else if(LumenCom_CHECK_I2C_FSM_HALT)
        {
            LumenCom_mstrStatus &= (uint16) ~LumenCom_I2C_MSTAT_XFER_HALT;
                              errStatus  = LumenCom_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check if master is ready to start  */
    if(LumenCom_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
    #if (!LumenCom_CY_SCBIP_V0 && \
        LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
            LumenCom_I2CMasterDisableEcAm();
    #endif /* (!LumenCom_CY_SCBIP_V0) */

        /* Set up write transaction */
        LumenCom_state = LumenCom_I2C_FSM_MSTR_WR_ADDR;
        LumenCom_mstrWrBufIndexTmp = 0u;
        LumenCom_mstrWrBufIndex    = 0u;
        LumenCom_mstrWrBufSize     = cnt;
        LumenCom_mstrWrBufPtr      = (volatile uint8 *) wrData;
        LumenCom_mstrControl       = (uint8) mode;

        slaveAddress = LumenCom_GET_I2C_8BIT_ADDRESS(slaveAddress);

        LumenCom_mstrStatus &= (uint16) ~LumenCom_I2C_MSTAT_WR_CMPLT;

        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_ALL);
        LumenCom_ClearTxInterruptSource(LumenCom_INTR_TX_UNDERFLOW);

        /* The TX and RX FIFO have to be EMPTY */

        /* Enable interrupt source to catch when address is sent */
        LumenCom_SetTxInterruptMode(LumenCom_INTR_TX_UNDERFLOW);

        /* Generate Start or ReStart */
        if(LumenCom_CHECK_I2C_MODE_RESTART(mode))
        {
            LumenCom_I2C_MASTER_GENERATE_RESTART;
            LumenCom_TX_FIFO_WR_REG = slaveAddress;
        }
        else
        {
            LumenCom_TX_FIFO_WR_REG = slaveAddress;
            LumenCom_I2C_MASTER_GENERATE_START;
        }
    }

    LumenCom_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterReadBuf
********************************************************************************
*
* Summary:
*  Automatically reads an entire buffer of data from a slave device.
*  Once the data transfer is initiated by this function, further data transfer
*  is handled by the included ISR.
* Enables the I2C interrupt and clears SCB_ I2C_MSTAT_RD_CMPLT status.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer where to put data from slave.
*  cnt:       Size of buffer to read.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Error status.
*
* Global variables:
*  LumenCom_mstrStatus  - used to store current status of I2C Master.
*  LumenCom_state       - used to store current state of software FSM.
*  LumenCom_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  LumenCom_mstrRdBufPtr - used to store pointer to master write buffer.
*  LumenCom_mstrRdBufIndex - used to current index within master write
*  buffer.
*  LumenCom_mstrRdBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check FSM state and bus before generating Start/ReStart condition */
        if(LumenCom_CHECK_I2C_FSM_IDLE)
        {
            LumenCom_DisableInt();  /* Lock from interruption */

            /* Check bus state */
            errStatus = LumenCom_CHECK_I2C_STATUS(LumenCom_I2C_STATUS_BUS_BUSY) ?
                            LumenCom_I2C_MSTR_BUS_BUSY : LumenCom_I2C_MSTR_NO_ERROR;
        }
        else if(LumenCom_CHECK_I2C_FSM_HALT)
        {
            LumenCom_mstrStatus &= (uint16) ~LumenCom_I2C_MSTAT_XFER_HALT;
                              errStatus  =  LumenCom_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check master ready to proceed */
    if(LumenCom_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        #if (!LumenCom_CY_SCBIP_V0 && \
        LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
            LumenCom_I2CMasterDisableEcAm();
        #endif /* (!LumenCom_CY_SCBIP_V0) */

        /* Set up read transaction */
        LumenCom_state = LumenCom_I2C_FSM_MSTR_RD_ADDR;
        LumenCom_mstrRdBufIndex = 0u;
        LumenCom_mstrRdBufSize  = cnt;
        LumenCom_mstrRdBufPtr   = (volatile uint8 *) rdData;
        LumenCom_mstrControl    = (uint8) mode;

        slaveAddress = (LumenCom_GET_I2C_8BIT_ADDRESS(slaveAddress) | LumenCom_I2C_READ_FLAG);

        LumenCom_mstrStatus &= (uint16) ~LumenCom_I2C_MSTAT_RD_CMPLT;

        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_ALL);

        /* TX and RX FIFO have to be EMPTY */

        /* Prepare reading */
        if(LumenCom_mstrRdBufSize < LumenCom_I2C_FIFO_SIZE)
        {
            /* Reading byte-by-byte */
            LumenCom_SetRxInterruptMode(LumenCom_INTR_RX_NOT_EMPTY);
        }
        else
        {
            /* Receive RX FIFO chunks */
            LumenCom_ENABLE_MASTER_AUTO_DATA_ACK;
            LumenCom_SetRxInterruptMode(LumenCom_INTR_RX_FULL);
        }

        /* Generate Start or ReStart */
        if(LumenCom_CHECK_I2C_MODE_RESTART(mode))
        {
            LumenCom_I2C_MASTER_GENERATE_RESTART;
            LumenCom_TX_FIFO_WR_REG = (slaveAddress);
        }
        else
        {
            LumenCom_TX_FIFO_WR_REG = (slaveAddress);
            LumenCom_I2C_MASTER_GENERATE_START;
        }
    }

    LumenCom_EnableInt();   /* Release lock */

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterSendStart
********************************************************************************
*
* Summary:
*  Generates Start condition and sends slave address with read/write bit.
*  Disables the I2C interrupt.
*  This function is blocking and does not return until start condition and
*  address byte are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Error status.
*
* Global variables:
*  LumenCom_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterSendStart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32  resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Start condition */
    if(LumenCom_CHECK_I2C_FSM_IDLE)
    {
        /* If bus is free, generate Start condition */
        if(LumenCom_CHECK_I2C_STATUS(LumenCom_I2C_STATUS_BUS_BUSY))
        {
            errStatus = LumenCom_I2C_MSTR_BUS_BUSY;
        }
        else
        {
            LumenCom_DisableInt();  /* Lock from interruption */

        #if (!LumenCom_CY_SCBIP_V0 && \
            LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
            LumenCom_I2CMasterDisableEcAm();
        #endif /* (!LumenCom_CY_SCBIP_V0) */

            slaveAddress = LumenCom_GET_I2C_8BIT_ADDRESS(slaveAddress);

            if(0u == bitRnW) /* Write direction */
            {
                LumenCom_state = LumenCom_I2C_FSM_MSTR_WR_DATA;
            }
            else /* Read direction */
            {
                LumenCom_state = LumenCom_I2C_FSM_MSTR_RD_DATA;
                         slaveAddress |= LumenCom_I2C_READ_FLAG;
            }

            /* TX and RX FIFO have to be EMPTY */

            LumenCom_TX_FIFO_WR_REG = slaveAddress; /* Put address in TX FIFO */
            LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_ALL);

            LumenCom_I2C_MASTER_GENERATE_START;


            while(!LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK      |
                                                      LumenCom_INTR_MASTER_I2C_NACK     |
                                                      LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                      LumenCom_INTR_MASTER_I2C_BUS_ERROR))
            {
                /*
                * Write: wait until address has been transferred
                * Read : wait until address has been transferred, data byte is going to RX FIFO as well.
                */
            }

            /* Check the results of the address phase */
            if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK))
            {
                errStatus = LumenCom_I2C_MSTR_NO_ERROR;
            }
            else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_NACK))
            {
                errStatus = LumenCom_I2C_MSTR_ERR_LB_NAK;
            }
            else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ARB_LOST))
            {
                LumenCom_state = LumenCom_I2C_FSM_IDLE;
                             errStatus = LumenCom_I2C_MSTR_ERR_ARB_LOST;
                             resetIp   = LumenCom_I2C_RESET_ERROR;
            }
            else /* LumenCom_INTR_MASTER_I2C_BUS_ERROR set is else condition */
            {
                LumenCom_state = LumenCom_I2C_FSM_IDLE;
                             errStatus = LumenCom_I2C_MSTR_ERR_BUS_ERR;
                             resetIp   = LumenCom_I2C_RESET_ERROR;
            }

            LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_I2C_ACK      |
                                                        LumenCom_INTR_MASTER_I2C_NACK     |
                                                        LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                        LumenCom_INTR_MASTER_I2C_BUS_ERROR);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            if(0u != resetIp)
            {
                LumenCom_SCB_SW_RESET;
            }
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterSendRestart
********************************************************************************
*
* Summary:
*  Generates Restart condition and sends slave address with read/write bit.
*  This function is blocking and does not return until start condition and
*  address are sent and ACK/NACK response is received or errors occurred.
*
* Parameters:
*  slaveAddress: Right justified 7-bit Slave address (valid range 8 to 120).
*  bitRnW:       Direction of the following transfer. It is defined by
*                read/write bit within address byte.
*
* Return:
*  Error status
*
*
* Global variables:
*  LumenCom_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterSendRestart(uint32 slaveAddress, uint32 bitRnW)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating ReStart condition */
    if(LumenCom_CHECK_I2C_MASTER_ACTIVE)
    {
        slaveAddress = LumenCom_GET_I2C_8BIT_ADDRESS(slaveAddress);

        if(0u == bitRnW) /* Write direction */
        {
            LumenCom_state = LumenCom_I2C_FSM_MSTR_WR_DATA;
        }
        else  /* Read direction */
        {
            LumenCom_state  = LumenCom_I2C_FSM_MSTR_RD_DATA;
                      slaveAddress |= LumenCom_I2C_READ_FLAG;
        }

        /* TX and RX FIFO have to be EMPTY */

        /* Clean-up interrupt status */
        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_ALL);

        /* A proper ReStart sequence is: generate ReStart, then put an address byte in the TX FIFO.
        * Otherwise the master treats the address in the TX FIFO as a data byte if a previous transfer is write.
        * The write transfer continues instead of ReStart.
        */
        LumenCom_I2C_MASTER_GENERATE_RESTART;

        while(LumenCom_CHECK_I2C_MASTER_CMD(LumenCom_I2C_MASTER_CMD_M_START))
        {
            /* Wait until ReStart has been generated */
        }

        /* Put address into TX FIFO */
        LumenCom_TX_FIFO_WR_REG = slaveAddress;

        /* Wait for address to be transferred */
        while(!LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK      |
                                                  LumenCom_INTR_MASTER_I2C_NACK     |
                                                  LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                  LumenCom_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until address has been transferred */
        }

        /* Check results of address phase */
        if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK))
        {
            errStatus = LumenCom_I2C_MSTR_NO_ERROR;
        }
        else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_NACK))
        {
             errStatus = LumenCom_I2C_MSTR_ERR_LB_NAK;
        }
        else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ARB_LOST))
        {
            LumenCom_state = LumenCom_I2C_FSM_IDLE;
                         errStatus = LumenCom_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = LumenCom_I2C_RESET_ERROR;
        }
        else /* LumenCom_INTR_MASTER_I2C_BUS_ERROR set is else condition */
        {
            LumenCom_state = LumenCom_I2C_FSM_IDLE;
                         errStatus = LumenCom_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = LumenCom_I2C_RESET_ERROR;
        }

        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_I2C_ACK      |
                                                    LumenCom_INTR_MASTER_I2C_NACK     |
                                                    LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                    LumenCom_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            LumenCom_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterSendStop
********************************************************************************
*
* Summary:
*  Generates Stop condition on the bus.
*  At least one byte has to be read if start or restart condition with read
*  direction was generated before.
*  This function is blocking and does not return until a stop condition
*  is generated or error occurred.
*
* Parameters:
*  None
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*  For read transfer, at least one byte has to be read before Stop generation.
*
* Global variables:
*  LumenCom_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterSendStop(void)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    /* Check FSM state before generating Stop condition */
    if(LumenCom_CHECK_I2C_MASTER_ACTIVE)
    {
        /*
        * Write direction: generates Stop
        * Read  direction: generates NACK and Stop
        */
        LumenCom_I2C_MASTER_GENERATE_STOP;

        while(!LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_STOP     |
                                                  LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                  LumenCom_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until Stop has been generated */
        }

        /* Check Stop generation */
        if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_STOP))
        {
            errStatus = LumenCom_I2C_MSTR_NO_ERROR;
        }
        else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ARB_LOST))
        {
            errStatus = LumenCom_I2C_MSTR_ERR_ARB_LOST;
            resetIp   = LumenCom_I2C_RESET_ERROR;
        }
        else /* LumenCom_INTR_MASTER_I2C_BUS_ERROR is set */
        {
            errStatus = LumenCom_I2C_MSTR_ERR_BUS_ERR;
            resetIp   = LumenCom_I2C_RESET_ERROR;
        }

        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_I2C_STOP     |
                                                    LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                    LumenCom_INTR_MASTER_I2C_BUS_ERROR);

        LumenCom_state = LumenCom_I2C_FSM_IDLE;

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            LumenCom_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterWriteByte
********************************************************************************
*
* Summary:
*  Sends one byte to a slave.
*  This function is blocking and does not return until byte is transmitted
*  or error occurred.
*
* Parameters:
*  data: The data byte to send to the slave.
*
* Return:
*  Error status
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling
*  this function. This function does nothing if Start or ReStart condition
*  failed before this function was called.
*
* Global variables:
*  LumenCom_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterWriteByte(uint32 theByte)
{
    uint32 resetIp;
    uint32 errStatus;

    resetIp   = 0u;
    errStatus = LumenCom_I2C_MSTR_NOT_READY;

    /* Check FSM state before write byte */
    if(LumenCom_CHECK_I2C_MASTER_ACTIVE)
    {
        LumenCom_TX_FIFO_WR_REG = theByte;

        while(!LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK      |
                                                  LumenCom_INTR_MASTER_I2C_NACK     |
                                                  LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                  LumenCom_INTR_MASTER_I2C_BUS_ERROR))
        {
            /* Wait until byte has been transferred */
        }

        /* Check results after byte was sent */
        if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ACK))
        {
            LumenCom_state = LumenCom_I2C_FSM_MSTR_HALT;
                         errStatus = LumenCom_I2C_MSTR_NO_ERROR;
        }
        else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_NACK))
        {
            LumenCom_state = LumenCom_I2C_FSM_MSTR_HALT;
                         errStatus = LumenCom_I2C_MSTR_ERR_LB_NAK;
        }
        else if(LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ARB_LOST))
        {
            LumenCom_state = LumenCom_I2C_FSM_IDLE;
                         errStatus = LumenCom_I2C_MSTR_ERR_ARB_LOST;
                         resetIp   = LumenCom_I2C_RESET_ERROR;
        }
        else /* LumenCom_INTR_MASTER_I2C_BUS_ERROR set is */
        {
            LumenCom_state = LumenCom_I2C_FSM_IDLE;
                         errStatus = LumenCom_I2C_MSTR_ERR_BUS_ERR;
                         resetIp   = LumenCom_I2C_RESET_ERROR;
        }

        LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_I2C_ACK      |
                                                    LumenCom_INTR_MASTER_I2C_NACK     |
                                                    LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                    LumenCom_INTR_MASTER_I2C_BUS_ERROR);

        /* Reset block in case of: LOST_ARB or BUS_ERR */
        if(0u != resetIp)
        {
            LumenCom_SCB_SW_RESET;
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterReadByte
********************************************************************************
*
* Summary:
*  Reads one byte from a slave and ACKs or NAKs received byte.
*  This function does not generate NAK explicitly. The following call
*  SCB_I2CMasterSendStop() or SCB_I2CMasterSendRestart() will generate NAK and
*  Stop or ReStart condition appropriately.
*  This function is blocking and does not return until byte is received
*  or error occurred.
*
* Parameters:
*  ackNack: Response to received byte.
*
* Return:
*  Byte read from the slave. In case of error the MSB of returned data
*  is set to 1.
*
* Side Effects:
*  A valid Start or ReStart condition must be generated before calling this
*  function. This function does nothing and returns invalid byte value
*  if Start or ReStart conditions failed before this function was called.
*
* Global variables:
*  LumenCom_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterReadByte(uint32 ackNack)
{
    uint32 theByte;

    /* Return invalid byte in case BUS_ERR happen during receiving */
    theByte = LumenCom_I2C_INVALID_BYTE;

    /* Check FSM state before read byte */
    if(LumenCom_CHECK_I2C_MASTER_ACTIVE)
    {
        while((!LumenCom_CHECK_INTR_RX(LumenCom_INTR_RX_NOT_EMPTY)) &&
              (!LumenCom_CHECK_INTR_MASTER(LumenCom_INTR_MASTER_I2C_ARB_LOST |
                                                  LumenCom_INTR_MASTER_I2C_BUS_ERROR)))
        {
            /* Wait until byte has been received */
        }

        /* Check the results after the byte was sent */
        if(LumenCom_CHECK_INTR_RX(LumenCom_INTR_RX_NOT_EMPTY))
        {
            theByte = LumenCom_RX_FIFO_RD_REG;

            LumenCom_ClearRxInterruptSource(LumenCom_INTR_RX_NOT_EMPTY);

            if(0u == ackNack)
            {
                LumenCom_I2C_MASTER_GENERATE_ACK;
            }
            else
            {
                /* NACK is generated by Stop or ReStart command */
                LumenCom_state = LumenCom_I2C_FSM_MSTR_HALT;
            }
        }
        else
        {
            LumenCom_ClearMasterInterruptSource(LumenCom_INTR_MASTER_ALL);

            /* Reset block in case of: LOST_ARB or BUS_ERR */
            LumenCom_SCB_SW_RESET;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that has been transferred with an
*  SCB_I2CMasterReadBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  the byte count transferred so far.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  LumenCom_mstrRdBufIndex - used to current index within master read
*  buffer.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterGetReadBufSize(void)
{
    return(LumenCom_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the number of bytes that have been transferred with an
*  SCB_I2CMasterWriteBuf() function.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it returns
*  zero unit transfer completion.
*
* Side Effects:
*  This function returns not valid value if SCB_I2C_MSTAT_ERR_ARB_LOST
*  or SCB_I2C_MSTAT_ERR_BUS_ERROR occurred while read transfer.
*
* Global variables:
*  LumenCom_mstrWrBufIndex - used to current index within master write
*  buffer.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterGetWriteBufSize(void)
{
    return(LumenCom_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LumenCom_mstrRdBufIndex - used to current index within master read
*   buffer.
*  LumenCom_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void LumenCom_I2CMasterClearReadBuf(void)
{
    LumenCom_DisableInt();  /* Lock from interruption */

    LumenCom_mstrRdBufIndex = 0u;
    LumenCom_mstrStatus    &= (uint16) ~LumenCom_I2C_MSTAT_RD_CMPLT;

    LumenCom_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LumenCom_mstrRdBufIndex - used to current index within master read
*   buffer.
*  LumenCom_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void LumenCom_I2CMasterClearWriteBuf(void)
{
    LumenCom_DisableInt();  /* Lock from interruption */

    LumenCom_mstrWrBufIndex = 0u;
    LumenCom_mstrStatus    &= (uint16) ~LumenCom_I2C_MSTAT_WR_CMPLT;

    LumenCom_EnableInt();   /* Release lock */
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterStatus
********************************************************************************
*
* Summary:
*  Returns the master's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  LumenCom_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterStatus(void)
{
    uint32 status;

    LumenCom_DisableInt();  /* Lock from interruption */

    status = (uint32) LumenCom_mstrStatus;

    if (LumenCom_CHECK_I2C_MASTER_ACTIVE)
    {
        /* Add status of master pending transaction: MSTAT_XFER_INP */
        status |= (uint32) LumenCom_I2C_MSTAT_XFER_INP;
    }

    LumenCom_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: LumenCom_I2CMasterClearStatus
********************************************************************************
*
* Summary:
*  Clears all status flags and returns the master status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  LumenCom_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 LumenCom_I2CMasterClearStatus(void)
{
    uint32 status;

    LumenCom_DisableInt();  /* Lock from interruption */

    /* Read and clear master status */
    status = (uint32) LumenCom_mstrStatus;
    LumenCom_mstrStatus = LumenCom_I2C_MSTAT_CLEAR;

    LumenCom_EnableInt();   /* Release lock */

    return(status);
}


/*******************************************************************************
* Function Name: LumenCom_I2CReStartGeneration
********************************************************************************
*
* Summary:
*  Generates a ReStart condition:
*  SCB IP V1 and later: Generates ReStart using the scb IP functionality
*    Sets the I2C_MASTER_CMD_M_START and I2C_MASTER_CMD_M_NACK (if the previous
*    transaction was read) bits in the SCB.I2C_MASTER_CMD register.
*    This combination forces the master to generate ReStart.
*
*  SCB IP V0: Generates Restart using the GPIO and scb IP functionality.
*   After the master completes write or read, the SCL is stretched.
*   The master waits until SDA line is released by the slave. Then the GPIO
*   function is enabled and the scb IP disabled as it already does not drive
*   the bus. In case of the previous transfer was read, the NACK is generated
*   by the GPIO. The delay of tLOW is added to manage the hold time.
*   Set I2C_M_CMD.START and enable the scb IP. The ReStart generation
*   is started after the I2C function is enabled for the SCL.
*   Note1: the scb IP due re-enable generates Start but on the I2C bus it
*          appears as ReStart.
*   Note2: the I2C_M_CMD.START is queued if scb IP is disabled.
*   Note3: the I2C_STATUS_M_READ is cleared is address was NACKed before.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  SCB IP V0: The NACK generation by the GPIO may cause a greater SCL period
*             than expected for the selected master data rate.
*
*******************************************************************************/
void LumenCom_I2CReStartGeneration(void)
{
#if(LumenCom_CY_SCBIP_V0)
    /* Generates Restart use GPIO and scb IP functionality. Ticket ID#143715,
    ID#145238 and ID#173656 */
    uint32 status = LumenCom_I2C_STATUS_REG;

    while(LumenCom_WAIT_SDA_SET_HIGH)
    {
        /* Wait when slave release SDA line: SCL tHIGH is complete */
    }

    /* Prepare DR register to drive SCL line */
    LumenCom_SET_I2C_SCL_DR(LumenCom_I2C_SCL_LOW);

    /* Switch HSIOM to GPIO: SCL goes low */
    LumenCom_SET_I2C_SCL_HSIOM_SEL(LumenCom_HSIOM_GPIO_SEL);

    /* Disable SCB block */
    LumenCom_CTRL_REG &= (uint32) ~LumenCom_CTRL_ENABLED;

    if(0u != (status & LumenCom_I2C_STATUS_M_READ))
    {
        /* Generate NACK use GPIO functionality */
        LumenCom_SET_I2C_SCL_DR(LumenCom_I2C_SCL_LOW);
        CyDelayUs(LumenCom_I2C_TLOW_TIME); /* Count tLOW */

        LumenCom_SET_I2C_SCL_DR(LumenCom_I2C_SCL_HIGH);
        while(LumenCom_WAIT_SCL_SET_HIGH)
        {
            /* Wait until slave releases SCL in case if it stretches */
        }
        CyDelayUs(LumenCom_I2C_THIGH_TIME); /* Count tHIGH */
    }

    /* Count tLOW as hold time for write and read */
    LumenCom_SET_I2C_SCL_DR(LumenCom_I2C_SCL_LOW);
    CyDelayUs(LumenCom_I2C_TLOW_TIME); /* Count tLOW */

    /* Set command for Start generation: it will appear */
    LumenCom_I2C_MASTER_CMD_REG = LumenCom_I2C_MASTER_CMD_M_START;

    /* Enable SCB block */
    LumenCom_CTRL_REG |= (uint32) LumenCom_CTRL_ENABLED;

    /* Switch HSIOM to I2C: */
    LumenCom_SET_I2C_SCL_HSIOM_SEL(LumenCom_HSIOM_I2C_SEL);

    /* Revert SCL DR register */
    LumenCom_SET_I2C_SCL_DR(LumenCom_I2C_SCL_HIGH);
#else
    uint32 cmd;

    /* Generates ReStart use scb IP functionality */
    cmd  = LumenCom_I2C_MASTER_CMD_M_START;
    cmd |= LumenCom_CHECK_I2C_STATUS(LumenCom_I2C_STATUS_M_READ) ?
                (LumenCom_I2C_MASTER_CMD_M_NACK) : (0u);

    LumenCom_I2C_MASTER_CMD_REG = cmd;
#endif /* (LumenCom_CY_SCBIP_V1) */
}

#endif /* (LumenCom_I2C_MASTER_CONST) */


#if (!LumenCom_CY_SCBIP_V0 && \
    LumenCom_I2C_MULTI_MASTER_SLAVE_CONST && LumenCom_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: LumenCom_I2CMasterDisableEcAm
    ********************************************************************************
    *
    * Summary:
    *  Disables externally clocked address match to enable master operation
    *  in active mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    static void LumenCom_I2CMasterDisableEcAm(void)
    {
        /* Disables externally clocked address match to enable master operation in active mode.
        * This applicable only for Multi-Master-Slave with wakeup enabled. Ticket ID#192742 */
        if (0u != (LumenCom_CTRL_REG & LumenCom_CTRL_EC_AM_MODE))
        {
            /* Enable external address match logic */
            LumenCom_Stop();
            LumenCom_CTRL_REG &= (uint32) ~LumenCom_CTRL_EC_AM_MODE;
            LumenCom_Enable();
        }
    }
#endif /* (!LumenCom_CY_SCBIP_V0) */


/* [] END OF FILE */
