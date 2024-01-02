/*
 * LCD.c
 *
 *  Created on: Dec 23, 2023
 *      Author: Mamdouh
 */

#include "../../lip/std_types.h"
#include "../../lip/common_macros.h"
#include "LCD.h"

#include "../../MCAL/GPIO/GPIO_int_.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"





void delay_us(unsigned int microseconds) {
    unsigned int cycles = microseconds * 25; // 25 cycles per microsecond (25 MHz frequency)

    for (unsigned int i = 0; i < cycles; i++) {
        // Delay loop
        // Adjust the loop count based on the specific microcontroller or system being used
        // This loop introduces a delay of approximately 1 microsecond per iteration
        asm volatile("nop");
    }
}


















void LCD_sendCommand(uint8 command)
{
	// Make RS LOGIG LOW
	GPIO_SetPin_Value(LCD_PORTID, LCD_RS, PIN_LOW);
	//DELAY 1ms
	delay_us(10);
	// make e logic high
	GPIO_SetPin_Value(LCD_PORTID, LCD_E, PIN_HIGH);
	//DELAY 1ms
	delay_us(10);
	// Write pins to send command to lcd
	GPIO_Write_Pins(LCD_PORTID, LCD_DATA_PINS, eight_one, command);
	//DELAY 1ms
	delay_us(10);
	// make e logic low
	GPIO_SetPin_Value(LCD_PORTID, LCD_E, PIN_LOW);
	//DELAY 1ms
	delay_us(10);
}



void LCD_displayCharacter(uint8 data)
{
	// Make RS LOGIG HIGH
	GPIO_SetPin_Value(LCD_PORTID, LCD_RS, PIN_HIGH);
	//DELAY 1ms
	delay_us(5);
	// make e logic high
	GPIO_SetPin_Value(LCD_PORTID, LCD_E, PIN_HIGH);
	//DELAY 1ms
	delay_us(5);
	// send data to lcd
	GPIO_Write_Pins(LCD_PORTID, LCD_DATA_PINS, eight_one, data);

	//DELAY 1ms
	delay_us(5);
	// make e logic low
	GPIO_SetPin_Value(LCD_PORTID, LCD_E, PIN_LOW);
	//DELAY 1ms
	delay_us(5);
}



void LCD_init(void)
{
	 uint8 counter = LCD_RS;
	 while(counter<11)
	 {
		 GPIO_SetPin_Direction(LCD_PORTID, counter, GPIO_MODE_OUTPUT);
		 GPIO_SetOutput_Type(LCD_PORTID, counter, PUSH_PULL);
		 GPIO_SetOutput_Speed(LCD_PORTID, counter, LowSpeed);
		 counter++;
	 }
	 MSTK_vSetBusWait(5000);
	 LCD_sendCommand(0X38);
	 LCD_sendCommand(0X0C);
	 LCD_sendCommand(0X01);

}


void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}


void LCD_displayString(const char *Str)
{
	LCD_sendCommand(0X01);
	uint8 i  = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}





void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

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







// Function to create a delay in milliseconds
void delay_ms(uint32 milliseconds) {
    // The actual delay depends on the processor frequency
    // Adjust the loop count accordingly for different frequencies
    uint32 cycles_per_ms = 25000;  // 25 MHz / 1000 ms
    uint32 total_cycles = cycles_per_ms * milliseconds;

    for (uint32 i = 0; i < total_cycles; ++i) {
        // This loop creates a delay
        __asm__("nop");  // You can replace this with other instructions as needed
    }
}





















