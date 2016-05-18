/*******************************************************************************
* File Name: RedPWM.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the RedPWM
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_RedPWM_H)
#define CY_TCPWM_RedPWM_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} RedPWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  RedPWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define RedPWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define RedPWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define RedPWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define RedPWM_QUAD_ENCODING_MODES            (0lu)
#define RedPWM_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define RedPWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define RedPWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define RedPWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define RedPWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define RedPWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define RedPWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define RedPWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define RedPWM_TC_RUN_MODE                    (0lu)
#define RedPWM_TC_COUNTER_MODE                (0lu)
#define RedPWM_TC_COMP_CAP_MODE               (2lu)
#define RedPWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define RedPWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define RedPWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define RedPWM_TC_START_SIGNAL_MODE           (0lu)
#define RedPWM_TC_STOP_SIGNAL_MODE            (0lu)
#define RedPWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define RedPWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define RedPWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define RedPWM_TC_START_SIGNAL_PRESENT        (0lu)
#define RedPWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define RedPWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RedPWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define RedPWM_PWM_KILL_EVENT                 (0lu)
#define RedPWM_PWM_STOP_EVENT                 (0lu)
#define RedPWM_PWM_MODE                       (4lu)
#define RedPWM_PWM_OUT_N_INVERT               (0lu)
#define RedPWM_PWM_OUT_INVERT                 (0lu)
#define RedPWM_PWM_ALIGN                      (0lu)
#define RedPWM_PWM_RUN_MODE                   (0lu)
#define RedPWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define RedPWM_PWM_PRESCALER                  (2lu)

/* Signal modes */
#define RedPWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define RedPWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define RedPWM_PWM_START_SIGNAL_MODE          (0lu)
#define RedPWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define RedPWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define RedPWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define RedPWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define RedPWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define RedPWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define RedPWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define RedPWM_PWM_INTERRUPT_MASK             (0lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define RedPWM_TC_PERIOD_VALUE                (65535lu)
#define RedPWM_TC_COMPARE_VALUE               (65535lu)
#define RedPWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define RedPWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define RedPWM_PWM_PERIOD_VALUE               (255lu)
#define RedPWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define RedPWM_PWM_PERIOD_SWAP                (0lu)
#define RedPWM_PWM_COMPARE_VALUE              (0lu)
#define RedPWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define RedPWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define RedPWM__LEFT 0
#define RedPWM__RIGHT 1
#define RedPWM__CENTER 2
#define RedPWM__ASYMMETRIC 3

#define RedPWM__X1 0
#define RedPWM__X2 1
#define RedPWM__X4 2

#define RedPWM__PWM 4
#define RedPWM__PWM_DT 5
#define RedPWM__PWM_PR 6

#define RedPWM__INVERSE 1
#define RedPWM__DIRECT 0

#define RedPWM__CAPTURE 2
#define RedPWM__COMPARE 0

#define RedPWM__TRIG_LEVEL 3
#define RedPWM__TRIG_RISING 0
#define RedPWM__TRIG_FALLING 1
#define RedPWM__TRIG_BOTH 2

#define RedPWM__INTR_MASK_TC 1
#define RedPWM__INTR_MASK_CC_MATCH 2
#define RedPWM__INTR_MASK_NONE 0
#define RedPWM__INTR_MASK_TC_CC 3

#define RedPWM__UNCONFIG 8
#define RedPWM__TIMER 1
#define RedPWM__QUAD 3
#define RedPWM__PWM_SEL 7

#define RedPWM__COUNT_UP 0
#define RedPWM__COUNT_DOWN 1
#define RedPWM__COUNT_UPDOWN0 2
#define RedPWM__COUNT_UPDOWN1 3


/* Prescaler */
#define RedPWM_PRESCALE_DIVBY1                ((uint32)(0u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY2                ((uint32)(1u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY4                ((uint32)(2u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY8                ((uint32)(3u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY16               ((uint32)(4u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY32               ((uint32)(5u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY64               ((uint32)(6u << RedPWM_PRESCALER_SHIFT))
#define RedPWM_PRESCALE_DIVBY128              ((uint32)(7u << RedPWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define RedPWM_MODE_TIMER_COMPARE             ((uint32)(RedPWM__COMPARE         <<  \
                                                                  RedPWM_MODE_SHIFT))
#define RedPWM_MODE_TIMER_CAPTURE             ((uint32)(RedPWM__CAPTURE         <<  \
                                                                  RedPWM_MODE_SHIFT))
