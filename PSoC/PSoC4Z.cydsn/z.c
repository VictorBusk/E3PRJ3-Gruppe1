/* ========================================
 *
 * File: xy.c
 * Description: 
 *
 * University: AARHUS UNIVERSITY SCHOOL OF ENGINEERING
 * Project: F16 - E3PRJ3-02 Semesterprojekt 3 [240501U178]
 * Group: 1
 * 
 * Author: 
 * Matriculation number: 
 *
 * Version: 1.0
 * Date: 13-05-2016
 *
 * ========================================
*/

#include "z.h"
#include "data.h"
#include "led.h"

void z_init()
{
    interrupt_Z_StartEx(isr_Z);
    interrupt_S_StartEx(isr_S);
}

CY_ISR(isr_Z)
{
    interrupt_Z_Disable();
    uint32 i;
    stopZ();
    setLed(0,0,1);
    for(i = 0; i < interruptSteps; i++)
    {
        stepZForwards();   
    }
    dataZ.zFlag = 1;
    setLed(0,0,0);
    interrupt_Z_ClearPending();
    interrupt_Z_Enable();
}

CY_ISR(isr_S)
{
    interrupt_S_Disable();
    uint32 i;
    stopZ();
    setLed(0,0,1);
    for(i = 0; i < interruptSteps; i++)
    {
        stepZBackwards();   
    }
    dataZ.zFlag = 0;
    setLed(0,0,0);
    interrupt_S_ClearPending();
    interrupt_S_Enable();
}

void calibrateZ()
{
    dataZ.calibratedZ = 0;
    dataZ.zFlag = 0;
    dataZ.zMax = 0;
    
    while(interrupt_Z_GetState() == 1 && dataZ.zFlag == 0)
    {
        setLed(1,0,0);
        stepZBackwards();
    }
    while(interrupt_Z_GetState() == 1 && dataZ.zFlag == 1)
    {
        setLed(1,0,0);
        stepZForwards();
        dataZ.zMax++;
    }
    dataZ.zPos = dataZ.zMax;
    dataZ.calibratedZ = 1;
    setLed(0,0,0);
}

void setZPos(uint8 zVal)
{
    uint32 i;
    uint32 zDes = 0;
    uint32 zSteps = 0;
    
    dataZ.isrStopZ = 0;
    
    if(dataZ.calibratedZ == 1)
    {
        dataZ.isrStopZ = 0;
        zDes = zVal * dataZ.zMax / resolution;
        if(zDes < dataZ.zPos)
        {
            setLed(0,1,0);
            zSteps = dataZ.zPos - zDes;
            for(i = 0; i < zSteps && dataZ.isrStopZ == 0; i++)
            {
                stepZBackwards();
                dataZ.zPos--;                
            }
            setLed(0,0,0);
        }
        else if(zDes > dataZ.zPos)
        {
            setLed(0,1,0);
            zSteps = zDes - dataZ.zPos;
            for(i = 0; i < zSteps && dataZ.isrStopZ == 0; i++)
            {
                stepZForwards();
                dataZ.zPos++;                
            }
            setLed(0,0,0);
        }
    }
    else
    {
        calibrateZ();
        setZPos(zVal);
    }
}

void stepZForwards()
{
    Pin_1a_Z_Write(1);
    Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(0);
    Pin_2a_Z_Write(1);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(0);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(1);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(0);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(1);
	CyDelay(stepDelay);   
}

void stepZBackwards()
{
    Pin_1a_Z_Write(0);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(1);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(0);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(1);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(0);
    Pin_2a_Z_Write(1);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Z_Write(1);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(0);
	CyDelay(stepDelay);
}

void stopZ()
{
    Pin_1a_Z_Write(0);
	Pin_2a_Z_Write(0);
	Pin_1b_Z_Write(0);
	Pin_2b_Z_Write(0);
}

/* [] END OF FILE */
