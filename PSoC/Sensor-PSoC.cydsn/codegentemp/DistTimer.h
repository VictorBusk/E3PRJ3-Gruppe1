/*******************************************************************************
* File Name: DistTimer.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_DistTimer_H)
#define CY_Timer_v2_60_DistTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 DistTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define DistTimer_Resolution                 16u
#define DistTimer_UsingFixedFunction         0u
#define DistTimer_UsingHWCaptureCounter      0u
#define DistTimer_SoftwareCaptureMode        0u
#define DistTimer_SoftwareTriggerMode        0u
#define DistTimer_UsingHWEnable              1u
#define DistTimer_EnableTriggerMode          1u
#define DistTimer_InterruptOnCaptureCount    1u
#define DistTimer_RunModeUsed                2u
#define DistTimer_ControlRegRemoved          1u

#if defined(DistTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define DistTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (DistTimer_UsingFixedFunction)
    #define DistTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define DistTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End DistTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!DistTimer_UsingFixedFunction)

        uint16 TimerUdb;
        uint8 InterruptMaskValue;
        #if (DistTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!DistTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}DistTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    DistTimer_Start(void) ;
void    DistTimer_Stop(void) ;

void    DistTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   DistTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define DistTimer_GetInterruptSource() DistTimer_ReadStatusRegister()

#if(!DistTimer_UDB_CONTROL_REG_REMOVED)
    uint8   DistTimer_ReadControlRegister(void) ;
    void    DistTimer_WriteControlRegister(uint8 control) ;
#endif /* (!DistTimer_UDB_CONTROL_REG_REMOVED) */

uint16  DistTimer_ReadPeriod(void) ;
void    DistTimer_WritePeriod(uint16 period) ;
uint16  DistTimer_ReadCounter(void) ;
void    DistTimer_WriteCounter(uint16 counter) ;
uint16  DistTimer_ReadCapture(void) ;
void    DistTimer_SoftwareCapture(void) ;

#if(!DistTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (DistTimer_SoftwareCaptureMode)
        void    DistTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!DistTimer_UsingFixedFunction) */

    #if (DistTimer_SoftwareTriggerMode)
        void    DistTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (DistTimer_SoftwareTriggerMode) */

    #if (DistTimer_EnableTriggerMode)
        void    DistTimer_EnableTrigger(void) ;
        void    DistTimer_DisableTrigger(void) ;
    #endif /* (DistTimer_EnableTriggerMode) */


    #if(DistTimer_InterruptOnCaptureCount)
        void    DistTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (DistTimer_InterruptOnCaptureCount) */

    #if (DistTimer_UsingHWCaptureCounter)
        void    DistTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   DistTimer_ReadCaptureCount(void) ;
    #endif /* (DistTimer_UsingHWCaptureCounter) */

    void DistTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void DistTimer_Init(void)          ;
void DistTimer_Enable(void)        ;
void DistTimer_SaveConfig(void)    ;
void DistTimer_RestoreConfig(void) ;
void DistTimer_Sleep(void)         ;
void DistTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define DistTimer__B_TIMER__CM_NONE 0
#define DistTimer__B_TIMER__CM_RISINGEDGE 1
#define DistTimer__B_TIMER__CM_FALLINGEDGE 2
#define DistTimer__B_TIMER__CM_EITHEREDGE 3
#define DistTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define DistTimer__B_TIMER__TM_NONE 0x00u
#define DistTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define DistTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define DistTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define DistTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define DistTimer_INIT_PERIOD             65535u
#define DistTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)2u << DistTimer_CTRL_CAP_MODE_SHIFT))
#define DistTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)1u << DistTimer_CTRL_TRIG_MODE_SHIFT))
#if (DistTimer_UsingFixedFunction)
    #define DistTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << DistTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)1 << DistTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define DistTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << DistTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)1 << DistTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << DistTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (DistTimer_UsingFixedFunction) */
