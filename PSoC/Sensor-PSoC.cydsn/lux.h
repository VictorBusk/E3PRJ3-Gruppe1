/*!
 * @file        lux.h
 * @brief       Code copied from the "TSL2561 Light-to-digital converter" datasheet
 * @author      TAOS, Inc.
 */

//****************************************************************************
//
// Copyright ? 2004−2005 TAOS, Inc.
//
// THIS CODE AND INFORMATION IS PROVIDED ”AS IS” WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
// PURPOSE.
//
// Module Name:
// lux.h
//
//****************************************************************************

/*!
 *  @brief      Calculate perceived lux from sensor values
 *  The sensor has two detectors, one that detects visible and infrared light
 *      while the second only detects infrared light. The amount of visible
 *      light is then calculated by substracting a scaling fraction of the
 *      second detector value from a scaling fraction of the first.
 *  @return The calculated lux value
 *  @param[in]  iGain Is internal scaling enabled in the sensor (0 = x1, 1 = x16)
 *  @param[in]  tInt Integration time set in the sensor (0 = 13.7ms, 1 = 101ms, 2 = 402ms)
 *  @param[in]  ch0 Value read from detector 0
 *  @param[in]  ch1 Value read from detector 1
 *  @param[in]  iType Physical sensor package (0 = T, FN or CL, 1 = CS)
 *  @public
 *  @author      TAOS, Inc.
 */
unsigned int CalculateLux(unsigned int iGain, unsigned int tInt, unsigned int ch0,
                          unsigned int ch1, int iType);

/* [] END OF FILE */