#define RedPWM_MODE_QUAD                      ((uint32)(RedPWM__QUAD            <<  \
                                                                  RedPWM_MODE_SHIFT))
#define RedPWM_MODE_PWM                       ((uint32)(RedPWM__PWM             <<  \
                                                                  RedPWM_MODE_SHIFT))
#define RedPWM_MODE_PWM_DT                    ((uint32)(RedPWM__PWM_DT          <<  \
                                                                  RedPWM_MODE_SHIFT))
#define RedPWM_MODE_PWM_PR                    ((uint32)(RedPWM__PWM_PR          <<  \
                                                                  RedPWM_MODE_SHIFT))

/* Quad Modes */
#define RedPWM_MODE_X1                        ((uint32)(RedPWM__X1              <<  \
                                                                  RedPWM_QUAD_MODE_SHIFT))
#define RedPWM_MODE_X2                        ((uint32)(RedPWM__X2              <<  \
                                                                  RedPWM_QUAD_MODE_SHIFT))
#define RedPWM_MODE_X4                        ((uint32)(RedPWM__X4              <<  \
                                                                  RedPWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define RedPWM_COUNT_UP                       ((uint32)(RedPWM__COUNT_UP        <<  \
                                                                  RedPWM_UPDOWN_SHIFT))
#define RedPWM_COUNT_DOWN                     ((uint32)(RedPWM__COUNT_DOWN      <<  \
                                                                  RedPWM_UPDOWN_SHIFT))
#define RedPWM_COUNT_UPDOWN0                  ((uint32)(RedPWM__COUNT_UPDOWN0   <<  \
                                                                  RedPWM_UPDOWN_SHIFT))
#define RedPWM_COUNT_UPDOWN1                  ((uint32)(RedPWM__COUNT_UPDOWN1   <<  \
                                                                  RedPWM_UPDOWN_SHIFT))

/* PWM output invert */
#define RedPWM_INVERT_LINE                    ((uint32)(RedPWM__INVERSE         <<  \
                                                                  RedPWM_INV_OUT_SHIFT))
#define RedPWM_INVERT_LINE_N                  ((uint32)(RedPWM__INVERSE         <<  \
                                                                  RedPWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define RedPWM_TRIG_RISING                    ((uint32)RedPWM__TRIG_RISING)
#define RedPWM_TRIG_FALLING                   ((uint32)RedPWM__TRIG_FALLING)
#define RedPWM_TRIG_BOTH                      ((uint32)RedPWM__TRIG_BOTH)
#define RedPWM_TRIG_LEVEL                     ((uint32)RedPWM__TRIG_LEVEL)

/* Interrupt mask */
#define RedPWM_INTR_MASK_TC                   ((uint32)RedPWM__INTR_MASK_TC)
#define RedPWM_INTR_MASK_CC_MATCH             ((uint32)RedPWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define RedPWM_CC_MATCH_SET                   (0x00u)
#define RedPWM_CC_MATCH_CLEAR                 (0x01u)
#define RedPWM_CC_MATCH_INVERT                (0x02u)
#define RedPWM_CC_MATCH_NO_CHANGE             (0x03u)
#define RedPWM_OVERLOW_SET                    (0x00u)
#define RedPWM_OVERLOW_CLEAR                  (0x04u)
#define RedPWM_OVERLOW_INVERT                 (0x08u)
#define RedPWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define RedPWM_UNDERFLOW_SET                  (0x00u)
#define RedPWM_UNDERFLOW_CLEAR                (0x10u)
#define RedPWM_UNDERFLOW_INVERT               (0x20u)
#define RedPWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define RedPWM_PWM_MODE_LEFT                  (RedPWM_CC_MATCH_CLEAR        |   \
                                                         RedPWM_OVERLOW_SET           |   \
                                                         RedPWM_UNDERFLOW_NO_CHANGE)
#define RedPWM_PWM_MODE_RIGHT                 (RedPWM_CC_MATCH_SET          |   \
                                                         RedPWM_OVERLOW_NO_CHANGE     |   \
                                                         RedPWM_UNDERFLOW_CLEAR)
#define RedPWM_PWM_MODE_ASYM                  (RedPWM_CC_MATCH_INVERT       |   \
                                                         RedPWM_OVERLOW_SET           |   \
                                                         RedPWM_UNDERFLOW_CLEAR)

