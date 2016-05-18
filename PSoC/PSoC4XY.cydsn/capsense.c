/* ========================================
 *
 * File: capsense.c
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

#include "capsense.h"

uint16 curPos;
uint16 oldPos;

void capsense_init()
{
    CapSense_Start();
    CapSense_InitializeAllBaselines();
}

void capsense()
{
    if(0u == CapSense_IsBusy())
    {
        CapSense_UpdateEnabledBaselines();
        CapSense_ScanEnabledWidgets();
    }
    CapSense_DisplayState();
}

void CapSense_DisplayState()
{
    curPos = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
    if(curPos == 0xFFFFu)
    {
        curPos = 0u;
    }
    
    if(curPos != oldPos)
    {
        oldPos = curPos;
        
        while(curPos != 0u)
        {
            if(curPos > 0 && curPos <= 20)
            {
                stepXForwards();
            }
            else if(curPos > 20 && curPos <= 40)
            {
                stepXBackwards();
            }
            else if(curPos > 40 && curPos <= 60)
            {
                stepYForwards();
            }
            else if(curPos > 60 && curPos <= 80)
            {
                stepYBackwards();
            }
            else if(curPos > 80 && curPos <= 100)
            {
                stopX();
                stopY();
            }
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
            curPos = CapSense_GetCentroidPos(CapSense_LINEARSLIDER0__LS);
            if(curPos == 0xFFFFu)
            {
                curPos = 0u;
            }
        }      
    }
}

/* [] END OF FILE */
