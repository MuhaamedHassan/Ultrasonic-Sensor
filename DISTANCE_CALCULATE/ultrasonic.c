/*
 * ultrasonic.c
 *
 *  Created on: Feb 24, 2022
 *      Author: Mohamed
 */


#include "common_macros.h"
#include "ultrasonic.h"
#include "gpio.h"
#include "icu.h"
#include "util/delay.h"

/*****************************************************************************
 *                             Global Variables                              *
 ****************************************************************************/
 static uint8 g_edgedetect = 0;
 static uint16 g_highsignaltime = 0;
/*****************************************************************************

/*
 * 1- Initialize ICU Driver
 * 2- SetUp The ICU Call Back Function
 * 3- Set Up The Direction Of Trigger Pin
 */
void ULTRASONIC_init(void)
{
	/* Intialize ICU Driver */
	ICU_configType icu_config = {FCPU_8,RISING_EDGE};
	ICU_init(&icu_config);

	/* Setup The Call Back Function */
	ICU_setCallBack(ULTRASONIC_edgeProcessing);

	/*Setup The Direction Of Trigger Pin */
	GPIO_setupPinDirection(ULTRA_SONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, PIN_OUTPUT);
}


/*
 * Send The Trigger Puls To Ultrasonic
 * High Pulse With Duration 10 ms  Or More
 */
void ULTRASONIC_trigger(void)
{
	GPIO_writePin(ULTRA_SONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_ms(10);
	GPIO_writePin(ULTRA_SONIC_TRIGGER_PORT_ID, ULTRASONIC_TRIGGER_PIN_ID, LOGIC_LOW);

}

/*
 * 1- Send The Trigger Pulse By Using Ultrasonic_trigger
 * 2-Start The Measurement Of ICU From This Moment
 */
uint16 ULTRASONIC_readDistance(void)
{
	/* Send Ultrasonic Trigger Signal */
	ULTRASONIC_trigger();

	/* Calculate Distance */
	/*
	 * Distance = 	Speed * Time
	 * Total Distance = (340 m/s * Time Of High ) / 2
	 * Distance In Cm = (34000 *time of high ) / 2
	 * Distance in cm = 17000 * Time Of High
	 *
	 * FCPU = 8 MHZ
	 * ICU FCPU = FCPU _8
	 * so 1 Instruction is 1 micro sec
	 *
	 * Distance In Cm = 17000 * 1 * 10 ^-6* Time Of High
	 * Distance In Cm = 0.017 *Time Of High = Time Of High / 58.8
	 */
	return (( g_highsignaltime /58.8) + 2);

}

/*
 * 1- This Is Call Back Function called by The ICU
 * 2- Calculate The High Time Of Echo Pulse
 */
 static void ULTRASONIC_edgeProcessing(void)
{
	g_edgedetect ++ ;
	if (g_edgedetect == 1)
	{
		/* Clearing Timer Value TCNT1 ; */
		ICU_clearTimerValue();

		/* Make Timer To Detect Falling Edge */
		ICU_setEdgeDetectionType(FALLING_EDGE);
	}
	if (g_edgedetect == 2)
	{
		/* Get The Value Of High Edge ICR1 */
		g_highsignaltime = ICU_getInputCaptureValue();

		/* Make Timer To Detect Rising Edge */
		ICU_setEdgeDetectionType(RISING_EDGE);

		/* Clearing The Value Of g_edgedetect */
		g_edgedetect = 0;
	}
}
