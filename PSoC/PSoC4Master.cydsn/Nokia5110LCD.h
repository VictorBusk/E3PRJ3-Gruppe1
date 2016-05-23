/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#if !defined(Nokia5110LCD_H) /* Nokia5110LCD_H */
#define Nokia5110LCD_H

#include "cytypes.h"
#include "cyfitter.h"
#include "project.h"

void LCD_Character(uint8);
void LCD_Clear(void);
void LCD_Init(void);
void LCD_String(char*);
void LCD_Write(uint8, uint8);
void Send_Data(int8);
void LCD_gotoXY(uint8, uint8);
void LCD_Bitmap(char*);

#define HIGH    1
#define LOW     0

#define LCD_COMMAND LOW 
#define LCD_DATA    HIGH

#define LCD_X 84
#define LCD_Y 48

#define FONT_HEIGHT 8
#define FONT_WIDTH 5

#define EMPTY_COLUMN_DATA   0x00u
#define OFFSET_FOR_ASCII    0x20u
#define MSb_POSITION        0x80u
#define DELAY_1_US          0x01u
#define DELAY_1_MS          0x01u
#define ROW_BEGINNING       0x00u
#define COLUMN_BEGINNING    0x00u
#define SHIFT_LEFT_BY_1     0x01u

/*******************************************************************************
* Instruction 1: CMD_NOP
*******************************************************************************/
#define CMD_NOP             0x00u

/*******************************************************************************
* Instruction 2: CMD_FUNCTION_SET
*******************************************************************************/
#define CMD_FUNCTION_SET    0x20u
#define FUNCTION_SET_MASK   0x07u    //Only Last 3 bits are valid

/* Bit 2 of Function Set Instruction */
#define PD_SHIFT            0x02u
#define PD_MASK             (0x01u << PD_SHIFT)
#define PD_CHIP_ACTIVE      0x00u
#define PD_CHIP_POWER_DOWN  0x01u

/* Bit 1 of Function Set Instruction */
#define V_SHIFT             0x01u
#define V_MASK              (0x01u << V_SHIFT)
#define V_HORIZONTAL_ADD    0x00u
#define V_VERTICAL_ADD      0x01u

/* Bit 0 of Function Set Instruction */
#define H_SHIFT             0x00u
#define H_MASK              (0x01u << H_SHIFT)
#define H_BASIC_INST        0x00u
#define H_EXTENDED_INST     0x01u

/*******************************************************************************
* Instruction 3: CMD_DISPLAY_CONTROL    (Basic Instruction)
*******************************************************************************/
#define CMD_DISPLAY_CONTROL 0x08u   //Only Bit 0 & 2 are valid
#define DISPLAY_CONTROL_MASK 0x05u  //Only Bit 0 & 2 are valid

#define DISPLAY_BLANK       0x00u   //000
#define DISPLAY_NORMAL      0x04u   //100
#define DISPLAY_ALL_SEG_ON  0x01u   //001
#define DISPLAY_INVERSE     0x05u   //101

/*******************************************************************************
* Instruction 4: CMD_COLUMN_DATA    (Basic Instruction)
*******************************************************************************/
#define CMD_COLUMN_DATA     0x80u       // X address of RAM
#define COLUMN_DATA_MASK    0x7Fu       // Least Significant 7 bits are valid

/*******************************************************************************
* Instruction 5: CMD_ROW_DATA
*******************************************************************************/
#define CMD_ROW_DATA        0x40u       // Y address of RAM
#define ROW_DATA_MASK       0x07u       // Least Significant 3 bits are valid

/*******************************************************************************
* Instruction 6: CMD_TEMP_CONTROL
*******************************************************************************/
#define CMD_TEMP_CONTROL    0x04u
#define TEMP_CONTROL_MASK   0x03u    //Only Last 2 bits are valid

/* Bit 1 of Temperature control Instruction */
#define TEMP_CONTROL_COEFF0 0x00u   //1mV/K
#define TEMP_CONTROL_COEFF1 0x01u   //9mV/K
#define TEMP_CONTROL_COEFF2 0x02u   //17mV/K
#define TEMP_CONTROL_COEFF3 0x03u   //24mV/K

/*******************************************************************************
* Instruction 7: CMD_BIAS_SYSTEM
*******************************************************************************/
#define CMD_BIAS_SYSTEM     0x10u
#define BIAS_SYSTEM_MASK    0x07u    //Only Last 3 bits are valid

#define BIAS_1_BY_11        0x00u
#define BIAS_1_BY_10        0x01u
#define BIAS_1_BY_9         0x02u
#define BIAS_1_BY_8         0x03u
#define BIAS_1_BY_7         0x04u
#define BIAS_1_BY_6         0x05u
#define BIAS_1_BY_5         0x06u
#define BIAS_1_BY_4         0x07u

/*******************************************************************************
* Instruction 8: CMD_SET_VOP
*
* VLCD = 3.06 + (VOP6 to VOP0) * 0.06
*******************************************************************************/
#define CMD_SET_VOP     0x80u
#define SET_VOP_MASK    0xFFu        //Last 7 bits are valid

#define SET_VOP_5V      0x40u
#define SET_VOP_3V      0x31u

#endif /* End NOKIA5110LCD_H */

//[] END OF FILE
