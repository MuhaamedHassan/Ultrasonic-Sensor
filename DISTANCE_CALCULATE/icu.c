/*
 * icu.c
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohamed
 */

#include "icu.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR ;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
	else
	{
		/* Do Nothing */
	}

}

/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_configType *config_ptr)
{
	/* Configure ICU Pin As Input PD6 */
	CLEAR_BIT(DDRD,PD6);

	/*
	 * ICU Mode Always Run In Normal Mode
	 * NON PWM MODE
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	/*
	 * Select Clock Of ICU
	 */
	TCCR1B = (TCCR1B & 0xF8) | (config_ptr->prescaler);

	/*
	 * Select Edge Of ICU Detection
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((config_ptr->edge)<<6);

	/*
	 * CLEAR ICR1 AND TCNT1
	 */
	TCNT1 = 0 ;
	ICR1 = 0 ;

	/* Enable Interrupt Module */
	SET_BIT(TIMSK,TICIE1);
}

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*ptr2func)(void))
{
	g_callBackPtr = ptr2func ;
}

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_edgeSelect edge)
{
	TCCR1B = (TCCR1B & 0xBF) | (edge<<6);
}
/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1 ;
}
/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0 ;
}

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void)
{
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TCNT1 = 0 ;
	ICR1 = 0 ;
	CLEAR_BIT(TIMSK,TICIE1);
}
