/*******************************************************************************
* File Name: BluePWM.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the BluePWM
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

#if !defined(CY_TCPWM_BluePWM_H)
#define CY_TCPWM_BluePWM_H


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
} BluePWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  BluePWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define BluePWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define BluePWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define BluePWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define BluePWM_QUAD_ENCODING_MODES            (0lu)
#define BluePWM_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define BluePWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define BluePWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define BluePWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define BluePWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define BluePWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define BluePWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define BluePWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define BluePWM_TC_RUN_MODE                    (0lu)
#define BluePWM_TC_COUNTER_MODE                (0lu)
#define BluePWM_TC_COMP_CAP_MODE               (2lu)
#define BluePWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define BluePWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define BluePWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define BluePWM_TC_START_SIGNAL_MODE           (0lu)
#define BluePWM_TC_STOP_SIGNAL_MODE            (0lu)
#define BluePWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define BluePWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define BluePWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define BluePWM_TC_START_SIGNAL_PRESENT        (0lu)
#define BluePWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define BluePWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BluePWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define BluePWM_PWM_KILL_EVENT                 (0lu)
#define BluePWM_PWM_STOP_EVENT                 (0lu)
#define BluePWM_PWM_MODE                       (4lu)
#define BluePWM_PWM_OUT_N_INVERT               (0lu)
#define BluePWM_PWM_OUT_INVERT                 (0lu)
#define BluePWM_PWM_ALIGN                      (0lu)
#define BluePWM_PWM_RUN_MODE                   (0lu)
#define BluePWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define BluePWM_PWM_PRESCALER                  (2lu)

/* Signal modes */
#define BluePWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define BluePWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define BluePWM_PWM_START_SIGNAL_MODE          (0lu)
#define BluePWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define BluePWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define BluePWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define BluePWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define BluePWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define BluePWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define BluePWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define BluePWM_PWM_INTERRUPT_MASK             (0lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define BluePWM_TC_PERIOD_VALUE                (65535lu)
#define BluePWM_TC_COMPARE_VALUE               (65535lu)
#define BluePWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define BluePWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define BluePWM_PWM_PERIOD_VALUE               (255lu)
#define BluePWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define BluePWM_PWM_PERIOD_SWAP                (0lu)
#define BluePWM_PWM_COMPARE_VALUE              (0lu)
#define BluePWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define BluePWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define BluePWM__LEFT 0
#define BluePWM__RIGHT 1
#define BluePWM__CENTER 2
#define BluePWM__ASYMMETRIC 3

#define BluePWM__X1 0
#define BluePWM__X2 1
#define BluePWM__X4 2

#define BluePWM__PWM 4
#define BluePWM__PWM_DT 5
#define BluePWM__PWM_PR 6

#define BluePWM__INVERSE 1
#define BluePWM__DIRECT 0

#define BluePWM__CAPTURE 2
#define BluePWM__COMPARE 0

#define BluePWM__TRIG_LEVEL 3
#define BluePWM__TRIG_RISING 0
#define BluePWM__TRIG_FALLING 1
#define BluePWM__TRIG_BOTH 2

#define BluePWM__INTR_MASK_TC 1
#define BluePWM__INTR_MASK_CC_MATCH 2
#define BluePWM__INTR_MASK_NONE 0
#define BluePWM__INTR_MASK_TC_CC 3

#define BluePWM__UNCONFIG 8
#define BluePWM__TIMER 1
#define BluePWM__QUAD 3
#define BluePWM__PWM_SEL 7

#define BluePWM__COUNT_UP 0
#define BluePWM__COUNT_DOWN 1
#define BluePWM__COUNT_UPDOWN0 2
#define BluePWM__COUNT_UPDOWN1 3


/* Prescaler */
#define BluePWM_PRESCALE_DIVBY1                ((uint32)(0u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY2                ((uint32)(1u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY4                ((uint32)(2u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY8                ((uint32)(3u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY16               ((uint32)(4u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY32               ((uint32)(5u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY64               ((uint32)(6u << BluePWM_PRESCALER_SHIFT))
#define BluePWM_PRESCALE_DIVBY128              ((uint32)(7u << BluePWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define BluePWM_MODE_TIMER_COMPARE             ((uint32)(BluePWM__COMPARE         <<  \
                                                                  BluePWM_MODE_SHIFT))
#define BluePWM_MODE_TIMER_CAPTURE             ((uint32)(BluePWM__CAPTURE         <<  \
                                                                  BluePWM_MODE_SHIFT))
