/*******************************************************************************
* File Name: GreenPWM.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the GreenPWM
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

#if !defined(CY_TCPWM_GreenPWM_H)
#define CY_TCPWM_GreenPWM_H


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
} GreenPWM_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  GreenPWM_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define GreenPWM_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define GreenPWM_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define GreenPWM_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define GreenPWM_QUAD_ENCODING_MODES            (0lu)
#define GreenPWM_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define GreenPWM_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define GreenPWM_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define GreenPWM_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define GreenPWM_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define GreenPWM_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define GreenPWM_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define GreenPWM_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define GreenPWM_TC_RUN_MODE                    (0lu)
#define GreenPWM_TC_COUNTER_MODE                (0lu)
#define GreenPWM_TC_COMP_CAP_MODE               (2lu)
#define GreenPWM_TC_PRESCALER                   (0lu)

/* Signal modes */
#define GreenPWM_TC_RELOAD_SIGNAL_MODE          (0lu)
#define GreenPWM_TC_COUNT_SIGNAL_MODE           (3lu)
#define GreenPWM_TC_START_SIGNAL_MODE           (0lu)
#define GreenPWM_TC_STOP_SIGNAL_MODE            (0lu)
#define GreenPWM_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define GreenPWM_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define GreenPWM_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define GreenPWM_TC_START_SIGNAL_PRESENT        (0lu)
#define GreenPWM_TC_STOP_SIGNAL_PRESENT         (0lu)
#define GreenPWM_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define GreenPWM_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define GreenPWM_PWM_KILL_EVENT                 (0lu)
#define GreenPWM_PWM_STOP_EVENT                 (0lu)
#define GreenPWM_PWM_MODE                       (4lu)
#define GreenPWM_PWM_OUT_N_INVERT               (0lu)
#define GreenPWM_PWM_OUT_INVERT                 (0lu)
#define GreenPWM_PWM_ALIGN                      (0lu)
#define GreenPWM_PWM_RUN_MODE                   (0lu)
#define GreenPWM_PWM_DEAD_TIME_CYCLE            (0lu)
#define GreenPWM_PWM_PRESCALER                  (2lu)

/* Signal modes */
#define GreenPWM_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define GreenPWM_PWM_COUNT_SIGNAL_MODE          (3lu)
#define GreenPWM_PWM_START_SIGNAL_MODE          (0lu)
#define GreenPWM_PWM_STOP_SIGNAL_MODE           (0lu)
#define GreenPWM_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define GreenPWM_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define GreenPWM_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define GreenPWM_PWM_START_SIGNAL_PRESENT       (0lu)
#define GreenPWM_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define GreenPWM_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define GreenPWM_PWM_INTERRUPT_MASK             (0lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define GreenPWM_TC_PERIOD_VALUE                (65535lu)
#define GreenPWM_TC_COMPARE_VALUE               (65535lu)
#define GreenPWM_TC_COMPARE_BUF_VALUE           (65535lu)
#define GreenPWM_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define GreenPWM_PWM_PERIOD_VALUE               (255lu)
#define GreenPWM_PWM_PERIOD_BUF_VALUE           (65535lu)
#define GreenPWM_PWM_PERIOD_SWAP                (0lu)
#define GreenPWM_PWM_COMPARE_VALUE              (0lu)
#define GreenPWM_PWM_COMPARE_BUF_VALUE          (65535lu)
#define GreenPWM_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define GreenPWM__LEFT 0
#define GreenPWM__RIGHT 1
#define GreenPWM__CENTER 2
#define GreenPWM__ASYMMETRIC 3

#define GreenPWM__X1 0
#define GreenPWM__X2 1
#define GreenPWM__X4 2

#define GreenPWM__PWM 4
#define GreenPWM__PWM_DT 5
#define GreenPWM__PWM_PR 6

#define GreenPWM__INVERSE 1
#define GreenPWM__DIRECT 0

#define GreenPWM__CAPTURE 2
#define GreenPWM__COMPARE 0

#define GreenPWM__TRIG_LEVEL 3
#define GreenPWM__TRIG_RISING 0
#define GreenPWM__TRIG_FALLING 1
#define GreenPWM__TRIG_BOTH 2