#if (RedPWM_CY_TCPWM_V2)
    #if(RedPWM_CY_TCPWM_4000)
        #define RedPWM_PWM_MODE_CENTER                (RedPWM_CC_MATCH_INVERT       |   \
                                                                 RedPWM_OVERLOW_NO_CHANGE     |   \
                                                                 RedPWM_UNDERFLOW_CLEAR)
    #else
        #define RedPWM_PWM_MODE_CENTER                (RedPWM_CC_MATCH_INVERT       |   \
                                                                 RedPWM_OVERLOW_SET           |   \
                                                                 RedPWM_UNDERFLOW_CLEAR)
    #endif /* (RedPWM_CY_TCPWM_4000) */
#else
    #define RedPWM_PWM_MODE_CENTER                (RedPWM_CC_MATCH_INVERT       |   \
                                                             RedPWM_OVERLOW_NO_CHANGE     |   \
                                                             RedPWM_UNDERFLOW_CLEAR)
#endif /* (RedPWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define RedPWM_CMD_CAPTURE                    (0u)
#define RedPWM_CMD_RELOAD                     (8u)
#define RedPWM_CMD_STOP                       (16u)
#define RedPWM_CMD_START                      (24u)

/* Status */
#define RedPWM_STATUS_DOWN                    (1u)
#define RedPWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   RedPWM_Init(void);
void   RedPWM_Enable(void);
void   RedPWM_Start(void);
void   RedPWM_Stop(void);

void   RedPWM_SetMode(uint32 mode);
void   RedPWM_SetCounterMode(uint32 counterMode);
void   RedPWM_SetPWMMode(uint32 modeMask);
void   RedPWM_SetQDMode(uint32 qdMode);

void   RedPWM_SetPrescaler(uint32 prescaler);
void   RedPWM_TriggerCommand(uint32 mask, uint32 command);
void   RedPWM_SetOneShot(uint32 oneShotEnable);
uint32 RedPWM_ReadStatus(void);

void   RedPWM_SetPWMSyncKill(uint32 syncKillEnable);
void   RedPWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   RedPWM_SetPWMDeadTime(uint32 deadTime);
void   RedPWM_SetPWMInvert(uint32 mask);

void   RedPWM_SetInterruptMode(uint32 interruptMask);
uint32 RedPWM_GetInterruptSourceMasked(void);
uint32 RedPWM_GetInterruptSource(void);
void   RedPWM_ClearInterrupt(uint32 interruptMask);
void   RedPWM_SetInterrupt(uint32 interruptMask);

void   RedPWM_WriteCounter(uint32 count);
uint32 RedPWM_ReadCounter(void);

uint32 RedPWM_ReadCapture(void);
uint32 RedPWM_ReadCaptureBuf(void);

void   RedPWM_WritePeriod(uint32 period);
uint32 RedPWM_ReadPeriod(void);
void   RedPWM_WritePeriodBuf(uint32 periodBuf);
uint32 RedPWM_ReadPeriodBuf(void);

void   RedPWM_WriteCompare(uint32 compare);
uint32 RedPWM_ReadCompare(void);
void   RedPWM_WriteCompareBuf(uint32 compareBuf);
uint32 RedPWM_ReadCompareBuf(void);

void   RedPWM_SetPeriodSwap(uint32 swapEnable);
void   RedPWM_SetCompareSwap(uint32 swapEnable);

void   RedPWM_SetCaptureMode(uint32 triggerMode);
void   RedPWM_SetReloadMode(uint32 triggerMode);
void   RedPWM_SetStartMode(uint32 triggerMode);
void   RedPWM_SetStopMode(uint32 triggerMode);
void   RedPWM_SetCountMode(uint32 triggerMode);

