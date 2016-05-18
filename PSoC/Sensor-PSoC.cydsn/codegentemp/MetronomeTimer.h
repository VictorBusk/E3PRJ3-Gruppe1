/*******************************************************************************
* File Name: MetronomeTimer.h
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

#if !defined(CY_Timer_v2_60_MetronomeTimer_H)
#define CY_Timer_v2_60_MetronomeTimer_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 MetronomeTimer_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define MetronomeTimer_Resolution                 8u
#define MetronomeTimer_UsingFixedFunction         0u
#define MetronomeTimer_UsingHWCaptureCounter      0u
#define MetronomeTimer_SoftwareCaptureMode        0u
#define MetronomeTimer_SoftwareTriggerMode        0u
#define MetronomeTimer_UsingHWEnable              0u
#define MetronomeTimer_EnableTriggerMode          0u
#define MetronomeTimer_InterruptOnCaptureCount    0u
#define MetronomeTimer_RunModeUsed                0u
#define MetronomeTimer_ControlRegRemoved          0u

#if defined(MetronomeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define MetronomeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (MetronomeTimer_UsingFixedFunction)
    #define MetronomeTimer_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define MetronomeTimer_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End MetronomeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!MetronomeTimer_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (MetronomeTimer_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}MetronomeTimer_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    MetronomeTimer_Start(void) ;
void    MetronomeTimer_Stop(void) ;

void    MetronomeTimer_SetInterruptMode(uint8 interruptMode) ;
uint8   MetronomeTimer_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define MetronomeTimer_GetInterruptSource() MetronomeTimer_ReadStatusRegister()

#if(!MetronomeTimer_UDB_CONTROL_REG_REMOVED)
    uint8   MetronomeTimer_ReadControlRegister(void) ;
    void    MetronomeTimer_WriteControlRegister(uint8 control) ;
#endif /* (!MetronomeTimer_UDB_CONTROL_REG_REMOVED) */

uint8  MetronomeTimer_ReadPeriod(void) ;
void    MetronomeTimer_WritePeriod(uint8 period) ;
uint8  MetronomeTimer_ReadCounter(void) ;
void    MetronomeTimer_WriteCounter(uint8 counter) ;
uint8  MetronomeTimer_ReadCapture(void) ;
void    MetronomeTimer_SoftwareCapture(void) ;

#if(!MetronomeTimer_UsingFixedFunction) /* UDB Prototypes */
    #if (MetronomeTimer_SoftwareCaptureMode)
        void    MetronomeTimer_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!MetronomeTimer_UsingFixedFunction) */

    #if (MetronomeTimer_SoftwareTriggerMode)
        void    MetronomeTimer_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (MetronomeTimer_SoftwareTriggerMode) */

    #if (MetronomeTimer_EnableTriggerMode)
        void    MetronomeTimer_EnableTrigger(void) ;
        void    MetronomeTimer_DisableTrigger(void) ;
    #endif /* (MetronomeTimer_EnableTriggerMode) */


    #if(MetronomeTimer_InterruptOnCaptureCount)
        void    MetronomeTimer_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (MetronomeTimer_InterruptOnCaptureCount) */

    #if (MetronomeTimer_UsingHWCaptureCounter)
        void    MetronomeTimer_SetCaptureCount(uint8 captureCount) ;
        uint8   MetronomeTimer_ReadCaptureCount(void) ;
    #endif /* (MetronomeTimer_UsingHWCaptureCounter) */

    void MetronomeTimer_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void MetronomeTimer_Init(void)          ;
void MetronomeTimer_Enable(void)        ;
void MetronomeTimer_SaveConfig(void)    ;
void MetronomeTimer_RestoreConfig(void) ;
void MetronomeTimer_Sleep(void)         ;
void MetronomeTimer_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define MetronomeTimer__B_TIMER__CM_NONE 0
#define MetronomeTimer__B_TIMER__CM_RISINGEDGE 1
#define MetronomeTimer__B_TIMER__CM_FALLINGEDGE 2
#define MetronomeTimer__B_TIMER__CM_EITHEREDGE 3
#define MetronomeTimer__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define MetronomeTimer__B_TIMER__TM_NONE 0x00u
#define MetronomeTimer__B_TIMER__TM_RISINGEDGE 0x04u
#define MetronomeTimer__B_TIMER__TM_FALLINGEDGE 0x08u
#define MetronomeTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
#define MetronomeTimer__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define MetronomeTimer_INIT_PERIOD             99u
#define MetronomeTimer_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << MetronomeTimer_CTRL_CAP_MODE_SHIFT))
#define MetronomeTimer_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << MetronomeTimer_CTRL_TRIG_MODE_SHIFT))
#if (MetronomeTimer_UsingFixedFunction)
    #define MetronomeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << MetronomeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << MetronomeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define MetronomeTimer_INIT_INTERRUPT_MODE (((uint8)((uint8)1u << MetronomeTimer_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << MetronomeTimer_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << MetronomeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (MetronomeTimer_UsingFixedFunction) */