#define BluePWM_MODE_QUAD                      ((uint32)(BluePWM__QUAD            <<  \
                                                                  BluePWM_MODE_SHIFT))
#define BluePWM_MODE_PWM                       ((uint32)(BluePWM__PWM             <<  \
                                                                  BluePWM_MODE_SHIFT))
#define BluePWM_MODE_PWM_DT                    ((uint32)(BluePWM__PWM_DT          <<  \
                                                                  BluePWM_MODE_SHIFT))
#define BluePWM_MODE_PWM_PR                    ((uint32)(BluePWM__PWM_PR          <<  \
                                                                  BluePWM_MODE_SHIFT))

/* Quad Modes */
#define BluePWM_MODE_X1                        ((uint32)(BluePWM__X1              <<  \
                                                                  BluePWM_QUAD_MODE_SHIFT))
#define BluePWM_MODE_X2                        ((uint32)(BluePWM__X2              <<  \
                                                                  BluePWM_QUAD_MODE_SHIFT))
#define BluePWM_MODE_X4                        ((uint32)(BluePWM__X4              <<  \
                                                                  BluePWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define BluePWM_COUNT_UP                       ((uint32)(BluePWM__COUNT_UP        <<  \
                                                                  BluePWM_UPDOWN_SHIFT))
#define BluePWM_COUNT_DOWN                     ((uint32)(BluePWM__COUNT_DOWN      <<  \
                                                                  BluePWM_UPDOWN_SHIFT))
#define BluePWM_COUNT_UPDOWN0                  ((uint32)(BluePWM__COUNT_UPDOWN0   <<  \
                                                                  BluePWM_UPDOWN_SHIFT))
#define BluePWM_COUNT_UPDOWN1                  ((uint32)(BluePWM__COUNT_UPDOWN1   <<  \
                                                                  BluePWM_UPDOWN_SHIFT))

/* PWM output invert */
#define BluePWM_INVERT_LINE                    ((uint32)(BluePWM__INVERSE         <<  \
                                                                  BluePWM_INV_OUT_SHIFT))
#define BluePWM_INVERT_LINE_N                  ((uint32)(BluePWM__INVERSE         <<  \
                                                                  BluePWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define BluePWM_TRIG_RISING                    ((uint32)BluePWM__TRIG_RISING)
#define BluePWM_TRIG_FALLING                   ((uint32)BluePWM__TRIG_FALLING)
#define BluePWM_TRIG_BOTH                      ((uint32)BluePWM__TRIG_BOTH)
#define BluePWM_TRIG_LEVEL                     ((uint32)BluePWM__TRIG_LEVEL)

/* Interrupt mask */
#define BluePWM_INTR_MASK_TC                   ((uint32)BluePWM__INTR_MASK_TC)
#define BluePWM_INTR_MASK_CC_MATCH             ((uint32)BluePWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define BluePWM_CC_MATCH_SET                   (0x00u)
#define BluePWM_CC_MATCH_CLEAR                 (0x01u)
#define BluePWM_CC_MATCH_INVERT                (0x02u)
#define BluePWM_CC_MATCH_NO_CHANGE             (0x03u)
#define BluePWM_OVERLOW_SET                    (0x00u)
#define BluePWM_OVERLOW_CLEAR                  (0x04u)
#define BluePWM_OVERLOW_INVERT                 (0x08u)
#define BluePWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define BluePWM_UNDERFLOW_SET                  (0x00u)
#define BluePWM_UNDERFLOW_CLEAR                (0x10u)
#define BluePWM_UNDERFLOW_INVERT               (0x20u)
#define BluePWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define BluePWM_PWM_MODE_LEFT                  (BluePWM_CC_MATCH_CLEAR        |   \
                                                         BluePWM_OVERLOW_SET           |   \
                                                         BluePWM_UNDERFLOW_NO_CHANGE)
#define BluePWM_PWM_MODE_RIGHT                 (BluePWM_CC_MATCH_SET          |   \
                                                         BluePWM_OVERLOW_NO_CHANGE     |   \
                                                         BluePWM_UNDERFLOW_CLEAR)
#define BluePWM_PWM_MODE_ASYM                  (BluePWM_CC_MATCH_INVERT       |   \
                                                         BluePWM_OVERLOW_SET           |   \
                                                         BluePWM_UNDERFLOW_CLEAR)

