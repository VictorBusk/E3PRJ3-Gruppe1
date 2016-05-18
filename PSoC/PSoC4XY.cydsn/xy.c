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

#include "xy.h"

uint8 calibratedX = 0;
uint8 calibratedY = 0;
uint8 xFlag = 0;
uint8 yFlag = 0;
uint32 xMax = 0;
uint32 xPos;
uint32 yMax = 0;
uint32 yPos;

void xy_init()
{
    interrupt_X_StartEx(isr_X);
    interrupt_Y_StartEx(isr_Y);
}

CY_ISR(isr_X)
{
    interrupt_X_Disable();
    uint32 i;
    stopX();
    setLed(0,0,1);
    if(xFlag == 0)
    {
        for(i = 0; i < interruptSteps; i++)
        {
            stepXBackwards();   
        }
        xFlag = 1;
    }
    else
    {
        for(i = 0; i < interruptSteps; i++)
        {
            stepXForwards();   
        }
        xFlag = 0;
    }
    setLed(0,0,0);
    interrupt_X_ClearPending();
    interrupt_X_Enable();
}

CY_ISR(isr_Y)
{
    interrupt_Y_Disable();
    uint32 i;
    stopY();
    setLed(0,0,1);
    if(yFlag == 0)
    {
        for(i = 0; i < interruptSteps; i++)
        {
            stepYBackwards();   
        }
        yFlag = 1;
    }
    else if(yFlag == 1)
    {
        for(i = 0; i < interruptSteps; i++)
        {
            stepYForwards();   
        }
        yFlag = 0;
    }
    setLed(0,0,0);
    interrupt_Y_ClearPending();
    interrupt_Y_Enable();
}

void calibrateX()
{
    xFlag = 0;
    while(interrupt_X_GetState() == 1 && xFlag == 0)
    {
        setLed(1,0,0);
        stepXForwards();
    }
    while(interrupt_X_GetState() == 1 && xFlag == 1)
    {
        setLed(1,0,0);
        stepXBackwards();
        xMax++;
    }
    xPos = 0;
    xMax = xMax - 100;
    calibratedX = 1;
    setLed(0,0,0);
}

void calibrateY()
{
    yFlag = 0;
    while(interrupt_Y_GetState() == 1 && yFlag == 0)
    {
        setLed(1,0,0);
        stepYForwards();
    }
    while(interrupt_Y_GetState() == 1 && yFlag == 1)
    {
        setLed(1,0,0);
        stepYBackwards();
        yMax++;
    }
    yPos = 0;
    yMax = yMax - 100;
    calibratedY = 1;
    setLed(0,0,0);
}

void setXPos(uint8 xVal)
{
    uint32 i;
    uint32 xDes = 0;
    uint32 xSteps = 0;
    
    if(calibratedX == 1)
    {
        xDes = xVal * xMax / resolution;
        if(xDes < xPos)
        {
            setLed(0,1,0);
            xSteps = xPos - xDes;
            for(i = 0; i < xSteps; i++)
            {
                stepXBackwards();
                xPos--;                
            }
            setLed(0,0,0);
        }
        else if(xDes > xPos)
        {
            setLed(0,1,0);
            xSteps = xDes - xPos;
            for(i = 0; i < xSteps; i++)
            {
                stepXForwards();
                xPos++;                
            }
            setLed(0,0,0);
        }
    }
    else
    {
        calibrateX();
        setXPos(xVal);
    }
}

void setYPos(uint8 yVal)
{
    uint32 i;
    uint32 yDes = 0;
    uint32 ySteps = 0;
    
    if(calibratedY == 1)
    {
        yDes = yVal * yMax / resolution;
        if(yDes < yPos)
        {
            setLed(0,1,0);
            ySteps = yPos - yDes;
            for(i = 0; i < ySteps; i++)
            {
                stepYBackwards();
                yPos--;                
            }
            setLed(0,0,0);
        }
        else if(yDes > yPos)
        {
            setLed(0,1,0);
            ySteps = yDes - yPos;
            for(i = 0; i < ySteps; i++)
            {
                stepYForwards();
                yPos++;                
            }
            setLed(0,0,0);
        }
    }
    else
    {
        calibrateY();
        setYPos(yVal);
    }
}

uint8 getXPos()
{
    return xPos;   
}

uint8 getYPos()
{
    return yPos;   
}

uint8 getXMax()
{
    return xMax;   
}

uint8 getYMax()
{
    return yMax;   
}

void stepXForwards()
{
    Pin_1a_X_Write(1);
    Pin_2a_X_Write(0);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);

	Pin_1a_X_Write(0);
    Pin_2a_X_Write(1);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);

	Pin_1a_X_Write(0);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(1);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);

	Pin_1a_X_Write(0);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(1);
	CyDelay(stepDelay);   
}

void stepXBackwards()
{
    Pin_1a_X_Write(0);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(1);
	CyDelay(stepDelay);

	Pin_1a_X_Write(0);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(1);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);

	Pin_1a_X_Write(0);
    Pin_2a_X_Write(1);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);

	Pin_1a_X_Write(1);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(0);
	CyDelay(stepDelay);
}

void stopX()
{
    Pin_1a_X_Write(0);
	Pin_2a_X_Write(0);
	Pin_1b_X_Write(0);
	Pin_2b_X_Write(0);
}

void stepYForwards()
{
    Pin_1a_Y_Write(1);
    Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(0);
    Pin_2a_Y_Write(1);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(0);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(1);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(0);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(1);
	CyDelay(stepDelay);   
}

void stepYBackwards()
{
    Pin_1a_Y_Write(0);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(1);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(0);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(1);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(0);
    Pin_2a_Y_Write(1);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);

	Pin_1a_Y_Write(1);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(0);
	CyDelay(stepDelay);
}

void stopY()
{
    Pin_1a_Y_Write(0);
	Pin_2a_Y_Write(0);
	Pin_1b_Y_Write(0);
	Pin_2b_Y_Write(0);
}


/* [] END OF FILE */
