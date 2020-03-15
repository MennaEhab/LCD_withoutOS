/*
 * LCD.c
 *
 * Created: 3/15/2020 11:47:59 AM
 * Author : MENA
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
    /* Replace with your application code */
			LCD_init();
			LCD_displayString("12345");
		
		/*LCD_WriteData('1');
		LCD_WriteData('2');
		LCD_WriteData('3');
		LCD_WriteData('4');*/
    while (1) 
    {

		
    }
}

