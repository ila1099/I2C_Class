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
#include <stdio.h>
#include "project.h"
#include "../src_shared/I2C_Interface.h"
#include "../src_shared/LIS3DH.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_1_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 ms after device power-up."
    
    // String to print out messages on the UART
    char message[50] = {'\0'};
    
    // Check which devices are present on the I2C bus
    for(int i = 0 ; i < 128; i++ )
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            // print out the address is hex format
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_1_PutString(message);
        } 
    }
    
    UART_1_PutString("\r\n**************\r\n");
    UART_1_PutString("** I2C Scan **\r\n");
    UART_1_PutString("**************\r\n");
    
    CyDelay(10);
    
    uint32_t rval;
 
	// Setup the screen and print the header
	UART_1_PutString("\n\n   ");
	for(uint8_t i = 0; i<0x10; i++)
	{
        sprintf(message, "%02X ", i);
		UART_1_PutString(message);
	}
 
	// SCAN the I2C BUS for slaves
	for( uint8_t i2caddress = 0; i2caddress < 0x80; i2caddress++ ) {
        
		if(i2caddress % 0x10 == 0 ) {
            sprintf(message, "\n%02X ", i2caddress);
		    UART_1_PutString(message);
        }
 
		rval = I2C_Master_MasterSendStart(i2caddress, I2C_Master_WRITE_XFER_MODE);
        
        if( rval == I2C_Master_MSTR_NO_ERROR ) // If you get ACK then print the address
		{
            sprintf(message, "%02X ", i2caddress);
		    UART_1_PutString(message);
		}
		else //  Otherwise print a --
		{
		    UART_1_PutString("-- ");
		}
        I2C_Master_MasterSendStop();
	}
	UART_1_PutString("\n\n");
    
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    // Your turn to code!
    // Check the defines in LIS3DH.h for the address of the
    // registers to read
    
    /*      I2C Master Read - WHOAMI Register       */
    uint8_t whoami_reg;
    
    // Call the reading function 
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_WHO_AM_I_REG_ADDR, &whoami_reg);
    
    // Check if some NACKs occurred
    if(error == NO_ERROR)
    {
        sprintf(message, "Who am i register value: 0x%02X \n\r", whoami_reg);
        UART_1_PutString(message);
    }
    else
    {
        UART_1_PutString("Error reading the who am i register");
    }
        
    /*      I2C Master Read - STATUS Register       */
    uint8_t status_reg;
    
    // Call the reading function 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_STATUS_REG, &status_reg);
    
    // Check if some NACKs occurred
    if(error == NO_ERROR)
    {
        sprintf(message, "Status register value: 0x%02X \n\r", status_reg);
        UART_1_PutString(message);
    }
    else
    {
        UART_1_PutString("Error reading the status register");
    }
    
    /*      I2C Master Read - CTRL Register 1       */
    uint8_t ctrl_reg1;
    
    // Call the reading function 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS, LIS3DH_CTRL_REG1, &ctrl_reg1);
    
    // Check if some NACKs occurred
    if(error == NO_ERROR)
    {
        sprintf(message, "Control register 1 value: 0x%02X \n\r", ctrl_reg1);
        UART_1_PutString(message);
    }
    else
    {
        UART_1_PutString("Error reading the control register 1");
    }
    
    for(;;)
    {
        
    }
}

/* [] END OF FILE */