#define MetronomeTimer_INIT_CAPTURE_COUNT      (2u)
#define MetronomeTimer_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << MetronomeTimer_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (MetronomeTimer_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define MetronomeTimer_STATUS         (*(reg8 *) MetronomeTimer_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define MetronomeTimer_STATUS_MASK    (*(reg8 *) MetronomeTimer_TimerHW__SR0 )
    #define MetronomeTimer_CONTROL        (*(reg8 *) MetronomeTimer_TimerHW__CFG0)
    #define MetronomeTimer_CONTROL2       (*(reg8 *) MetronomeTimer_TimerHW__CFG1)
    #define MetronomeTimer_CONTROL2_PTR   ( (reg8 *) MetronomeTimer_TimerHW__CFG1)
    #define MetronomeTimer_RT1            (*(reg8 *) MetronomeTimer_TimerHW__RT1)
    #define MetronomeTimer_RT1_PTR        ( (reg8 *) MetronomeTimer_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define MetronomeTimer_CONTROL3       (*(reg8 *) MetronomeTimer_TimerHW__CFG2)
        #define MetronomeTimer_CONTROL3_PTR   ( (reg8 *) MetronomeTimer_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define MetronomeTimer_GLOBAL_ENABLE  (*(reg8 *) MetronomeTimer_TimerHW__PM_ACT_CFG)
    #define MetronomeTimer_GLOBAL_STBY_ENABLE  (*(reg8 *) MetronomeTimer_TimerHW__PM_STBY_CFG)

    #define MetronomeTimer_CAPTURE_LSB         (* (reg16 *) MetronomeTimer_TimerHW__CAP0 )
    #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg16 *) MetronomeTimer_TimerHW__CAP0 )
    #define MetronomeTimer_PERIOD_LSB          (* (reg16 *) MetronomeTimer_TimerHW__PER0 )
    #define MetronomeTimer_PERIOD_LSB_PTR        ((reg16 *) MetronomeTimer_TimerHW__PER0 )
    #define MetronomeTimer_COUNTER_LSB         (* (reg16 *) MetronomeTimer_TimerHW__CNT_CMP0 )
    #define MetronomeTimer_COUNTER_LSB_PTR       ((reg16 *) MetronomeTimer_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define MetronomeTimer_BLOCK_EN_MASK                     MetronomeTimer_TimerHW__PM_ACT_MSK
    #define MetronomeTimer_BLOCK_STBY_EN_MASK                MetronomeTimer_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define MetronomeTimer_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define MetronomeTimer_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define MetronomeTimer_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define MetronomeTimer_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define MetronomeTimer_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define MetronomeTimer_CTRL_ENABLE                        ((uint8)((uint8)0x01u << MetronomeTimer_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define MetronomeTimer_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define MetronomeTimer_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << MetronomeTimer_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define MetronomeTimer_CTRL_MODE_SHIFT                 0x01u
        #define MetronomeTimer_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << MetronomeTimer_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define MetronomeTimer_CTRL_RCOD_SHIFT        0x02u
        #define MetronomeTimer_CTRL_ENBL_SHIFT        0x00u
        #define MetronomeTimer_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define MetronomeTimer_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define MetronomeTimer_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << MetronomeTimer_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define MetronomeTimer_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define MetronomeTimer_CTRL_RCOD       ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_RCOD_SHIFT))
        #define MetronomeTimer_CTRL_ENBL       ((uint8)((uint8)0x80u << MetronomeTimer_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define MetronomeTimer_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define MetronomeTimer_RT1_MASK                        ((uint8)((uint8)0x03u << MetronomeTimer_RT1_SHIFT))
    #define MetronomeTimer_SYNC                            ((uint8)((uint8)0x03u << MetronomeTimer_RT1_SHIFT))
    #define MetronomeTimer_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define MetronomeTimer_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << MetronomeTimer_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define MetronomeTimer_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << MetronomeTimer_SYNCDSI_SHIFT))

    #define MetronomeTimer_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << MetronomeTimer_CTRL_MODE_SHIFT))
    #define MetronomeTimer_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << MetronomeTimer_CTRL_MODE_SHIFT))
    #define MetronomeTimer_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << MetronomeTimer_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define MetronomeTimer_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define MetronomeTimer_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define MetronomeTimer_STATUS_TC_INT_MASK_SHIFT        (MetronomeTimer_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define MetronomeTimer_STATUS_CAPTURE_INT_MASK_SHIFT   (MetronomeTimer_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define MetronomeTimer_STATUS_TC                       ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_TC_SHIFT))
    #define MetronomeTimer_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define MetronomeTimer_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define MetronomeTimer_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define MetronomeTimer_STATUS              (* (reg8 *) MetronomeTimer_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define MetronomeTimer_STATUS_MASK         (* (reg8 *) MetronomeTimer_TimerUDB_rstSts_stsreg__MASK_REG)
    #define MetronomeTimer_STATUS_AUX_CTRL     (* (reg8 *) MetronomeTimer_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define MetronomeTimer_CONTROL             (* (reg8 *) MetronomeTimer_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(MetronomeTimer_Resolution <= 8u) /* 8-bit Timer */
        #define MetronomeTimer_CAPTURE_LSB         (* (reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define MetronomeTimer_PERIOD_LSB          (* (reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define MetronomeTimer_PERIOD_LSB_PTR        ((reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define MetronomeTimer_COUNTER_LSB         (* (reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define MetronomeTimer_COUNTER_LSB_PTR       ((reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(MetronomeTimer_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define MetronomeTimer_CAPTURE_LSB         (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define MetronomeTimer_PERIOD_LSB          (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define MetronomeTimer_PERIOD_LSB_PTR        ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define MetronomeTimer_COUNTER_LSB         (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define MetronomeTimer_COUNTER_LSB_PTR       ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define MetronomeTimer_CAPTURE_LSB         (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define MetronomeTimer_PERIOD_LSB          (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define MetronomeTimer_PERIOD_LSB_PTR        ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define MetronomeTimer_COUNTER_LSB         (* (reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define MetronomeTimer_COUNTER_LSB_PTR       ((reg16 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(MetronomeTimer_Resolution <= 24u)/* 24-bit Timer */
        #define MetronomeTimer_CAPTURE_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define MetronomeTimer_PERIOD_LSB          (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define MetronomeTimer_PERIOD_LSB_PTR        ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define MetronomeTimer_COUNTER_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define MetronomeTimer_COUNTER_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define MetronomeTimer_CAPTURE_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define MetronomeTimer_PERIOD_LSB          (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define MetronomeTimer_PERIOD_LSB_PTR        ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define MetronomeTimer_COUNTER_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define MetronomeTimer_COUNTER_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define MetronomeTimer_CAPTURE_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define MetronomeTimer_CAPTURE_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define MetronomeTimer_PERIOD_LSB          (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define MetronomeTimer_PERIOD_LSB_PTR        ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define MetronomeTimer_COUNTER_LSB         (* (reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define MetronomeTimer_COUNTER_LSB_PTR       ((reg32 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define MetronomeTimer_COUNTER_LSB_PTR_8BIT       ((reg8 *) MetronomeTimer_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (MetronomeTimer_UsingHWCaptureCounter)
        #define MetronomeTimer_CAP_COUNT              (*(reg8 *) MetronomeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define MetronomeTimer_CAP_COUNT_PTR          ( (reg8 *) MetronomeTimer_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define MetronomeTimer_CAPTURE_COUNT_CTRL     (*(reg8 *) MetronomeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define MetronomeTimer_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) MetronomeTimer_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (MetronomeTimer_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define MetronomeTimer_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define MetronomeTimer_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define MetronomeTimer_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define MetronomeTimer_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define MetronomeTimer_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define MetronomeTimer_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_INTCNT_SHIFT))
    #define MetronomeTimer_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_TRIG_MODE_SHIFT))
    #define MetronomeTimer_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << MetronomeTimer_CTRL_TRIG_EN_SHIFT))
    #define MetronomeTimer_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << MetronomeTimer_CTRL_CAP_MODE_SHIFT))
    #define MetronomeTimer_CTRL_ENABLE                    ((uint8)((uint8)0x01u << MetronomeTimer_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define MetronomeTimer_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define MetronomeTimer_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define MetronomeTimer_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define MetronomeTimer_STATUS_TC_INT_MASK_SHIFT       MetronomeTimer_STATUS_TC_SHIFT
    #define MetronomeTimer_STATUS_CAPTURE_INT_MASK_SHIFT  MetronomeTimer_STATUS_CAPTURE_SHIFT
    #define MetronomeTimer_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define MetronomeTimer_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define MetronomeTimer_STATUS_FIFOFULL_INT_MASK_SHIFT MetronomeTimer_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define MetronomeTimer_STATUS_TC                      ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define MetronomeTimer_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MetronomeTimer_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MetronomeTimer_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define MetronomeTimer_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define MetronomeTimer_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define MetronomeTimer_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << MetronomeTimer_STATUS_FIFOFULL_SHIFT))

    #define MetronomeTimer_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define MetronomeTimer_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define MetronomeTimer_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define MetronomeTimer_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define MetronomeTimer_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define MetronomeTimer_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_MetronomeTimer_H */


/* [] END OF FILE */