#if (BluePWM_CY_TCPWM_V2)
    #if(BluePWM_CY_TCPWM_4000)
        #define BluePWM_PWM_MODE_CENTER                (BluePWM_CC_MATCH_INVERT       |   \
                                                                 BluePWM_OVERLOW_NO_CHANGE     |   \
                                                                 BluePWM_UNDERFLOW_CLEAR)
    #else
        #define BluePWM_PWM_MODE_CENTER                (BluePWM_CC_MATCH_INVERT       |   \
                                                                 BluePWM_OVERLOW_SET           |   \
                                                                 BluePWM_UNDERFLOW_CLEAR)
    #endif /* (BluePWM_CY_TCPWM_4000) */
#else
    #define BluePWM_PWM_MODE_CENTER                (BluePWM_CC_MATCH_INVERT       |   \
                                                             BluePWM_OVERLOW_NO_CHANGE     |   \
                                                             BluePWM_UNDERFLOW_CLEAR)
#endif /* (BluePWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define BluePWM_CMD_CAPTURE                    (0u)
#define BluePWM_CMD_RELOAD                     (8u)
#define BluePWM_CMD_STOP                       (16u)
#define BluePWM_CMD_START                      (24u)

/* Status */
#define BluePWM_STATUS_DOWN                    (1u)
#define BluePWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   BluePWM_Init(void);
void   BluePWM_Enable(void);
void   BluePWM_Start(void);
void   BluePWM_Stop(void);

void   BluePWM_SetMode(uint32 mode);
void   BluePWM_SetCounterMode(uint32 counterMode);
void   BluePWM_SetPWMMode(uint32 modeMask);
void   BluePWM_SetQDMode(uint32 qdMode);

void   BluePWM_SetPrescaler(uint32 prescaler);
void   BluePWM_TriggerCommand(uint32 mask, uint32 command);
void   BluePWM_SetOneShot(uint32 oneShotEnable);
uint32 BluePWM_ReadStatus(void);

void   BluePWM_SetPWMSyncKill(uint32 syncKillEnable);
void   BluePWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   BluePWM_SetPWMDeadTime(uint32 deadTime);
void   BluePWM_SetPWMInvert(uint32 mask);

void   BluePWM_SetInterruptMode(uint32 interruptMask);
uint32 BluePWM_GetInterruptSourceMasked(void);
uint32 BluePWM_GetInterruptSource(void);
void   BluePWM_ClearInterrupt(uint32 interruptMask);
void   BluePWM_SetInterrupt(uint32 interruptMask);

void   BluePWM_WriteCounter(uint32 count);
uint32 BluePWM_ReadCounter(void);

uint32 BluePWM_ReadCapture(void);
uint32 BluePWM_ReadCaptureBuf(void);

void   BluePWM_WritePeriod(uint32 period);
uint32 BluePWM_ReadPeriod(void);
void   BluePWM_WritePeriodBuf(uint32 periodBuf);
uint32 BluePWM_ReadPeriodBuf(void);

void   BluePWM_WriteCompare(uint32 compare);
uint32 BluePWM_ReadCompare(void);
void   BluePWM_WriteCompareBuf(uint32 compareBuf);
uint32 BluePWM_ReadCompareBuf(void);

void   BluePWM_SetPeriodSwap(uint32 swapEnable);
void   BluePWM_SetCompareSwap(uint32 swapEnable);

void   BluePWM_SetCaptureMode(uint32 triggerMode);
void   BluePWM_SetReloadMode(uint32 triggerMode);
void   BluePWM_SetStartMode(uint32 triggerMode);
void   BluePWM_SetStopMode(uint32 triggerMode);
void   BluePWM_SetCountMode(uint32 triggerMode);

