 /******************************************************************************
 *
 * Module: Timer0 PWM
 *
 * File Name: pwm_timer0.c
 *
 * Description: source file for the timer 0 PWM driver
 *
 * Author: Hisham Abosena
 *
 *******************************************************************************/

/*******************************************************************************
 *                             Header Files Includes                           *
 *******************************************************************************/

#include "common_macros.h"
#include "gpio.h"
#include "std_types.h"
#include <avr/io.h>
/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle){

	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	TCCR0= 0x6A;
	TCNT0=0;
	OCR0= ( (uint8)( ( (float)(duty_cycle)/100 ) * 255 ) );

}