void   RedPWM_SaveConfig(void);
void   RedPWM_RestoreConfig(void);
void   RedPWM_Sleep(void);
void   RedPWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define RedPWM_BLOCK_CONTROL_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RedPWM_BLOCK_CONTROL_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define RedPWM_COMMAND_REG                    (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RedPWM_COMMAND_PTR                    ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define RedPWM_INTRRUPT_CAUSE_REG             (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RedPWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define RedPWM_CONTROL_REG                    (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__CTRL )
#define RedPWM_CONTROL_PTR                    ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__CTRL )
#define RedPWM_STATUS_REG                     (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__STATUS )
#define RedPWM_STATUS_PTR                     ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__STATUS )
#define RedPWM_COUNTER_REG                    (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__COUNTER )
#define RedPWM_COUNTER_PTR                    ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__COUNTER )
#define RedPWM_COMP_CAP_REG                   (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__CC )
#define RedPWM_COMP_CAP_PTR                   ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__CC )
#define RedPWM_COMP_CAP_BUF_REG               (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define RedPWM_COMP_CAP_BUF_PTR               ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define RedPWM_PERIOD_REG                     (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__PERIOD )
#define RedPWM_PERIOD_PTR                     ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__PERIOD )
#define RedPWM_PERIOD_BUF_REG                 (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RedPWM_PERIOD_BUF_PTR                 ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define RedPWM_TRIG_CONTROL0_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RedPWM_TRIG_CONTROL0_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define RedPWM_TRIG_CONTROL1_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RedPWM_TRIG_CONTROL1_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define RedPWM_TRIG_CONTROL2_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RedPWM_TRIG_CONTROL2_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define RedPWM_INTERRUPT_REQ_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR )
#define RedPWM_INTERRUPT_REQ_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR )
#define RedPWM_INTERRUPT_SET_REG              (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define RedPWM_INTERRUPT_SET_PTR              ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define RedPWM_INTERRUPT_MASK_REG             (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define RedPWM_INTERRUPT_MASK_PTR             ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define RedPWM_INTERRUPT_MASKED_REG           (*(reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define RedPWM_INTERRUPT_MASKED_PTR           ( (reg32 *) RedPWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define RedPWM_MASK                           ((uint32)RedPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define RedPWM_RELOAD_CC_SHIFT                (0u)
#define RedPWM_RELOAD_PERIOD_SHIFT            (1u)
#define RedPWM_PWM_SYNC_KILL_SHIFT            (2u)
#define RedPWM_PWM_STOP_KILL_SHIFT            (3u)
#define RedPWM_PRESCALER_SHIFT                (8u)
#define RedPWM_UPDOWN_SHIFT                   (16u)
#define RedPWM_ONESHOT_SHIFT                  (18u)
#define RedPWM_QUAD_MODE_SHIFT                (20u)
#define RedPWM_INV_OUT_SHIFT                  (20u)
#define RedPWM_INV_COMPL_OUT_SHIFT            (21u)
#define RedPWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define RedPWM_RELOAD_CC_MASK                 ((uint32)(RedPWM_1BIT_MASK        <<  \
                                                                            RedPWM_RELOAD_CC_SHIFT))
#define RedPWM_RELOAD_PERIOD_MASK             ((uint32)(RedPWM_1BIT_MASK        <<  \
                                                                            RedPWM_RELOAD_PERIOD_SHIFT))
#define RedPWM_PWM_SYNC_KILL_MASK             ((uint32)(RedPWM_1BIT_MASK        <<  \
                                                                            RedPWM_PWM_SYNC_KILL_SHIFT))
#define RedPWM_PWM_STOP_KILL_MASK             ((uint32)(RedPWM_1BIT_MASK        <<  \
                                                                            RedPWM_PWM_STOP_KILL_SHIFT))
#define RedPWM_PRESCALER_MASK                 ((uint32)(RedPWM_8BIT_MASK        <<  \
                                                                            RedPWM_PRESCALER_SHIFT))
#define RedPWM_UPDOWN_MASK                    ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                            RedPWM_UPDOWN_SHIFT))
#define RedPWM_ONESHOT_MASK                   ((uint32)(RedPWM_1BIT_MASK        <<  \
                                                                            RedPWM_ONESHOT_SHIFT))
#define RedPWM_QUAD_MODE_MASK                 ((uint32)(RedPWM_3BIT_MASK        <<  \
                                                                            RedPWM_QUAD_MODE_SHIFT))
#define RedPWM_INV_OUT_MASK                   ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                            RedPWM_INV_OUT_SHIFT))
#define RedPWM_MODE_MASK                      ((uint32)(RedPWM_3BIT_MASK        <<  \
                                                                            RedPWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define RedPWM_CAPTURE_SHIFT                  (0u)
#define RedPWM_COUNT_SHIFT                    (2u)
#define RedPWM_RELOAD_SHIFT                   (4u)
#define RedPWM_STOP_SHIFT                     (6u)
#define RedPWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define RedPWM_CAPTURE_MASK                   ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                  RedPWM_CAPTURE_SHIFT))
#define RedPWM_COUNT_MASK                     ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                  RedPWM_COUNT_SHIFT))
#define RedPWM_RELOAD_MASK                    ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                  RedPWM_RELOAD_SHIFT))
#define RedPWM_STOP_MASK                      ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                  RedPWM_STOP_SHIFT))
#define RedPWM_START_MASK                     ((uint32)(RedPWM_2BIT_MASK        <<  \
                                                                  RedPWM_START_SHIFT))