void   BluePWM_SaveConfig(void);
void   BluePWM_RestoreConfig(void);
void   BluePWM_Sleep(void);
void   BluePWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define BluePWM_BLOCK_CONTROL_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BluePWM_BLOCK_CONTROL_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define BluePWM_COMMAND_REG                    (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BluePWM_COMMAND_PTR                    ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define BluePWM_INTRRUPT_CAUSE_REG             (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BluePWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define BluePWM_CONTROL_REG                    (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__CTRL )
#define BluePWM_CONTROL_PTR                    ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__CTRL )
#define BluePWM_STATUS_REG                     (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__STATUS )
#define BluePWM_STATUS_PTR                     ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__STATUS )
#define BluePWM_COUNTER_REG                    (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__COUNTER )
#define BluePWM_COUNTER_PTR                    ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__COUNTER )
#define BluePWM_COMP_CAP_REG                   (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__CC )
#define BluePWM_COMP_CAP_PTR                   ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__CC )
#define BluePWM_COMP_CAP_BUF_REG               (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define BluePWM_COMP_CAP_BUF_PTR               ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define BluePWM_PERIOD_REG                     (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__PERIOD )
#define BluePWM_PERIOD_PTR                     ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__PERIOD )
#define BluePWM_PERIOD_BUF_REG                 (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BluePWM_PERIOD_BUF_PTR                 ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define BluePWM_TRIG_CONTROL0_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BluePWM_TRIG_CONTROL0_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define BluePWM_TRIG_CONTROL1_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BluePWM_TRIG_CONTROL1_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define BluePWM_TRIG_CONTROL2_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BluePWM_TRIG_CONTROL2_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define BluePWM_INTERRUPT_REQ_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR )
#define BluePWM_INTERRUPT_REQ_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR )
#define BluePWM_INTERRUPT_SET_REG              (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_SET )
#define BluePWM_INTERRUPT_SET_PTR              ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_SET )
#define BluePWM_INTERRUPT_MASK_REG             (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define BluePWM_INTERRUPT_MASK_PTR             ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define BluePWM_INTERRUPT_MASKED_REG           (*(reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define BluePWM_INTERRUPT_MASKED_PTR           ( (reg32 *) BluePWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define BluePWM_MASK                           ((uint32)BluePWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define BluePWM_RELOAD_CC_SHIFT                (0u)
#define BluePWM_RELOAD_PERIOD_SHIFT            (1u)
#define BluePWM_PWM_SYNC_KILL_SHIFT            (2u)
#define BluePWM_PWM_STOP_KILL_SHIFT            (3u)
#define BluePWM_PRESCALER_SHIFT                (8u)
#define BluePWM_UPDOWN_SHIFT                   (16u)
#define BluePWM_ONESHOT_SHIFT                  (18u)
#define BluePWM_QUAD_MODE_SHIFT                (20u)
#define BluePWM_INV_OUT_SHIFT                  (20u)
#define BluePWM_INV_COMPL_OUT_SHIFT            (21u)
#define BluePWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define BluePWM_RELOAD_CC_MASK                 ((uint32)(BluePWM_1BIT_MASK        <<  \
                                                                            BluePWM_RELOAD_CC_SHIFT))
#define BluePWM_RELOAD_PERIOD_MASK             ((uint32)(BluePWM_1BIT_MASK        <<  \
                                                                            BluePWM_RELOAD_PERIOD_SHIFT))
#define BluePWM_PWM_SYNC_KILL_MASK             ((uint32)(BluePWM_1BIT_MASK        <<  \
                                                                            BluePWM_PWM_SYNC_KILL_SHIFT))
#define BluePWM_PWM_STOP_KILL_MASK             ((uint32)(BluePWM_1BIT_MASK        <<  \
                                                                            BluePWM_PWM_STOP_KILL_SHIFT))
#define BluePWM_PRESCALER_MASK                 ((uint32)(BluePWM_8BIT_MASK        <<  \
                                                                            BluePWM_PRESCALER_SHIFT))
#define BluePWM_UPDOWN_MASK                    ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                            BluePWM_UPDOWN_SHIFT))
#define BluePWM_ONESHOT_MASK                   ((uint32)(BluePWM_1BIT_MASK        <<  \
                                                                            BluePWM_ONESHOT_SHIFT))
#define BluePWM_QUAD_MODE_MASK                 ((uint32)(BluePWM_3BIT_MASK        <<  \
                                                                            BluePWM_QUAD_MODE_SHIFT))
#define BluePWM_INV_OUT_MASK                   ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                            BluePWM_INV_OUT_SHIFT))
#define BluePWM_MODE_MASK                      ((uint32)(BluePWM_3BIT_MASK        <<  \
                                                                            BluePWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define BluePWM_CAPTURE_SHIFT                  (0u)
#define BluePWM_COUNT_SHIFT                    (2u)
#define BluePWM_RELOAD_SHIFT                   (4u)
#define BluePWM_STOP_SHIFT                     (6u)
#define BluePWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define BluePWM_CAPTURE_MASK                   ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                  BluePWM_CAPTURE_SHIFT))
#define BluePWM_COUNT_MASK                     ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                  BluePWM_COUNT_SHIFT))
#define BluePWM_RELOAD_MASK                    ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                  BluePWM_RELOAD_SHIFT))
#define BluePWM_STOP_MASK                      ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                  BluePWM_STOP_SHIFT))
#define BluePWM_START_MASK                     ((uint32)(BluePWM_2BIT_MASK        <<  \
                                                                  BluePWM_START_SHIFT))

