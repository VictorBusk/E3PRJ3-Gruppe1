/*******************************************************************************
* File Name: GreenPWM.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the GreenPWM
*  component
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

#include "GreenPWM.h"

uint8 GreenPWM_initVar = 0u;


/*******************************************************************************
* Function Name: GreenPWM_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default GreenPWM configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (GreenPWM__QUAD == GreenPWM_CONFIG)
        GreenPWM_CONTROL_REG = GreenPWM_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        GreenPWM_TRIG_CONTROL1_REG  = GreenPWM_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        GreenPWM_SetInterruptMode(GreenPWM_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        GreenPWM_SetCounterMode(GreenPWM_COUNT_DOWN);
        GreenPWM_WritePeriod(GreenPWM_QUAD_PERIOD_INIT_VALUE);
        GreenPWM_WriteCounter(GreenPWM_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (GreenPWM__QUAD == GreenPWM_CONFIG) */

    #if (GreenPWM__TIMER == GreenPWM_CONFIG)
        GreenPWM_CONTROL_REG = GreenPWM_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        GreenPWM_TRIG_CONTROL1_REG  = GreenPWM_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        GreenPWM_SetInterruptMode(GreenPWM_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        GreenPWM_WritePeriod(GreenPWM_TC_PERIOD_VALUE );

        #if (GreenPWM__COMPARE == GreenPWM_TC_COMP_CAP_MODE)
            GreenPWM_WriteCompare(GreenPWM_TC_COMPARE_VALUE);

            #if (1u == GreenPWM_TC_COMPARE_SWAP)
                GreenPWM_SetCompareSwap(1u);
                GreenPWM_WriteCompareBuf(GreenPWM_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == GreenPWM_TC_COMPARE_SWAP) */
        #endif  /* (GreenPWM__COMPARE == GreenPWM_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (GreenPWM_CY_TCPWM_V2 && GreenPWM_TIMER_UPDOWN_CNT_USED && !GreenPWM_CY_TCPWM_4000)
            GreenPWM_WriteCounter(1u);
        #elif(GreenPWM__COUNT_DOWN == GreenPWM_TC_COUNTER_MODE)
            GreenPWM_WriteCounter(GreenPWM_TC_PERIOD_VALUE);
        #else
            GreenPWM_WriteCounter(0u);
        #endif /* (GreenPWM_CY_TCPWM_V2 && GreenPWM_TIMER_UPDOWN_CNT_USED && !GreenPWM_CY_TCPWM_4000) */
    #endif  /* (GreenPWM__TIMER == GreenPWM_CONFIG) */

    #if (GreenPWM__PWM_SEL == GreenPWM_CONFIG)
        GreenPWM_CONTROL_REG = GreenPWM_CTRL_PWM_BASE_CONFIG;

        #if (GreenPWM__PWM_PR == GreenPWM_PWM_MODE)
            GreenPWM_CONTROL_REG |= GreenPWM_CTRL_PWM_RUN_MODE;
            GreenPWM_WriteCounter(GreenPWM_PWM_PR_INIT_VALUE);
        #else
            GreenPWM_CONTROL_REG |= GreenPWM_CTRL_PWM_ALIGN | GreenPWM_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (GreenPWM_CY_TCPWM_V2 && GreenPWM_PWM_UPDOWN_CNT_USED && !GreenPWM_CY_TCPWM_4000)
                GreenPWM_WriteCounter(1u);
            #elif (GreenPWM__RIGHT == GreenPWM_PWM_ALIGN)
                GreenPWM_WriteCounter(GreenPWM_PWM_PERIOD_VALUE);
            #else 
                GreenPWM_WriteCounter(0u);
            #endif  /* (GreenPWM_CY_TCPWM_V2 && GreenPWM_PWM_UPDOWN_CNT_USED && !GreenPWM_CY_TCPWM_4000) */
        #endif  /* (GreenPWM__PWM_PR == GreenPWM_PWM_MODE) */

        #if (GreenPWM__PWM_DT == GreenPWM_PWM_MODE)
            GreenPWM_CONTROL_REG |= GreenPWM_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (GreenPWM__PWM_DT == GreenPWM_PWM_MODE) */

        #if (GreenPWM__PWM == GreenPWM_PWM_MODE)
            GreenPWM_CONTROL_REG |= GreenPWM_CTRL_PWM_PRESCALER;
        #endif  /* (GreenPWM__PWM == GreenPWM_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        GreenPWM_TRIG_CONTROL1_REG  = GreenPWM_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        GreenPWM_SetInterruptMode(GreenPWM_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (GreenPWM__PWM_PR == GreenPWM_PWM_MODE)
            GreenPWM_TRIG_CONTROL2_REG =
                    (GreenPWM_CC_MATCH_NO_CHANGE    |
                    GreenPWM_OVERLOW_NO_CHANGE      |
                    GreenPWM_UNDERFLOW_NO_CHANGE);
        #else
            #if (GreenPWM__LEFT == GreenPWM_PWM_ALIGN)
                GreenPWM_TRIG_CONTROL2_REG = GreenPWM_PWM_MODE_LEFT;
            #endif  /* ( GreenPWM_PWM_LEFT == GreenPWM_PWM_ALIGN) */

            #if (GreenPWM__RIGHT == GreenPWM_PWM_ALIGN)
                GreenPWM_TRIG_CONTROL2_REG = GreenPWM_PWM_MODE_RIGHT;
            #endif  /* ( GreenPWM_PWM_RIGHT == GreenPWM_PWM_ALIGN) */

            #if (GreenPWM__CENTER == GreenPWM_PWM_ALIGN)
                GreenPWM_TRIG_CONTROL2_REG = GreenPWM_PWM_MODE_CENTER;
            #endif  /* ( GreenPWM_PWM_CENTER == GreenPWM_PWM_ALIGN) */

            #if (GreenPWM__ASYMMETRIC == GreenPWM_PWM_ALIGN)
                GreenPWM_TRIG_CONTROL2_REG = GreenPWM_PWM_MODE_ASYM;
            #endif  /* (GreenPWM__ASYMMETRIC == GreenPWM_PWM_ALIGN) */
        #endif  /* (GreenPWM__PWM_PR == GreenPWM_PWM_MODE) */

        /* Set other values from customizer */
        GreenPWM_WritePeriod(GreenPWM_PWM_PERIOD_VALUE );
        GreenPWM_WriteCompare(GreenPWM_PWM_COMPARE_VALUE);

        #if (1u == GreenPWM_PWM_COMPARE_SWAP)
            GreenPWM_SetCompareSwap(1u);
            GreenPWM_WriteCompareBuf(GreenPWM_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == GreenPWM_PWM_COMPARE_SWAP) */

        #if (1u == GreenPWM_PWM_PERIOD_SWAP)
            GreenPWM_SetPeriodSwap(1u);
            GreenPWM_WritePeriodBuf(GreenPWM_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == GreenPWM_PWM_PERIOD_SWAP) */
    #endif  /* (GreenPWM__PWM_SEL == GreenPWM_CONFIG) */
    
}