#define GreenPWM__INTR_MASK_TC 1
#define GreenPWM__INTR_MASK_CC_MATCH 2
#define GreenPWM__INTR_MASK_NONE 0
#define GreenPWM__INTR_MASK_TC_CC 3

#define GreenPWM__UNCONFIG 8
#define GreenPWM__TIMER 1
#define GreenPWM__QUAD 3
#define GreenPWM__PWM_SEL 7

#define GreenPWM__COUNT_UP 0
#define GreenPWM__COUNT_DOWN 1
#define GreenPWM__COUNT_UPDOWN0 2
#define GreenPWM__COUNT_UPDOWN1 3


/* Prescaler */
#define GreenPWM_PRESCALE_DIVBY1                ((uint32)(0u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY2                ((uint32)(1u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY4                ((uint32)(2u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY8                ((uint32)(3u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY16               ((uint32)(4u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY32               ((uint32)(5u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY64               ((uint32)(6u << GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_PRESCALE_DIVBY128              ((uint32)(7u << GreenPWM_PRESCALER_SHIFT))

/* TCPWM set modes */
#define GreenPWM_MODE_TIMER_COMPARE             ((uint32)(GreenPWM__COMPARE         <<  \
                                                                  GreenPWM_MODE_SHIFT))
#define GreenPWM_MODE_TIMER_CAPTURE             ((uint32)(GreenPWM__CAPTURE         <<  \
                                                                  GreenPWM_MODE_SHIFT))
#define GreenPWM_MODE_QUAD                      ((uint32)(GreenPWM__QUAD            <<  \
                                                                  GreenPWM_MODE_SHIFT))
#define GreenPWM_MODE_PWM                       ((uint32)(GreenPWM__PWM             <<  \
                                                                  GreenPWM_MODE_SHIFT))
#define GreenPWM_MODE_PWM_DT                    ((uint32)(GreenPWM__PWM_DT          <<  \
                                                                  GreenPWM_MODE_SHIFT))
#define GreenPWM_MODE_PWM_PR                    ((uint32)(GreenPWM__PWM_PR          <<  \
                                                                  GreenPWM_MODE_SHIFT))

/* Quad Modes */
#define GreenPWM_MODE_X1                        ((uint32)(GreenPWM__X1              <<  \
                                                                  GreenPWM_QUAD_MODE_SHIFT))
#define GreenPWM_MODE_X2                        ((uint32)(GreenPWM__X2              <<  \
                                                                  GreenPWM_QUAD_MODE_SHIFT))
#define GreenPWM_MODE_X4                        ((uint32)(GreenPWM__X4              <<  \
                                                                  GreenPWM_QUAD_MODE_SHIFT))

/* Counter modes */
#define GreenPWM_COUNT_UP                       ((uint32)(GreenPWM__COUNT_UP        <<  \
                                                                  GreenPWM_UPDOWN_SHIFT))
#define GreenPWM_COUNT_DOWN                     ((uint32)(GreenPWM__COUNT_DOWN      <<  \
                                                                  GreenPWM_UPDOWN_SHIFT))
#define GreenPWM_COUNT_UPDOWN0                  ((uint32)(GreenPWM__COUNT_UPDOWN0   <<  \
                                                                  GreenPWM_UPDOWN_SHIFT))
#define GreenPWM_COUNT_UPDOWN1                  ((uint32)(GreenPWM__COUNT_UPDOWN1   <<  \
                                                                  GreenPWM_UPDOWN_SHIFT))

/* PWM output invert */
#define GreenPWM_INVERT_LINE                    ((uint32)(GreenPWM__INVERSE         <<  \
                                                                  GreenPWM_INV_OUT_SHIFT))
#define GreenPWM_INVERT_LINE_N                  ((uint32)(GreenPWM__INVERSE         <<  \
                                                                  GreenPWM_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define GreenPWM_TRIG_RISING                    ((uint32)GreenPWM__TRIG_RISING)
#define GreenPWM_TRIG_FALLING                   ((uint32)GreenPWM__TRIG_FALLING)
#define GreenPWM_TRIG_BOTH                      ((uint32)GreenPWM__TRIG_BOTH)
#define GreenPWM_TRIG_LEVEL                     ((uint32)GreenPWM__TRIG_LEVEL)