/* MASK */
#define BluePWM_1BIT_MASK                      ((uint32)0x01u)
#define BluePWM_2BIT_MASK                      ((uint32)0x03u)
#define BluePWM_3BIT_MASK                      ((uint32)0x07u)
#define BluePWM_6BIT_MASK                      ((uint32)0x3Fu)
#define BluePWM_8BIT_MASK                      ((uint32)0xFFu)
#define BluePWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define BluePWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define BluePWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(BluePWM_QUAD_ENCODING_MODES     << BluePWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(BluePWM_CONFIG                  << BluePWM_MODE_SHIFT)))

#define BluePWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(BluePWM_PWM_STOP_EVENT          << BluePWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(BluePWM_PWM_OUT_INVERT          << BluePWM_INV_OUT_SHIFT))         |\
         ((uint32)(BluePWM_PWM_OUT_N_INVERT        << BluePWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(BluePWM_PWM_MODE                << BluePWM_MODE_SHIFT)))

#define BluePWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(BluePWM_PWM_RUN_MODE         << BluePWM_ONESHOT_SHIFT))
            
#define BluePWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(BluePWM_PWM_ALIGN            << BluePWM_UPDOWN_SHIFT))

#define BluePWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(BluePWM_PWM_KILL_EVENT      << BluePWM_PWM_SYNC_KILL_SHIFT))

#define BluePWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(BluePWM_PWM_DEAD_TIME_CYCLE  << BluePWM_PRESCALER_SHIFT))

#define BluePWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(BluePWM_PWM_PRESCALER        << BluePWM_PRESCALER_SHIFT))

#define BluePWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(BluePWM_TC_PRESCALER            << BluePWM_PRESCALER_SHIFT))       |\
         ((uint32)(BluePWM_TC_COUNTER_MODE         << BluePWM_UPDOWN_SHIFT))          |\
         ((uint32)(BluePWM_TC_RUN_MODE             << BluePWM_ONESHOT_SHIFT))         |\
         ((uint32)(BluePWM_TC_COMP_CAP_MODE        << BluePWM_MODE_SHIFT)))
        
#define BluePWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(BluePWM_QUAD_PHIA_SIGNAL_MODE   << BluePWM_COUNT_SHIFT))           |\
         ((uint32)(BluePWM_QUAD_INDEX_SIGNAL_MODE  << BluePWM_RELOAD_SHIFT))          |\
         ((uint32)(BluePWM_QUAD_STOP_SIGNAL_MODE   << BluePWM_STOP_SHIFT))            |\
         ((uint32)(BluePWM_QUAD_PHIB_SIGNAL_MODE   << BluePWM_START_SHIFT)))

#define BluePWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(BluePWM_PWM_SWITCH_SIGNAL_MODE  << BluePWM_CAPTURE_SHIFT))         |\
         ((uint32)(BluePWM_PWM_COUNT_SIGNAL_MODE   << BluePWM_COUNT_SHIFT))           |\
         ((uint32)(BluePWM_PWM_RELOAD_SIGNAL_MODE  << BluePWM_RELOAD_SHIFT))          |\
         ((uint32)(BluePWM_PWM_STOP_SIGNAL_MODE    << BluePWM_STOP_SHIFT))            |\
         ((uint32)(BluePWM_PWM_START_SIGNAL_MODE   << BluePWM_START_SHIFT)))

#define BluePWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(BluePWM_TC_CAPTURE_SIGNAL_MODE  << BluePWM_CAPTURE_SHIFT))         |\
         ((uint32)(BluePWM_TC_COUNT_SIGNAL_MODE    << BluePWM_COUNT_SHIFT))           |\
         ((uint32)(BluePWM_TC_RELOAD_SIGNAL_MODE   << BluePWM_RELOAD_SHIFT))          |\
         ((uint32)(BluePWM_TC_STOP_SIGNAL_MODE     << BluePWM_STOP_SHIFT))            |\
         ((uint32)(BluePWM_TC_START_SIGNAL_MODE    << BluePWM_START_SHIFT)))
        
#define BluePWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((BluePWM__COUNT_UPDOWN0 == BluePWM_TC_COUNTER_MODE)                  ||\
                 (BluePWM__COUNT_UPDOWN1 == BluePWM_TC_COUNTER_MODE))

#define BluePWM_PWM_UPDOWN_CNT_USED                                                            \
                ((BluePWM__CENTER == BluePWM_PWM_ALIGN)                               ||\
                 (BluePWM__ASYMMETRIC == BluePWM_PWM_ALIGN))               
        
#define BluePWM_PWM_PR_INIT_VALUE              (1u)
#define BluePWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_BluePWM_H */

/* [] END OF FILE */
