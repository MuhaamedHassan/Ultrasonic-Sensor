/*
 * main.c
 *
 *  Created on: Feb 24, 2022
 *      Author: Mohamed
 */


#include "lcd.h"
#include "ultrasonic.h"
#include <avr/interrupt.h>
#include <avr/io.h>

int main(void)
{
	uint16 distance = 0 ;
	/* Enable Global Interrupt */
	SREG |=(1<<7);
	LCD_init();
	ULTRASONIC_init();

	LCD_displayString("Distance =   cm");

	while(1)
	{
		distance = ULTRASONIC_readDistance();
		if (distance < 100)
		{
			LCD_moveCursor(0, 10);
			LCD_intgerToString(distance);
			LCD_displayString(" ");
		}
		else
		{
			LCD_moveCursor(0, 10);
			LCD_intgerToString(distance);
		}

	}
}
