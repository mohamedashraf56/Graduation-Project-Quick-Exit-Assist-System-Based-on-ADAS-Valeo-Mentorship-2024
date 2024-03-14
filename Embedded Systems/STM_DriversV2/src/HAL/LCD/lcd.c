 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed Tarek
 *
 * Edited by : asabet
 *
 *******************************************************************************/

#include "../../lip/common_macros.h"
#include "../../lip/std_types.h"
#include "lcd.h"
#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"
#include <stdlib.h>



void _delay_ms(uint32 milliseconds)
{
    // Calculate the number of cycles required for the desired delay
    uint32 cycles = 250 * milliseconds;

    // Perform the delay loop
    for (uint32 i = 0; i < cycles; i++)
    {
        // Do nothing
        __asm__("nop");
    }
}


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_init(void)
{
	/* Configure the direction for RS and E pins as output pins */
	GPIO_Set_Pin_Direction(LCD_RS_PORT_ID,LCD_RS_PIN_ID,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(LCD_E_PORT_ID,LCD_E_PIN_ID,GPIO_MODE_OUTPUT);
	_delay_ms(50);		/* LCD Power ON delay always > 15ms */

#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_Set_Pin_Direction(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GPIO_MODE_OUTPUT);
	GPIO_Set_Pin_Direction(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GPIO_MODE_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	GPIO_SIT_PORT_DIRECTION(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID, PIN9, output);
	//SYSTICK_SET_BUSY_WAIT(50000);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*
 * Description :
 * Send the required command to the screen
 */

void LCD_sendCommand(uint8 command)
{
	GPIO_Set_Pin_Value(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW); /* Instruction Mode RS=0 */
	_delay_ms(1);
	//delay_us(1); /* delay for processing Tas = 50ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	//delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);


#if(LCD_DATA_BITS_MODE == 4)
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_SET_PORT_VALUE_(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID, command);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_SET_PIN_VALUE(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
	GPIO_Set_Pin_Value(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH); /* Data Mode RS=1 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_Set_Pin_Value(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_Set_Pin_Value(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	GPIO_SET_PORT_VALUE_(LCD_DATA_PORT_ID, LCD_DATA_FIRST_PIN_ID, data);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_SET_PIN_VALUE(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	/*while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}*/
	/***************** Another Method ************************/
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}		
	/*********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address=0;
	
	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}					
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
