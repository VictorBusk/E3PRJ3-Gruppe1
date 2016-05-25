/*!
 * @todo  Dokumenter! xy.c
 */
#include "xy.h"
#include "data.h"
#include "led.h"

/***************************************
 *       Private methods
 ***************************************/

static void stepXForwards(void);
static void stepXBackwards(void);
static void stepYForwards(void);
static void stepYBackwards(void);


/***************************************
 *       Public methods
 ***************************************/

void xy_init()
{
  interrupt_X_StartEx(isr_X);
  interrupt_Y_StartEx(isr_Y);
}

void xy_start()
{
  DEBUG_PutString("X initializing going to zero");
  
  while(dataXY.interruptX == 0 && dataXY.xFlag == 0)
  {
    DEBUG_PutString(".");
    stepXBackwards();
  }
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  
  dataXY.interruptX = 0;
  
  DEBUG_PutString("Y initializing going to zero");
  
  while(dataXY.interruptY == 0 && dataXY.yFlag == 0)
  {
    DEBUG_PutString(".");
    stepYBackwards();
  }
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  
  dataXY.interruptY = 0;
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
      stepXForwards();
    }
    dataXY.xFlag = 1;
  }
  else if(dataXY.xFlag == 1)
  {
    setLed(0,0,1);
    for(i = 0; i < interruptSteps; i++)
    {
      stepXBackwards();
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
      stepYForwards();
    }
    dataXY.yFlag = 1;
  }
  else if(dataXY.yFlag == 1)
  {
    setLed(0,0,1);
    for(i = 0; i < interruptSteps; i++)
    {
      stepYBackwards();
    }
    dataXY.yFlag = 0;
  }
  setLed(0,0,0);
  
  interrupt_Y_ClearPending();
  interrupt_Y_Enable();
}

void calibrateX()
{
  DEBUG_PutString("X calibrate pre-xMax: ");
  DEBUG_PutHexInt(dataXY.xMax);
  DEBUG_PutCRLF();
  
  dataXY.calibratedX = 0;
  dataXY.xFlag = 1;
  dataXY.xMax = 0;
  
  DEBUG_PutString("Going forwards to max");
  while(dataXY.interruptX == 0 && dataXY.xFlag == 1)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepXForwards();
  }
  dataXY.interruptX = 0;
  
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  DEBUG_PutString("Going backwards to zero");
  while(dataXY.interruptX == 0 && dataXY.xFlag == 0)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepXBackwards();
    dataXY.xMax++;
  }
  DEBUG_PutString("done");
  
  setLed(0,0,0);
  
  dataXY.xPos = 0;
  dataXY.xMax = dataXY.xMax - interruptSteps;
  
  DEBUG_PutString(" post-xMax: ");
  DEBUG_PutHexInt(dataXY.xMax);
  DEBUG_PutString(" new xPos: ");
  DEBUG_PutHexInt(dataXY.xPos);
  DEBUG_PutCRLF();
  DEBUG_PutCRLF();
  
  dataXY.calibratedX = 1;
  dataXY.interruptX = 0;
}