/* Interrupt mask */
#define GreenPWM_INTR_MASK_TC                   ((uint32)GreenPWM__INTR_MASK_TC)
#define GreenPWM_INTR_MASK_CC_MATCH             ((uint32)GreenPWM__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define GreenPWM_CC_MATCH_SET                   (0x00u)
#define GreenPWM_CC_MATCH_CLEAR                 (0x01u)
#define GreenPWM_CC_MATCH_INVERT                (0x02u)
#define GreenPWM_CC_MATCH_NO_CHANGE             (0x03u)
#define GreenPWM_OVERLOW_SET                    (0x00u)
#define GreenPWM_OVERLOW_CLEAR                  (0x04u)
#define GreenPWM_OVERLOW_INVERT                 (0x08u)
#define GreenPWM_OVERLOW_NO_CHANGE              (0x0Cu)
#define GreenPWM_UNDERFLOW_SET                  (0x00u)
#define GreenPWM_UNDERFLOW_CLEAR                (0x10u)
#define GreenPWM_UNDERFLOW_INVERT               (0x20u)
#define GreenPWM_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define GreenPWM_PWM_MODE_LEFT                  (GreenPWM_CC_MATCH_CLEAR        |   \
                                                         GreenPWM_OVERLOW_SET           |   \
                                                         GreenPWM_UNDERFLOW_NO_CHANGE)
#define GreenPWM_PWM_MODE_RIGHT                 (GreenPWM_CC_MATCH_SET          |   \
                                                         GreenPWM_OVERLOW_NO_CHANGE     |   \
                                                         GreenPWM_UNDERFLOW_CLEAR)
#define GreenPWM_PWM_MODE_ASYM                  (GreenPWM_CC_MATCH_INVERT       |   \
                                                         GreenPWM_OVERLOW_SET           |   \
                                                         GreenPWM_UNDERFLOW_CLEAR)

#if (GreenPWM_CY_TCPWM_V2)
    #if(GreenPWM_CY_TCPWM_4000)
        #define GreenPWM_PWM_MODE_CENTER                (GreenPWM_CC_MATCH_INVERT       |   \
                                                                 GreenPWM_OVERLOW_NO_CHANGE     |   \
                                                                 GreenPWM_UNDERFLOW_CLEAR)
    #else
        #define GreenPWM_PWM_MODE_CENTER                (GreenPWM_CC_MATCH_INVERT       |   \
                                                                 GreenPWM_OVERLOW_SET           |   \
                                                                 GreenPWM_UNDERFLOW_CLEAR)
    #endif /* (GreenPWM_CY_TCPWM_4000) */
#else
    #define GreenPWM_PWM_MODE_CENTER                (GreenPWM_CC_MATCH_INVERT       |   \
                                                             GreenPWM_OVERLOW_NO_CHANGE     |   \
                                                             GreenPWM_UNDERFLOW_CLEAR)
#endif /* (GreenPWM_CY_TCPWM_NEW) */

/* Command operations without condition */
#define GreenPWM_CMD_CAPTURE                    (0u)
#define GreenPWM_CMD_RELOAD                     (8u)
#define GreenPWM_CMD_STOP                       (16u)
#define GreenPWM_CMD_START                      (24u)

/* Status */
#define GreenPWM_STATUS_DOWN                    (1u)
#define GreenPWM_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   GreenPWM_Init(void);
void   GreenPWM_Enable(void);
void   GreenPWM_Start(void);
void   GreenPWM_Stop(void);

void   GreenPWM_SetMode(uint32 mode);
void   GreenPWM_SetCounterMode(uint32 counterMode);
void   GreenPWM_SetPWMMode(uint32 modeMask);
void   GreenPWM_SetQDMode(uint32 qdMode);

void   GreenPWM_SetPrescaler(uint32 prescaler);
void   GreenPWM_TriggerCommand(uint32 mask, uint32 command);
void   GreenPWM_SetOneShot(uint32 oneShotEnable);
uint32 GreenPWM_ReadStatus(void);

void   GreenPWM_SetPWMSyncKill(uint32 syncKillEnable);
void   GreenPWM_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   GreenPWM_SetPWMDeadTime(uint32 deadTime);
void   GreenPWM_SetPWMInvert(uint32 mask);

