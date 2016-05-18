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

uint8 calibratedZ = 1;
uint8 zFlag = 0;
uint32 zMax = 3000;
uint32 zPos;

void z_init()
{
    interrupt_Z_StartEx(isr_Z);
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
    zFlag = 1;
    setLed(0,0,0);
    interrupt_Z_ClearPending();
    interrupt_Z_Enable();
}

void calibrateZ()
{
    calibratedZ = 0;
    zFlag = 0;
    while(interrupt_Z_GetState() == 1 && zFlag == 0)
    {
        setLed(1,0,0);
        stepZBackwards();
    }
    zPos = 0;
    calibratedZ = 1;
    setLed(0,0,0);
}

void setZPos(uint8 zVal)
{
    uint32 i;
    uint32 zDes = 0;
    uint32 zSteps = 0;
    
    if(calibratedZ == 1)
    {
        zDes = zVal * zMax / resolution;
        if(zDes < zPos)
        {
            setLed(0,1,0);
            zSteps = zPos - zDes;
            for(i = 0; i < zSteps; i++)
            {
                stepZBackwards();
                zPos--;                
            }
            setLed(0,0,0);
        }
        else if(zDes > zPos)
        {
            setLed(0,1,0);
            zSteps = zDes - zPos;
            for(i = 0; i < zSteps; i++)
            {
                stepZForwards();
                zPos++;                
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

uint8 getZPos()
{
    return zPos;   
}

uint8 getZMax()
{
    return zMax;   
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