void calibrateY()
{
  DEBUG_PutString("Y calibrate pre yMax: ");
  DEBUG_PutHexInt(dataXY.yMax);
  DEBUG_PutCRLF();
  
  dataXY.calibratedX = 0;
  dataXY.yFlag = 1;
  dataXY.yMax = 0;
  
  DEBUG_PutString("Going forwards to max");
  while(dataXY.interruptY == 0 && dataXY.yFlag == 1)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepYForwards();
  }
  dataXY.interruptY = 0;
  
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  DEBUG_PutString("Going backwards to zero");
  while(dataXY.interruptY == 0 && dataXY.yFlag == 0)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepYBackwards();
    dataXY.yMax++;
  }
  DEBUG_PutString("done");
  
  setLed(0,0,0);
  
  dataXY.yPos = 0;
  dataXY.yMax = dataXY.yMax - interruptSteps;
  
  DEBUG_PutString(" post-yMax: ");
  DEBUG_PutHexInt(dataXY.yMax);
  DEBUG_PutString(" new yPos: ");
  DEBUG_PutHexInt(dataXY.yPos);
  DEBUG_PutCRLF();
  DEBUG_PutCRLF();
  
  dataXY.calibratedY = 1;
  dataXY.interruptY = 0;
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
    
    DEBUG_PutString("X set value: ");
    DEBUG_PutHexInt(xVal);
    DEBUG_PutString(" pre-xPos: ");
    DEBUG_PutHexInt(dataXY.xPos);
    DEBUG_PutString(" xDes: ");
    DEBUG_PutHexInt(xDes);
    
    if(xDes > dataXY.xPos)
    {
      setLed(0,1,0);
      dataXY.interruptX = 0;
      dataXY.xFlag = 1;
      xSteps = xDes - dataXY.xPos;
      
      DEBUG_PutString(" going forwards steps: ");
      DEBUG_PutHexInt(xSteps);
      for(i = 0; i < xSteps && dataXY.isrStopX == 0 && dataXY.interruptX == 0 && dataXY.xFlag == 1; i++)
      {
        DEBUG_PutString(".");
        stepXForwards();
        dataXY.xPos++;
      }
      DEBUG_PutString("done");
      
      if(dataXY.interruptX == 1u)
      {
        dataXY.xPos = dataXY.xMax;
      }
      DEBUG_PutString(" new-xPos: ");
      DEBUG_PutHexInt(dataXY.xPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
      setLed(0,0,0);
    }
    else if(xDes < dataXY.xPos)
    {
      setLed(0,1,0);
      
      dataXY.interruptX = 0;
      dataXY.xFlag = 0;
      xSteps = dataXY.xPos - xDes;
      
      DEBUG_PutString(" going backwards steps: ");
      DEBUG_PutHexInt(xSteps);
      for(i = 0; i < xSteps && dataXY.isrStopX == 0 && dataXY.interruptX == 0 && dataXY.xFlag == 0; i++)
      {
        DEBUG_PutString(".");
        stepXBackwards();
        dataXY.xPos--;
      }
      DEBUG_PutString("done");
      if(dataXY.interruptX == 1u)
      {
        dataXY.xPos = 0;
      }
      DEBUG_PutString(" new-xPos: ");
      DEBUG_PutHexInt(dataXY.xPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
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
    
    DEBUG_PutString("Y set value: ");
    DEBUG_PutHexInt(yVal);
    DEBUG_PutString(" pre-yPos: ");
    DEBUG_PutHexInt(dataXY.yPos);
    DEBUG_PutString(" yDes: ");
    DEBUG_PutHexInt(yDes);
    
    if(yDes > dataXY.yPos)
    {
      setLed(0,1,0);
      
      dataXY.interruptY = 0;
      dataXY.yFlag = 1;
      ySteps = yDes - dataXY.yPos;
      
      DEBUG_PutString(" going forwards steps: ");
      DEBUG_PutHexInt(ySteps);
      for(i = 0; i < ySteps && dataXY.isrStopY == 0 && dataXY.interruptY == 0 && dataXY.yFlag == 1; i++)
      {
        DEBUG_PutString(".");
        stepYForwards();
        dataXY.yPos++;
      }
      DEBUG_PutString("done");
      if(dataXY.interruptY == 1u)
      {
        dataXY.yPos = dataXY.yMax;
      }
      DEBUG_PutString(" new-yPos: ");
      DEBUG_PutHexInt(dataXY.yPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
      setLed(0,0,0);
    }
    else if(yDes < dataXY.yPos)
    {
      setLed(0,1,0);
      
      dataXY.interruptY = 0;
      dataXY.yFlag = 0;
      ySteps = dataXY.yPos - yDes;
      
      DEBUG_PutString(" going backwards steps: ");
      DEBUG_PutHexInt(ySteps);
      for(i = 0; i < ySteps && dataXY.isrStopY == 0u && dataXY.interruptY == 0 && dataXY.yFlag == 0; i++)
      {
        DEBUG_PutString(".");
        stepYBackwards();
        dataXY.yPos--;
      }
      DEBUG_PutString("done");
      if(dataXY.interruptY == 1u)
      {
        dataXY.yPos = 0;
      }
      DEBUG_PutString(" new-yPos: ");
      DEBUG_PutHexInt(dataXY.yPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
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


/***************************************
 *       Private methods
 ***************************************/

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


/* [] END OF FILE */