void   GreenPWM_SetInterruptMode(uint32 interruptMask);
uint32 GreenPWM_GetInterruptSourceMasked(void);
uint32 GreenPWM_GetInterruptSource(void);
void   GreenPWM_ClearInterrupt(uint32 interruptMask);
void   GreenPWM_SetInterrupt(uint32 interruptMask);

void   GreenPWM_WriteCounter(uint32 count);
uint32 GreenPWM_ReadCounter(void);

uint32 GreenPWM_ReadCapture(void);
uint32 GreenPWM_ReadCaptureBuf(void);

void   GreenPWM_WritePeriod(uint32 period);
uint32 GreenPWM_ReadPeriod(void);
void   GreenPWM_WritePeriodBuf(uint32 periodBuf);
uint32 GreenPWM_ReadPeriodBuf(void);

void   GreenPWM_WriteCompare(uint32 compare);
uint32 GreenPWM_ReadCompare(void);
void   GreenPWM_WriteCompareBuf(uint32 compareBuf);
uint32 GreenPWM_ReadCompareBuf(void);

void   GreenPWM_SetPeriodSwap(uint32 swapEnable);
void   GreenPWM_SetCompareSwap(uint32 swapEnable);

void   GreenPWM_SetCaptureMode(uint32 triggerMode);
void   GreenPWM_SetReloadMode(uint32 triggerMode);
void   GreenPWM_SetStartMode(uint32 triggerMode);
void   GreenPWM_SetStopMode(uint32 triggerMode);
void   GreenPWM_SetCountMode(uint32 triggerMode);

void   GreenPWM_SaveConfig(void);
void   GreenPWM_RestoreConfig(void);
void   GreenPWM_Sleep(void);
void   GreenPWM_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define GreenPWM_BLOCK_CONTROL_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define GreenPWM_BLOCK_CONTROL_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define GreenPWM_COMMAND_REG                    (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define GreenPWM_COMMAND_PTR                    ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define GreenPWM_INTRRUPT_CAUSE_REG             (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define GreenPWM_INTRRUPT_CAUSE_PTR             ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define GreenPWM_CONTROL_REG                    (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CTRL )
#define GreenPWM_CONTROL_PTR                    ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CTRL )
#define GreenPWM_STATUS_REG                     (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__STATUS )
#define GreenPWM_STATUS_PTR                     ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__STATUS )
#define GreenPWM_COUNTER_REG                    (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__COUNTER )
#define GreenPWM_COUNTER_PTR                    ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__COUNTER )
#define GreenPWM_COMP_CAP_REG                   (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CC )
#define GreenPWM_COMP_CAP_PTR                   ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CC )
#define GreenPWM_COMP_CAP_BUF_REG               (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define GreenPWM_COMP_CAP_BUF_PTR               ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__CC_BUFF )
#define GreenPWM_PERIOD_REG                     (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__PERIOD )
#define GreenPWM_PERIOD_PTR                     ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__PERIOD )
#define GreenPWM_PERIOD_BUF_REG                 (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define GreenPWM_PERIOD_BUF_PTR                 ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define GreenPWM_TRIG_CONTROL0_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define GreenPWM_TRIG_CONTROL0_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define GreenPWM_TRIG_CONTROL1_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define GreenPWM_TRIG_CONTROL1_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define GreenPWM_TRIG_CONTROL2_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define GreenPWM_TRIG_CONTROL2_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define GreenPWM_INTERRUPT_REQ_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR )
#define GreenPWM_INTERRUPT_REQ_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR )
#define GreenPWM_INTERRUPT_SET_REG              (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define GreenPWM_INTERRUPT_SET_PTR              ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_SET )
#define GreenPWM_INTERRUPT_MASK_REG             (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define GreenPWM_INTERRUPT_MASK_PTR             ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_MASK )
#define GreenPWM_INTERRUPT_MASKED_REG           (*(reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_MASKED )
#define GreenPWM_INTERRUPT_MASKED_PTR           ( (reg32 *) GreenPWM_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define GreenPWM_MASK                           ((uint32)GreenPWM_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define GreenPWM_RELOAD_CC_SHIFT                (0u)
#define GreenPWM_RELOAD_PERIOD_SHIFT            (1u)
#define GreenPWM_PWM_SYNC_KILL_SHIFT            (2u)
#define GreenPWM_PWM_STOP_KILL_SHIFT            (3u)
#define GreenPWM_PRESCALER_SHIFT                (8u)
#define GreenPWM_UPDOWN_SHIFT                   (16u)
#define GreenPWM_ONESHOT_SHIFT                  (18u)
#define GreenPWM_QUAD_MODE_SHIFT                (20u)
#define GreenPWM_INV_OUT_SHIFT                  (20u)
#define GreenPWM_INV_COMPL_OUT_SHIFT            (21u)
#define GreenPWM_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define GreenPWM_RELOAD_CC_MASK                 ((uint32)(GreenPWM_1BIT_MASK        <<  \
                                                                            GreenPWM_RELOAD_CC_SHIFT))
