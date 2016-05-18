/*******************************************************************************
* File Name: Lumen_I2C_BOOT.c
* Version 3.10
*
* Description:
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Lumen_I2C_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (Lumen_I2C_BTLDR_COMM_ENABLED) && \
                                (Lumen_I2C_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: Lumen_I2C_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStart function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Lumen_I2C_CyBtldrCommStart(void)
{
    if (Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        Lumen_I2C_I2CCyBtldrCommStart();
    }
    else if (Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Lumen_I2C_EzI2CCyBtldrCommStart();
    }
#if (!Lumen_I2C_CY_SCBIP_V1)
    else if (Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        Lumen_I2C_SpiCyBtldrCommStart();
    }
    else if (Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        Lumen_I2C_UartCyBtldrCommStart();
    }
#endif /* (!Lumen_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Lumen_I2C_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommStop function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Lumen_I2C_CyBtldrCommStop(void)
{
    if (Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        Lumen_I2C_I2CCyBtldrCommStop();
    }
    else if (Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Lumen_I2C_EzI2CCyBtldrCommStop();
    }
#if (!Lumen_I2C_CY_SCBIP_V1)
    else if (Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        Lumen_I2C_SpiCyBtldrCommStop();
    }
    else if (Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        Lumen_I2C_UartCyBtldrCommStop();
    }
#endif /* (!Lumen_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Lumen_I2C_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommReset function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Lumen_I2C_CyBtldrCommReset(void)
{
    if(Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        Lumen_I2C_I2CCyBtldrCommReset();
    }
    else if(Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        Lumen_I2C_EzI2CCyBtldrCommReset();
    }
#if (!Lumen_I2C_CY_SCBIP_V1)
    else if(Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        Lumen_I2C_SpiCyBtldrCommReset();
    }
    else if(Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        Lumen_I2C_UartCyBtldrCommReset();
    }
#endif /* (!Lumen_I2C_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: Lumen_I2C_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommRead function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Lumen_I2C_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = Lumen_I2C_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = Lumen_I2C_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!Lumen_I2C_CY_SCBIP_V1)
    else if(Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = Lumen_I2C_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        status = Lumen_I2C_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!Lumen_I2C_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: Lumen_I2C_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls the CyBtldrCommWrite  function of the bootloader communication
*  component for the selected mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus Lumen_I2C_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(Lumen_I2C_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = Lumen_I2C_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(Lumen_I2C_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = Lumen_I2C_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!Lumen_I2C_CY_SCBIP_V1)
    else if(Lumen_I2C_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = Lumen_I2C_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(Lumen_I2C_SCB_MODE_UART_RUNTM_CFG)
    {
        status = Lumen_I2C_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!Lumen_I2C_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (Lumen_I2C_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