/* MASK */
#define RedPWM_1BIT_MASK                      ((uint32)0x01u)
#define RedPWM_2BIT_MASK                      ((uint32)0x03u)
#define RedPWM_3BIT_MASK                      ((uint32)0x07u)
#define RedPWM_6BIT_MASK                      ((uint32)0x3Fu)
#define RedPWM_8BIT_MASK                      ((uint32)0xFFu)
#define RedPWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define RedPWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define RedPWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(RedPWM_QUAD_ENCODING_MODES     << RedPWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(RedPWM_CONFIG                  << RedPWM_MODE_SHIFT)))

#define RedPWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(RedPWM_PWM_STOP_EVENT          << RedPWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(RedPWM_PWM_OUT_INVERT          << RedPWM_INV_OUT_SHIFT))         |\
         ((uint32)(RedPWM_PWM_OUT_N_INVERT        << RedPWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(RedPWM_PWM_MODE                << RedPWM_MODE_SHIFT)))

#define RedPWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(RedPWM_PWM_RUN_MODE         << RedPWM_ONESHOT_SHIFT))
            
#define RedPWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(RedPWM_PWM_ALIGN            << RedPWM_UPDOWN_SHIFT))

#define RedPWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(RedPWM_PWM_KILL_EVENT      << RedPWM_PWM_SYNC_KILL_SHIFT))

#define RedPWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(RedPWM_PWM_DEAD_TIME_CYCLE  << RedPWM_PRESCALER_SHIFT))

#define RedPWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(RedPWM_PWM_PRESCALER        << RedPWM_PRESCALER_SHIFT))

#define RedPWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(RedPWM_TC_PRESCALER            << RedPWM_PRESCALER_SHIFT))       |\
         ((uint32)(RedPWM_TC_COUNTER_MODE         << RedPWM_UPDOWN_SHIFT))          |\
         ((uint32)(RedPWM_TC_RUN_MODE             << RedPWM_ONESHOT_SHIFT))         |\
         ((uint32)(RedPWM_TC_COMP_CAP_MODE        << RedPWM_MODE_SHIFT)))
        
#define RedPWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(RedPWM_QUAD_PHIA_SIGNAL_MODE   << RedPWM_COUNT_SHIFT))           |\
         ((uint32)(RedPWM_QUAD_INDEX_SIGNAL_MODE  << RedPWM_RELOAD_SHIFT))          |\
         ((uint32)(RedPWM_QUAD_STOP_SIGNAL_MODE   << RedPWM_STOP_SHIFT))            |\
         ((uint32)(RedPWM_QUAD_PHIB_SIGNAL_MODE   << RedPWM_START_SHIFT)))

#define RedPWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(RedPWM_PWM_SWITCH_SIGNAL_MODE  << RedPWM_CAPTURE_SHIFT))         |\
         ((uint32)(RedPWM_PWM_COUNT_SIGNAL_MODE   << RedPWM_COUNT_SHIFT))           |\
         ((uint32)(RedPWM_PWM_RELOAD_SIGNAL_MODE  << RedPWM_RELOAD_SHIFT))          |\
         ((uint32)(RedPWM_PWM_STOP_SIGNAL_MODE    << RedPWM_STOP_SHIFT))            |\
         ((uint32)(RedPWM_PWM_START_SIGNAL_MODE   << RedPWM_START_SHIFT)))

#define RedPWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(RedPWM_TC_CAPTURE_SIGNAL_MODE  << RedPWM_CAPTURE_SHIFT))         |\
         ((uint32)(RedPWM_TC_COUNT_SIGNAL_MODE    << RedPWM_COUNT_SHIFT))           |\
         ((uint32)(RedPWM_TC_RELOAD_SIGNAL_MODE   << RedPWM_RELOAD_SHIFT))          |\
         ((uint32)(RedPWM_TC_STOP_SIGNAL_MODE     << RedPWM_STOP_SHIFT))            |\
         ((uint32)(RedPWM_TC_START_SIGNAL_MODE    << RedPWM_START_SHIFT)))
        
#define RedPWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((RedPWM__COUNT_UPDOWN0 == RedPWM_TC_COUNTER_MODE)                  ||\
                 (RedPWM__COUNT_UPDOWN1 == RedPWM_TC_COUNTER_MODE))

#define RedPWM_PWM_UPDOWN_CNT_USED                                                            \
                ((RedPWM__CENTER == RedPWM_PWM_ALIGN)                               ||\
                 (RedPWM__ASYMMETRIC == RedPWM_PWM_ALIGN))               
        
#define RedPWM_PWM_PR_INIT_VALUE              (1u)
#define RedPWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_RedPWM_H */

/* [] END OF FILE */