#define GreenPWM_RELOAD_PERIOD_MASK             ((uint32)(GreenPWM_1BIT_MASK        <<  \
                                                                            GreenPWM_RELOAD_PERIOD_SHIFT))
#define GreenPWM_PWM_SYNC_KILL_MASK             ((uint32)(GreenPWM_1BIT_MASK        <<  \
                                                                            GreenPWM_PWM_SYNC_KILL_SHIFT))
#define GreenPWM_PWM_STOP_KILL_MASK             ((uint32)(GreenPWM_1BIT_MASK        <<  \
                                                                            GreenPWM_PWM_STOP_KILL_SHIFT))
#define GreenPWM_PRESCALER_MASK                 ((uint32)(GreenPWM_8BIT_MASK        <<  \
                                                                            GreenPWM_PRESCALER_SHIFT))
#define GreenPWM_UPDOWN_MASK                    ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                            GreenPWM_UPDOWN_SHIFT))
#define GreenPWM_ONESHOT_MASK                   ((uint32)(GreenPWM_1BIT_MASK        <<  \
                                                                            GreenPWM_ONESHOT_SHIFT))
#define GreenPWM_QUAD_MODE_MASK                 ((uint32)(GreenPWM_3BIT_MASK        <<  \
                                                                            GreenPWM_QUAD_MODE_SHIFT))
#define GreenPWM_INV_OUT_MASK                   ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                            GreenPWM_INV_OUT_SHIFT))
#define GreenPWM_MODE_MASK                      ((uint32)(GreenPWM_3BIT_MASK        <<  \
                                                                            GreenPWM_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define GreenPWM_CAPTURE_SHIFT                  (0u)
#define GreenPWM_COUNT_SHIFT                    (2u)
#define GreenPWM_RELOAD_SHIFT                   (4u)
#define GreenPWM_STOP_SHIFT                     (6u)
#define GreenPWM_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define GreenPWM_CAPTURE_MASK                   ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                  GreenPWM_CAPTURE_SHIFT))
#define GreenPWM_COUNT_MASK                     ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                  GreenPWM_COUNT_SHIFT))
#define GreenPWM_RELOAD_MASK                    ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                  GreenPWM_RELOAD_SHIFT))
#define GreenPWM_STOP_MASK                      ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                  GreenPWM_STOP_SHIFT))
#define GreenPWM_START_MASK                     ((uint32)(GreenPWM_2BIT_MASK        <<  \
                                                                  GreenPWM_START_SHIFT))

/* MASK */
#define GreenPWM_1BIT_MASK                      ((uint32)0x01u)
#define GreenPWM_2BIT_MASK                      ((uint32)0x03u)
#define GreenPWM_3BIT_MASK                      ((uint32)0x07u)
#define GreenPWM_6BIT_MASK                      ((uint32)0x3Fu)
#define GreenPWM_8BIT_MASK                      ((uint32)0xFFu)
#define GreenPWM_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define GreenPWM_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define GreenPWM_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(GreenPWM_QUAD_ENCODING_MODES     << GreenPWM_QUAD_MODE_SHIFT))       |\
         ((uint32)(GreenPWM_CONFIG                  << GreenPWM_MODE_SHIFT)))

#define GreenPWM_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(GreenPWM_PWM_STOP_EVENT          << GreenPWM_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(GreenPWM_PWM_OUT_INVERT          << GreenPWM_INV_OUT_SHIFT))         |\
         ((uint32)(GreenPWM_PWM_OUT_N_INVERT        << GreenPWM_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(GreenPWM_PWM_MODE                << GreenPWM_MODE_SHIFT)))