/*******************************************************************************
* Function Name: GreenPWM_Enable
********************************************************************************
*
* Summary:
*  Enables the GreenPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    GreenPWM_BLOCK_CONTROL_REG |= GreenPWM_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (GreenPWM__PWM_SEL == GreenPWM_CONFIG)
        #if (0u == GreenPWM_PWM_START_SIGNAL_PRESENT)
            GreenPWM_TriggerCommand(GreenPWM_MASK, GreenPWM_CMD_START);
        #endif /* (0u == GreenPWM_PWM_START_SIGNAL_PRESENT) */
    #endif /* (GreenPWM__PWM_SEL == GreenPWM_CONFIG) */

    #if (GreenPWM__TIMER == GreenPWM_CONFIG)
        #if (0u == GreenPWM_TC_START_SIGNAL_PRESENT)
            GreenPWM_TriggerCommand(GreenPWM_MASK, GreenPWM_CMD_START);
        #endif /* (0u == GreenPWM_TC_START_SIGNAL_PRESENT) */
    #endif /* (GreenPWM__TIMER == GreenPWM_CONFIG) */
    
    #if (GreenPWM__QUAD == GreenPWM_CONFIG)
        #if (0u != GreenPWM_QUAD_AUTO_START)
            GreenPWM_TriggerCommand(GreenPWM_MASK, GreenPWM_CMD_RELOAD);
        #endif /* (0u != GreenPWM_QUAD_AUTO_START) */
    #endif  /* (GreenPWM__QUAD == GreenPWM_CONFIG) */
}


