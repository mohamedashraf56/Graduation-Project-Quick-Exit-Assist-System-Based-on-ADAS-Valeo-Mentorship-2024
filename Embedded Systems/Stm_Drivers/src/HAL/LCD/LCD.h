/*
 * LCD.h
 *
 *  Created on: Dec 23, 2023
 *      Author: Mamdouh
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


// important note the pins are all connected consecutively start from RS and E and DATAPINS
#define LCD_PORTID   GPIO_PORTB
#define LCD_DATA_PINS   PIN2
#define LCD_RS       PIN0
#define LCD_E        PIN1

void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_displayCharacter(uint8 data);
void LCD_sendCommand(uint8 command);
void delay_us(unsigned int microseconds);

void LCD_moveCursor(uint8 row,uint8 col);
void LCD_intgerToString(int data);

void delay_ms(uint32 milliseconds);

#endif /* HAL_LCD_LCD_H_ */
