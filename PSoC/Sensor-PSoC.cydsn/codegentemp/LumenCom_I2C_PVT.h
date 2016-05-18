/*******************************************************************************
* File Name: .h
* Version 3.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_PVT_LumenCom_H)
#define CY_SCB_I2C_PVT_LumenCom_H

#include "LumenCom_I2C.h"


/***************************************
*     Private Global Vars
***************************************/

extern volatile uint8 LumenCom_state; /* Current state of I2C FSM */

#if(LumenCom_I2C_SLAVE_CONST)
    extern volatile uint8 LumenCom_slStatus;          /* Slave Status */

    /* Receive buffer variables */
    extern volatile uint8 * LumenCom_slWrBufPtr;      /* Pointer to Receive buffer  */
    extern volatile uint32  LumenCom_slWrBufSize;     /* Slave Receive buffer size  */
    extern volatile uint32  LumenCom_slWrBufIndex;    /* Slave Receive buffer Index */

    /* Transmit buffer variables */
    extern volatile uint8 * LumenCom_slRdBufPtr;      /* Pointer to Transmit buffer  */
    extern volatile uint32  LumenCom_slRdBufSize;     /* Slave Transmit buffer size  */
    extern volatile uint32  LumenCom_slRdBufIndex;    /* Slave Transmit buffer Index */
    extern volatile uint32  LumenCom_slRdBufIndexTmp; /* Slave Transmit buffer Index Tmp */
    extern volatile uint8   LumenCom_slOverFlowCount; /* Slave Transmit Overflow counter */
#endif /* (LumenCom_I2C_SLAVE_CONST) */

#if(LumenCom_I2C_MASTER_CONST)
    extern volatile uint16 LumenCom_mstrStatus;      /* Master Status byte  */
    extern volatile uint8  LumenCom_mstrControl;     /* Master Control byte */

    /* Receive buffer variables */
    extern volatile uint8 * LumenCom_mstrRdBufPtr;   /* Pointer to Master Read buffer */
    extern volatile uint32  LumenCom_mstrRdBufSize;  /* Master Read buffer size       */
    extern volatile uint32  LumenCom_mstrRdBufIndex; /* Master Read buffer Index      */

    /* Transmit buffer variables */
    extern volatile uint8 * LumenCom_mstrWrBufPtr;   /* Pointer to Master Write buffer */
    extern volatile uint32  LumenCom_mstrWrBufSize;  /* Master Write buffer size       */
    extern volatile uint32  LumenCom_mstrWrBufIndex; /* Master Write buffer Index      */
    extern volatile uint32  LumenCom_mstrWrBufIndexTmp; /* Master Write buffer Index Tmp */
#endif /* (LumenCom_I2C_MASTER_CONST) */

#if (LumenCom_I2C_CUSTOM_ADDRESS_HANDLER_CONST)
    extern uint32 (*LumenCom_customAddressHandler) (void);
#endif /* (LumenCom_I2C_CUSTOM_ADDRESS_HANDLER_CONST) */

/***************************************
*     Private Function Prototypes
***************************************/

#if(LumenCom_SCB_MODE_I2C_CONST_CFG)
    void LumenCom_I2CInit(void);
#endif /* (LumenCom_SCB_MODE_I2C_CONST_CFG) */

void LumenCom_I2CStop(void);
void LumenCom_I2CSaveConfig(void);
void LumenCom_I2CRestoreConfig(void);

#if(LumenCom_I2C_MASTER_CONST)
    void LumenCom_I2CReStartGeneration(void);
#endif /* (LumenCom_I2C_MASTER_CONST) */

#endif /* (CY_SCB_I2C_PVT_LumenCom_H) */


/* [] END OF FILE */
