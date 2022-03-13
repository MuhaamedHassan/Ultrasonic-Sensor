/*
 * icu.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Mohamed
 */

#ifndef ICU_H_
#define ICU_H_


#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum {
	NO_CLK , FCPU , FCPU_8 ,FCPU_64 , FCPU_256 , FCPU_1024 , EXT_CLK_F_EDGE , EXT_CLK_R_EDGE
}ICU_prescaler;

typedef enum {
	FALLING_EDGE , RISING_EDGE
}ICU_edgeSelect;

typedef struct {
	ICU_prescaler prescaler ;
	ICU_edgeSelect edge ;
}ICU_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. Set the required clock.
 * 	2. Set the required edge detection.
 * 	3. Enable the Input Capture Interrupt.
 * 	4. Initialize Timer1 Registers
 */
void ICU_init(const ICU_configType *config_ptr);

/*
 * Description: Function to set the Call Back function address.
 */
void ICU_setCallBack(void(*ptr2func)(void));

/*
 * Description: Function to set the required edge detection.
 */
void ICU_setEdgeDetectionType(const ICU_edgeSelect edge);

/*
 * Description: Function to get the Timer1 Value when the input is captured
 *              The value stored at Input Capture Register ICR1
 */
uint16 ICU_getInputCaptureValue(void);

/*
 * Description: Function to clear the Timer1 Value to start count from ZERO
 */
void ICU_clearTimerValue(void);

/*
 * Description: Function to disable the Timer1 to stop the ICU Driver
 */
void ICU_DeInit(void);
#endif /* ICU_H_ */