/*******************************************************************************
* Function Name: GreenPWM_Start
********************************************************************************
*
* Summary:
*  Initializes the GreenPWM with default customizer
*  values when called the first time and enables the GreenPWM.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  GreenPWM_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time GreenPWM_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the GreenPWM_Start() routine.
*
*******************************************************************************/
void GreenPWM_Start(void)
{
    if (0u == GreenPWM_initVar)
    {
        GreenPWM_Init();
        GreenPWM_initVar = 1u;
    }

    GreenPWM_Enable();
}


/*******************************************************************************
* Function Name: GreenPWM_Stop
********************************************************************************
*
* Summary:
*  Disables the GreenPWM.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_BLOCK_CONTROL_REG &= (uint32)~GreenPWM_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the GreenPWM. This function is used when
*  configured as a generic GreenPWM and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the GreenPWM to operate in
*   Values:
*   - GreenPWM_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - GreenPWM_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - GreenPWM_MODE_QUAD - Quadrature decoder
*         - GreenPWM_MODE_PWM - PWM
*         - GreenPWM_MODE_PWM_DT - PWM with dead time
*         - GreenPWM_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_MODE_MASK;
    GreenPWM_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - GreenPWM_MODE_X1 - Counts on phi 1 rising
*         - GreenPWM_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - GreenPWM_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_QUAD_MODE_MASK;
    GreenPWM_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - GreenPWM_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - GreenPWM_PRESCALE_DIVBY2    - Divide by 2
*         - GreenPWM_PRESCALE_DIVBY4    - Divide by 4
*         - GreenPWM_PRESCALE_DIVBY8    - Divide by 8
*         - GreenPWM_PRESCALE_DIVBY16   - Divide by 16
*         - GreenPWM_PRESCALE_DIVBY32   - Divide by 32
*         - GreenPWM_PRESCALE_DIVBY64   - Divide by 64
*         - GreenPWM_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_PRESCALER_MASK;
    GreenPWM_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the GreenPWM runs
*  continuously or stops when terminal count is reached.  By default the
*  GreenPWM operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_ONESHOT_MASK;
    GreenPWM_CONTROL_REG |= ((uint32)((oneShotEnable & GreenPWM_1BIT_MASK) <<
                                                               GreenPWM_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPWMMode(uint32 modeMask)
{
    GreenPWM_TRIG_CONTROL2_REG = (modeMask & GreenPWM_6BIT_MASK);
}



/*******************************************************************************
* Function Name: GreenPWM_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_PWM_SYNC_KILL_MASK;
    GreenPWM_CONTROL_REG |= ((uint32)((syncKillEnable & GreenPWM_1BIT_MASK)  <<
                                               GreenPWM_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_PWM_STOP_KILL_MASK;
    GreenPWM_CONTROL_REG |= ((uint32)((stopOnKillEnable & GreenPWM_1BIT_MASK)  <<
                                                         GreenPWM_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_PRESCALER_MASK;
    GreenPWM_CONTROL_REG |= ((uint32)((deadTime & GreenPWM_8BIT_MASK) <<
                                                          GreenPWM_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - GreenPWM_INVERT_LINE   - Inverts the line output
*         - GreenPWM_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_INV_OUT_MASK;
    GreenPWM_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: GreenPWM_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_WriteCounter(uint32 count)
{
    GreenPWM_COUNTER_REG = (count & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 GreenPWM_ReadCounter(void)
{
    return (GreenPWM_COUNTER_REG & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - GreenPWM_COUNT_UP       - Counts up
*     - GreenPWM_COUNT_DOWN     - Counts down
*     - GreenPWM_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - GreenPWM_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_UPDOWN_MASK;
    GreenPWM_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_WritePeriod(uint32 period)
{
    GreenPWM_PERIOD_REG = (period & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 GreenPWM_ReadPeriod(void)
{
    return (GreenPWM_PERIOD_REG & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_RELOAD_CC_MASK;
    GreenPWM_CONTROL_REG |= (swapEnable & GreenPWM_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_WritePeriodBuf(uint32 periodBuf)
{
    GreenPWM_PERIOD_BUF_REG = (periodBuf & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 GreenPWM_ReadPeriodBuf(void)
{
    return (GreenPWM_PERIOD_BUF_REG & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_CONTROL_REG &= (uint32)~GreenPWM_RELOAD_PERIOD_MASK;
    GreenPWM_CONTROL_REG |= ((uint32)((swapEnable & GreenPWM_1BIT_MASK) <<
                                                            GreenPWM_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void GreenPWM_WriteCompare(uint32 compare)
{
    #if (GreenPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (GreenPWM_CY_TCPWM_4000) */

    #if (GreenPWM_CY_TCPWM_4000)
        currentMode = ((GreenPWM_CONTROL_REG & GreenPWM_UPDOWN_MASK) >> GreenPWM_UPDOWN_SHIFT);

        if (((uint32)GreenPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)GreenPWM__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (GreenPWM_CY_TCPWM_4000) */
    
    GreenPWM_COMP_CAP_REG = (compare & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 GreenPWM_ReadCompare(void)
{
    #if (GreenPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (GreenPWM_CY_TCPWM_4000) */

    #if (GreenPWM_CY_TCPWM_4000)
        currentMode = ((GreenPWM_CONTROL_REG & GreenPWM_UPDOWN_MASK) >> GreenPWM_UPDOWN_SHIFT);
        
        regVal = GreenPWM_COMP_CAP_REG;
        
        if (((uint32)GreenPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)GreenPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & GreenPWM_16BIT_MASK);
    #else
        return (GreenPWM_COMP_CAP_REG & GreenPWM_16BIT_MASK);
    #endif /* (GreenPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: GreenPWM_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void GreenPWM_WriteCompareBuf(uint32 compareBuf)
{
    #if (GreenPWM_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (GreenPWM_CY_TCPWM_4000) */

    #if (GreenPWM_CY_TCPWM_4000)
        currentMode = ((GreenPWM_CONTROL_REG & GreenPWM_UPDOWN_MASK) >> GreenPWM_UPDOWN_SHIFT);

        if (((uint32)GreenPWM__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)GreenPWM__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (GreenPWM_CY_TCPWM_4000) */
    
    GreenPWM_COMP_CAP_BUF_REG = (compareBuf & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 GreenPWM_ReadCompareBuf(void)
{
    #if (GreenPWM_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (GreenPWM_CY_TCPWM_4000) */

    #if (GreenPWM_CY_TCPWM_4000)
        currentMode = ((GreenPWM_CONTROL_REG & GreenPWM_UPDOWN_MASK) >> GreenPWM_UPDOWN_SHIFT);

        regVal = GreenPWM_COMP_CAP_BUF_REG;
        
        if (((uint32)GreenPWM__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)GreenPWM__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & GreenPWM_16BIT_MASK);
    #else
        return (GreenPWM_COMP_CAP_BUF_REG & GreenPWM_16BIT_MASK);
    #endif /* (GreenPWM_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: GreenPWM_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 GreenPWM_ReadCapture(void)
{
    return (GreenPWM_COMP_CAP_REG & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 GreenPWM_ReadCaptureBuf(void)
{
    return (GreenPWM_COMP_CAP_BUF_REG & GreenPWM_16BIT_MASK);
}


/*******************************************************************************
* Function Name: GreenPWM_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - GreenPWM_TRIG_LEVEL     - Level
*     - GreenPWM_TRIG_RISING    - Rising edge
*     - GreenPWM_TRIG_FALLING   - Falling edge
*     - GreenPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_TRIG_CONTROL1_REG &= (uint32)~GreenPWM_CAPTURE_MASK;
    GreenPWM_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - GreenPWM_TRIG_LEVEL     - Level
*     - GreenPWM_TRIG_RISING    - Rising edge
*     - GreenPWM_TRIG_FALLING   - Falling edge
*     - GreenPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_TRIG_CONTROL1_REG &= (uint32)~GreenPWM_RELOAD_MASK;
    GreenPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << GreenPWM_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - GreenPWM_TRIG_LEVEL     - Level
*     - GreenPWM_TRIG_RISING    - Rising edge
*     - GreenPWM_TRIG_FALLING   - Falling edge
*     - GreenPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_TRIG_CONTROL1_REG &= (uint32)~GreenPWM_START_MASK;
    GreenPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << GreenPWM_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - GreenPWM_TRIG_LEVEL     - Level
*     - GreenPWM_TRIG_RISING    - Rising edge
*     - GreenPWM_TRIG_FALLING   - Falling edge
*     - GreenPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_TRIG_CONTROL1_REG &= (uint32)~GreenPWM_STOP_MASK;
    GreenPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << GreenPWM_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - GreenPWM_TRIG_LEVEL     - Level
*     - GreenPWM_TRIG_RISING    - Rising edge
*     - GreenPWM_TRIG_FALLING   - Falling edge
*     - GreenPWM_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_TRIG_CONTROL1_REG &= (uint32)~GreenPWM_COUNT_MASK;
    GreenPWM_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << GreenPWM_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - GreenPWM_CMD_CAPTURE    - Trigger Capture/Switch command
*     - GreenPWM_CMD_RELOAD     - Trigger Reload/Index command
*     - GreenPWM_CMD_STOP       - Trigger Stop/Kill command
*     - GreenPWM_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    GreenPWM_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: GreenPWM_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the GreenPWM.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - GreenPWM_STATUS_DOWN    - Set if counting down
*     - GreenPWM_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 GreenPWM_ReadStatus(void)
{
    return ((GreenPWM_STATUS_REG >> GreenPWM_RUNNING_STATUS_SHIFT) |
            (GreenPWM_STATUS_REG & GreenPWM_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: GreenPWM_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - GreenPWM_INTR_MASK_TC       - Terminal count mask
*     - GreenPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetInterruptMode(uint32 interruptMask)
{
    GreenPWM_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: GreenPWM_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - GreenPWM_INTR_MASK_TC       - Terminal count mask
*     - GreenPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 GreenPWM_GetInterruptSourceMasked(void)
{
    return (GreenPWM_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: GreenPWM_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - GreenPWM_INTR_MASK_TC       - Terminal count mask
*     - GreenPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 GreenPWM_GetInterruptSource(void)
{
    return (GreenPWM_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: GreenPWM_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - GreenPWM_INTR_MASK_TC       - Terminal count mask
*     - GreenPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_ClearInterrupt(uint32 interruptMask)
{
    GreenPWM_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: GreenPWM_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - GreenPWM_INTR_MASK_TC       - Terminal count mask
*     - GreenPWM_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void GreenPWM_SetInterrupt(uint32 interruptMask)
{
    GreenPWM_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
