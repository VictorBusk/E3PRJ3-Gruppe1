/*!
 *  @file       z.c
 *  @brief      Z modul
 *  @details    Styre Z modulets funktioner.
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
#include "z.h"
#include "data.h"
#include "led.h"


/***************************************
 *       Private methods
 ***************************************/

static void stepZForwards();
static void stepZBackwards():


/***************************************
 *       Public methods
 ***************************************/

/**
 *  @brief      Initialiser Z modulet
 *  @details    Initialiser Z modulets interrupt.
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void z_init()
{
  interrupt_Z_StartEx(isr_Z);
  interrupt_S_StartEx(isr_S);
}

/**
 *  @brief      Starter Z modulet
 *  @details    Starter Z modulet, og køre til position 0
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void Z_start()
{
  DEBUG_PutString("Z initializing going to zero");
  
  while(dataZ.interruptZ == 0 && dataZ.zFlag == 0)
  {
    DEBUG_PutString(".");
    stepZBackwards();
  }
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  
  dataZ.interruptZ = 0;
}

/*!
 *  @brief      Afvikler "Interrupt" fra Z
 *  @details    En "Interrupt Service Routine(ISR)" for Z der aktiveres ved interrupt fra Z modulet.
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
CY_ISR(isr_Z)
{
  interrupt_Z_Disable();
  
  uint32 i;
  
  dataZ.interruptZ = 1;

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

/*!
 *  @brief      Afvikler "Interrupt" fra Z
 *  @details    En "Interrupt Service Routine(ISR)" for Z der aktiveres ved interrupt fra Z modulet.
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
CY_ISR(isr_S)
{
  interrupt_S_Disable();
  
  uint32 i;
  
  dataZ.interruptZ = 1;
  
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

/*!
 *  @brief      Kalibrere Z
 *  @details    Metoden kalibrerer Z og sætter en ny max værdi for Z.
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void calibrateZ()
{
  DEBUG_PutString("Z calibrate pre-zMax: ");
  DEBUG_PutHexInt(dataZ.zMax);
  DEBUG_PutCRLF();
  
  dataZ.calibratedZ = 0;
  dataZ.zFlag = 1;
  dataZ.zMax = 0;
  
  DEBUG_PutString("Going forwards to max");
  while(dataZ.interruptZ == 0 && dataZ.zFlag == 1)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepZForwards();
  }
  dataZ.interruptZ = 0;
  
  DEBUG_PutString("done");
  DEBUG_PutCRLF();
  
  DEBUG_PutString("Going backwards to zero");
  while(dataZ.interruptZ == 0 && dataZ.zFlag == 0)
  {
    DEBUG_PutString(".");
    setLed(1,0,0);
    stepZBackwards();
    dataZ.zMax++;
  }
  DEBUG_PutString("done");

  setLed(0,0,0);
  
  dataZ.zPos = 0;
  dataZ.zMax = dataZ.zMax - interruptSteps;
  
  DEBUG_PutString(" post-zMax: ");
  DEBUG_PutHexInt(dataZ.zMax);
  DEBUG_PutString(" new xPos: ");
  DEBUG_PutHexInt(dataZ.zPos);
  DEBUG_PutCRLF();
  DEBUG_PutCRLF();
  
  dataZ.calibratedZ = 1;
  dataZ.interruptZ = 0;
}

/*!
 *  @brief      Sætter ny Z position
 *  @details    Ud fra den modtaget værdi udregnes antal step og vej til den ønsket destination.
 *  @param[in]  zVal  Værdi for position.
 *  @public
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
void setZPos(uint8 zVal)
{
  uint32 i;
  uint32 zDes = 0;
  uint32 zSteps = 0;
  
  dataZ.isrStopZ = 0;
  
  if(dataZ.calibratedZ == 1)
  {
    zDes = zVal * dataZ.zMax / resolution;
    
    DEBUG_PutString("Z set value: ");
    DEBUG_PutHexInt(zVal);
    DEBUG_PutString(" pre-zPos: ");
    DEBUG_PutHexInt(dataZ.zPos);
    DEBUG_PutString(" zDes: ");
    DEBUG_PutHexInt(zDes);
    
    if(zDes > dataZ.zPos)
    {
      setLed(0,1,0);
      dataZ.interruptZ = 0;
      dataZ.zFlag = 1;
      zSteps = zDes - dataZ.zPos;
      
      DEBUG_PutString(" going forwards steps: ");
      DEBUG_PutHexInt(xSteps);
      for(i = 0; i < zSteps  && dataZ.isrStopZ == 0 && dataZ.interruptZ == 0 && dataZ.zFlag == 1; i++)
      {
        DEBUG_PutString(".");
        stepZForwards();
        dataZ.zPos++;
      }
      DEBUG_PutString("done");
      
      if(dataZ.interruptZ == 1)
      {
        dataZ.zPos = dataZ.zMax;
      }
      DEBUG_PutString(" new-zPos: ");
      DEBUG_PutHexInt(dataZ.zPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
      setLed(0,0,0,0);
    }
    else if(zDes < dataZ.zPos)
    {
      setLed(0,1,0);
      
      dataZ.interruptZ = 0;
      dataZ.zFlag = 0;
      zSteps = dataZ.zPos - zDes;
      
      DEBUG_PutString(" going backwards steps: ");
      DEBUG_PutHexInt(zSteps);
      for(i = 0; i < zSteps && dataZ.isrStopZ == 0 && dataZ.interruptZ == 0 && dataZ.zFlag == 0; i++)
      {
        DEBUG_PutString(".");
        stepZBackwards();
        dataZ.zPos--;
      }
      DEBUG_PutString("done");
      if(dataZ.interruptZ == 1)
      {
        dataZ.zPos = 0;
      }
      DEBUG_PutString(" new-zPos: ");
      DEBUG_PutHexInt(dataZ.zPos);
      DEBUG_PutCRLF();
      DEBUG_PutCRLF();
      
      setLed(0,0,0,0);
    }
  }
  else
  {
    calibrateZ();
    setZPos(zVal);
  }
  dataZ.interruptZ = 0;
}


/***************************************
 *       Private methods
 ***************************************/

/*!
 *  @brief      Køre Z motor et step frem
 *  @details    Køre Z motoren et step fremad.
 *  @private
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
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

/*!
 *  @brief      Køre Z motor et step tilbage
 *  @details    Køre Z motoren et step tilbage.
 *  @private
 *  @memberof   Z
 *  @author     Casper Dieu Le (201370338@uni.au.dk)
 *  @author     Kasper Hinkler Uldbjerg (201370281@uni.au.dk)
 *  @author     Jeppe Stærk Antonsen (201271201@uni.au.dk)
 */
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


/* [] END OF FILE */