#define DistTimer_INIT_CAPTURE_COUNT      (2u)
#define DistTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << DistTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (DistTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define DistTimer_STATUS         (*(reg8 *) DistTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define DistTimer_STATUS_MASK    (*(reg8 *) DistTimer_TimerHW__SR0 )
    #define DistTimer_CONTROL        (*(reg8 *) DistTimer_TimerHW__CFG0)
    #define DistTimer_CONTROL2       (*(reg8 *) DistTimer_TimerHW__CFG1)
    #define DistTimer_CONTROL2_PTR   ( (reg8 *) DistTimer_TimerHW__CFG1)
    #define DistTimer_RT1            (*(reg8 *) DistTimer_TimerHW__RT1)
    #define DistTimer_RT1_PTR        ( (reg8 *) DistTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define DistTimer_CONTROL3       (*(reg8 *) DistTimer_TimerHW__CFG2)
        #define DistTimer_CONTROL3_PTR   ( (reg8 *) DistTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define DistTimer_GLOBAL_ENABLE  (*(reg8 *) DistTimer_TimerHW__PM_ACT_CFG)
    #define DistTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) DistTimer_TimerHW__PM_STBY_CFG)

    #define DistTimer_CAPTURE_LSB         (* (reg16 *) DistTimer_TimerHW__CAP0 )
    #define DistTimer_CAPTURE_LSB_PTR       ((reg16 *) DistTimer_TimerHW__CAP0 )
    #define DistTimer_PERIOD_LSB          (* (reg16 *) DistTimer_TimerHW__PER0 )
    #define DistTimer_PERIOD_LSB_PTR        ((reg16 *) DistTimer_TimerHW__PER0 )
    #define DistTimer_COUNTER_LSB         (* (reg16 *) DistTimer_TimerHW__CNT_CMP0 )
    #define DistTimer_COUNTER_LSB_PTR       ((reg16 *) DistTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define DistTimer_BLOCK_EN_MASK                     DistTimer_TimerHW__PM_ACT_MSK
    #define DistTimer_BLOCK_STBY_EN_MASK                DistTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define DistTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define DistTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define DistTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define DistTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define DistTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define DistTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << DistTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define DistTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define DistTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << DistTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define DistTimer_CTRL_MODE_SHIFT                 0x01u
        #define DistTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << DistTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define DistTimer_CTRL_RCOD_SHIFT        0x02u
        #define DistTimer_CTRL_ENBL_SHIFT        0x00u
        #define DistTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define DistTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << DistTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define DistTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << DistTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define DistTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << DistTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define DistTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << DistTimer_CTRL_RCOD_SHIFT))
        #define DistTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << DistTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define DistTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define DistTimer_RT1_MASK                        ((uint8)((uint8)0x03u << DistTimer_RT1_SHIFT))
    #define DistTimer_SYNC                            ((uint8)((uint8)0x03u << DistTimer_RT1_SHIFT))
    #define DistTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define DistTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << DistTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define DistTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << DistTimer_SYNCDSI_SHIFT))

    #define DistTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << DistTimer_CTRL_MODE_SHIFT))
    #define DistTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << DistTimer_CTRL_MODE_SHIFT))
    #define DistTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << DistTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define DistTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define DistTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define DistTimer_STATUS_TC_INT_MASK_SHIFT        (DistTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define DistTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (DistTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define DistTimer_STATUS_TC                       ((uint8)((uint8)0x01u << DistTimer_STATUS_TC_SHIFT))
    #define DistTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << DistTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define DistTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << DistTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define DistTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << DistTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define DistTimer_STATUS              (* (reg8 *) DistTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define DistTimer_STATUS_MASK         (* (reg8 *) DistTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define DistTimer_STATUS_AUX_CTRL     (* (reg8 *) DistTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define DistTimer_CONTROL             (* (reg8 *) DistTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(DistTimer_Resolution <= 8u) /* 8-bit Timer */
        #define DistTimer_CAPTURE_LSB         (* (reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DistTimer_CAPTURE_LSB_PTR       ((reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DistTimer_PERIOD_LSB          (* (reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DistTimer_PERIOD_LSB_PTR        ((reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DistTimer_COUNTER_LSB         (* (reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define DistTimer_COUNTER_LSB_PTR       ((reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #elif(DistTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define DistTimer_CAPTURE_LSB         (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DistTimer_CAPTURE_LSB_PTR       ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DistTimer_PERIOD_LSB          (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DistTimer_PERIOD_LSB_PTR        ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DistTimer_COUNTER_LSB         (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define DistTimer_COUNTER_LSB_PTR       ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define DistTimer_CAPTURE_LSB         (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define DistTimer_CAPTURE_LSB_PTR       ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_F0_REG )
            #define DistTimer_PERIOD_LSB          (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define DistTimer_PERIOD_LSB_PTR        ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_D0_REG )
            #define DistTimer_COUNTER_LSB         (* (reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
            #define DistTimer_COUNTER_LSB_PTR       ((reg16 *) DistTimer_TimerUDB_sT16_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(DistTimer_Resolution <= 24u)/* 24-bit Timer */
        #define DistTimer_CAPTURE_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DistTimer_CAPTURE_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
        #define DistTimer_PERIOD_LSB          (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DistTimer_PERIOD_LSB_PTR        ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
        #define DistTimer_COUNTER_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #define DistTimer_COUNTER_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define DistTimer_CAPTURE_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DistTimer_CAPTURE_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__F0_REG )
            #define DistTimer_PERIOD_LSB          (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DistTimer_PERIOD_LSB_PTR        ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__D0_REG )
            #define DistTimer_COUNTER_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
            #define DistTimer_COUNTER_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define DistTimer_CAPTURE_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define DistTimer_CAPTURE_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_F0_REG )
            #define DistTimer_PERIOD_LSB          (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define DistTimer_PERIOD_LSB_PTR        ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_D0_REG )
            #define DistTimer_COUNTER_LSB         (* (reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
            #define DistTimer_COUNTER_LSB_PTR       ((reg32 *) DistTimer_TimerUDB_sT16_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define DistTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) DistTimer_TimerUDB_sT16_timerdp_u0__A0_REG )
    
    #if (DistTimer_UsingHWCaptureCounter)
        #define DistTimer_CAP_COUNT              (*(reg8 *) DistTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define DistTimer_CAP_COUNT_PTR          ( (reg8 *) DistTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define DistTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) DistTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define DistTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) DistTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (DistTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define DistTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define DistTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define DistTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define DistTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define DistTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define DistTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << DistTimer_CTRL_INTCNT_SHIFT))
    #define DistTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << DistTimer_CTRL_TRIG_MODE_SHIFT))
    #define DistTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << DistTimer_CTRL_TRIG_EN_SHIFT))
    #define DistTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << DistTimer_CTRL_CAP_MODE_SHIFT))
    #define DistTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << DistTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define DistTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define DistTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define DistTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define DistTimer_STATUS_TC_INT_MASK_SHIFT       DistTimer_STATUS_TC_SHIFT
    #define DistTimer_STATUS_CAPTURE_INT_MASK_SHIFT  DistTimer_STATUS_CAPTURE_SHIFT
    #define DistTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define DistTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define DistTimer_STATUS_FIFOFULL_INT_MASK_SHIFT DistTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define DistTimer_STATUS_TC                      ((uint8)((uint8)0x01u << DistTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define DistTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << DistTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DistTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << DistTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DistTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << DistTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define DistTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << DistTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define DistTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << DistTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define DistTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << DistTimer_STATUS_FIFOFULL_SHIFT))

    #define DistTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define DistTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define DistTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define DistTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define DistTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define DistTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_DistTimer_H */


/* [] END OF FILE */