#define GreenPWM_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(GreenPWM_PWM_RUN_MODE         << GreenPWM_ONESHOT_SHIFT))
            
#define GreenPWM_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(GreenPWM_PWM_ALIGN            << GreenPWM_UPDOWN_SHIFT))

#define GreenPWM_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(GreenPWM_PWM_KILL_EVENT      << GreenPWM_PWM_SYNC_KILL_SHIFT))

#define GreenPWM_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(GreenPWM_PWM_DEAD_TIME_CYCLE  << GreenPWM_PRESCALER_SHIFT))

#define GreenPWM_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(GreenPWM_PWM_PRESCALER        << GreenPWM_PRESCALER_SHIFT))

#define GreenPWM_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(GreenPWM_TC_PRESCALER            << GreenPWM_PRESCALER_SHIFT))       |\
         ((uint32)(GreenPWM_TC_COUNTER_MODE         << GreenPWM_UPDOWN_SHIFT))          |\
         ((uint32)(GreenPWM_TC_RUN_MODE             << GreenPWM_ONESHOT_SHIFT))         |\
         ((uint32)(GreenPWM_TC_COMP_CAP_MODE        << GreenPWM_MODE_SHIFT)))
        
#define GreenPWM_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(GreenPWM_QUAD_PHIA_SIGNAL_MODE   << GreenPWM_COUNT_SHIFT))           |\
         ((uint32)(GreenPWM_QUAD_INDEX_SIGNAL_MODE  << GreenPWM_RELOAD_SHIFT))          |\
         ((uint32)(GreenPWM_QUAD_STOP_SIGNAL_MODE   << GreenPWM_STOP_SHIFT))            |\
         ((uint32)(GreenPWM_QUAD_PHIB_SIGNAL_MODE   << GreenPWM_START_SHIFT)))

#define GreenPWM_PWM_SIGNALS_MODES                                                              \
        (((uint32)(GreenPWM_PWM_SWITCH_SIGNAL_MODE  << GreenPWM_CAPTURE_SHIFT))         |\
         ((uint32)(GreenPWM_PWM_COUNT_SIGNAL_MODE   << GreenPWM_COUNT_SHIFT))           |\
         ((uint32)(GreenPWM_PWM_RELOAD_SIGNAL_MODE  << GreenPWM_RELOAD_SHIFT))          |\
         ((uint32)(GreenPWM_PWM_STOP_SIGNAL_MODE    << GreenPWM_STOP_SHIFT))            |\
         ((uint32)(GreenPWM_PWM_START_SIGNAL_MODE   << GreenPWM_START_SHIFT)))

#define GreenPWM_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(GreenPWM_TC_CAPTURE_SIGNAL_MODE  << GreenPWM_CAPTURE_SHIFT))         |\
         ((uint32)(GreenPWM_TC_COUNT_SIGNAL_MODE    << GreenPWM_COUNT_SHIFT))           |\
         ((uint32)(GreenPWM_TC_RELOAD_SIGNAL_MODE   << GreenPWM_RELOAD_SHIFT))          |\
         ((uint32)(GreenPWM_TC_STOP_SIGNAL_MODE     << GreenPWM_STOP_SHIFT))            |\
         ((uint32)(GreenPWM_TC_START_SIGNAL_MODE    << GreenPWM_START_SHIFT)))
        
#define GreenPWM_TIMER_UPDOWN_CNT_USED                                                          \
                ((GreenPWM__COUNT_UPDOWN0 == GreenPWM_TC_COUNTER_MODE)                  ||\
                 (GreenPWM__COUNT_UPDOWN1 == GreenPWM_TC_COUNTER_MODE))

#define GreenPWM_PWM_UPDOWN_CNT_USED                                                            \
                ((GreenPWM__CENTER == GreenPWM_PWM_ALIGN)                               ||\
                 (GreenPWM__ASYMMETRIC == GreenPWM_PWM_ALIGN))               
        
#define GreenPWM_PWM_PR_INIT_VALUE              (1u)
#define GreenPWM_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_GreenPWM_H */

/* [] END OF FILE */
