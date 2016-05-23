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
#include "data.h"
#include "led.h"

void xy_init()
{
    interrupt_X_StartEx(isr_X);
    interrupt_Y_StartEx(isr_Y);
}

CY_ISR(isr_X)
{
    interrupt_X_Disable();
    
    uint32 i; 
    
    dataXY.interruptX = 1;

    if(dataXY.xFlag == 0)
    {
        setLed(0,0,1);
        for(i = 0; i < interruptSteps; i++)
        {
            stepXBackwards();   
        }
        dataXY.xFlag = 1;
    }
    else if(dataXY.xFlag == 1)
    {
        setLed(0,0,1);
        for(i = 0; i < interruptSteps; i++)
        {
            stepXForwards();   
        }
        dataXY.xFlag = 0;
    }
    setLed(0,0,0);
    
    interrupt_X_ClearPending();
    interrupt_X_Enable();
}

CY_ISR(isr_Y)
{
    interrupt_Y_Disable();
    
    uint32 i;

    dataXY.interruptY = 1;

    if(dataXY.yFlag == 0)
    {
        setLed(0,0,1);
        for(i = 0; i < interruptSteps; i++)
        {
            stepYBackwards();   
        }
        dataXY.yFlag = 1;
    }
    else if(dataXY.yFlag == 1)
    {
        setLed(0,0,1);
        for(i = 0; i < interruptSteps; i++)
        {
            stepYForwards();   
        }
        dataXY.yFlag = 0;
    }
    setLed(0,0,0);
    
    interrupt_Y_ClearPending();
    interrupt_Y_Enable();
}

void calibrateX()
{
    dataXY.calibratedX = 0;
    dataXY.xFlag = 0;
    dataXY.xMax = 0;
    
    while(interrupt_X_GetState() == 1 && dataXY.xFlag == 0)
    {
        setLed(1,0,0);
        stepXForwards();
    }
    while(interrupt_X_GetState() == 1 && dataXY.xFlag == 1)
    {
        setLed(1,0,0);
        stepXBackwards();
        dataXY.xMax++;
    }
    setLed(0,0,0);
        
    dataXY.xPos = 0;
    dataXY.xMax = dataXY.xMax - interruptSteps;
    dataXY.calibratedX = 1;
}

void calibrateY()
{
    dataXY.calibratedX = 0;
    dataXY.yFlag = 0;
    dataXY.yMax = 0;
    
    while(interrupt_Y_GetState() == 1 && dataXY.yFlag == 0)
    {
        setLed(1,0,0);
        stepYForwards();
    }
    while(interrupt_Y_GetState() == 1 && dataXY.yFlag == 1)
    {
        setLed(1,0,0);
        stepYBackwards();
        dataXY.yMax++;
    }
    setLed(0,0,0);
    
    dataXY.yPos = 0;
    dataXY.yMax = dataXY.yMax - interruptSteps;
    dataXY.calibratedY = 1;
}

void setXPos(uint8 xVal)
{
    uint32 i;
    uint32 xDes = 0;
    uint32 xSteps = 0;
    
    dataXY.isrStopX = 0;
    
    if(dataXY.calibratedX == 1)
    {
        xDes = xVal * dataXY.xMax / resolution;
        if(xDes < dataXY.xPos)
        {
            setLed(0,1,0);
            dataXY.interruptX = 0;
            dataXY.xFlag = 1;
            xSteps = dataXY.xPos - xDes;
            for(i = 0; i < xSteps && dataXY.isrStopX == 0u; i++)
            {
                stepXBackwards();
                dataXY.xPos--;
            }
            if(dataXY.interruptX == 1u)
            {
                dataXY.xPos = 0;
            }
            setLed(0,0,0);
        }
        else if(xDes > dataXY.xPos)
        {
            setLed(0,1,0);
            dataXY.interruptX = 0;
            dataXY.xFlag = 0;
            xSteps = xDes - dataXY.xPos;
            for(i = 0; i < xSteps && dataXY.isrStopX == 0u; i++)
            {
                stepXForwards();
                dataXY.xPos++;                
            }
            if(dataXY.interruptX == 1u)
            {
                dataXY.xPos = dataXY.xMax;
            }
            setLed(0,0,0);
        }
    }
    else
    {
        calibrateX();
        setXPos(xVal);
    }
    dataXY.interruptX = 0;
}

void setYPos(uint8 yVal)
{
    uint32 i;
    uint32 yDes = 0;
    uint32 ySteps = 0;
    
    dataXY.isrStopY = 0;
    
    if(dataXY.calibratedY == 1)
    {
        yDes = yVal * dataXY.yMax / resolution;
        if(yDes < dataXY.yPos)
        {
            setLed(0,1,0);
            dataXY.interruptY = 0;
            ySteps = dataXY.yPos - yDes;
            for(i = 0; i < ySteps && dataXY.isrStopY == 0u; i++)
            {
                stepYBackwards();
                dataXY.yPos--;                
            }
            if(dataXY.interruptY == 1u)
            {
                dataXY.yPos = dataXY.yPos + interruptSteps;
            }
            setLed(0,0,0);
        }
        else if(yDes > dataXY.yPos)
        {
            setLed(0,1,0);
            dataXY.interruptY = 0;
            dataXY.yFlag = 0;
            ySteps = yDes - dataXY.yPos;
            for(i = 0; i < ySteps && dataXY.isrStopY == 0u; i++)
            {
                stepYForwards();
                dataXY.yPos++;                
            }
            if(dataXY.interruptY == 1u)
            {
                dataXY.yPos = dataXY.yPos - interruptSteps;
            }
            setLed(0,0,0);
        }
    }
    else
    {
        calibrateY();
        setYPos(yVal);
    }
    dataXY.interruptY = 0;
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
