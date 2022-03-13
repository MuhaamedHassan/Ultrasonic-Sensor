/*
 * ultrasonic.h
 *
 *  Created on: Feb 24, 2022
 *      Author: Mohamed
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"


/******************************************************************************
 *                              Definitions
 *****************************************************************************/

#define ULTRASONIC_ECHO_PORT_ID  PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID   PIN6_ID

#define ULTRA_SONIC_TRIGGER_PORT_ID PORTB_ID
#define ULTRASONIC_TRIGGER_PIN_ID   PIN5_ID

/* Maximum Value Of Ultra Sonic Sensor In Cm */
#define ULTRASONIC_MAX_DISTANCE_CM     400


/******************************************************************************
 *                          Description & Prototype
 ******************************************************************************/
/*
 * 1- Initialize ICU Driver
 * 2- SetUp The ICU Call Back Function
 * 3- Set Up The Direction Of Trigger Pin
 */
void ULTRASONIC_init(void);


/*
 * Send The Trigger Puls To Ultrasonic
 * High Pulse With Duration 10 ms  Or More
 */
void ULTRASONIC_trigger(void);


/*
 * 1- Send The Trigger Pulse By Using Ultrasonic_trigger
 * 2-Start The Measurement Of ICU From This Moment
 */
uint16 ULTRASONIC_readDistance(void);


/*
 * 1- This Is Call Back Function called by The ICU
 * 2- Calculate The High Time Of Echo Pulse
 */
 static void ULTRASONIC_edgeProcessing(void);
#endif /* ULTRASONIC_H_ */
