/************************************************************
 * file name: timer1.c
 *
 * Module: Timer 1
 *
 * Description: source file for timer 1 module
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 ************************************************************/
#include "timer1.h"
#include<avr/io.h>
#include<avr/interrupt.h>
/*************************************************************
* 				Global Variables Definition 				 *
**************************************************************/
static volatile void (*g_function_ptr)(void) = NULL_PTR;


/*************************************************************
* 				Function Definitions 						 *
**************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);

	TCNT1= Config_Ptr->initial_value;
	OCR1A= Config_Ptr->compare_value;

	TCCR1A= (TCCR1A & 0xFC) | ((Config_Ptr->mode) & 0x03);
	TCCR1B= (TCCR1B & 0x00) | ( ( (Config_Ptr->mode) & 0xFC) << 3);

	TIMSK = (1<< OCIE1A) | (1<< TOIE1);
	SREG|= (1<<7);

	TCCR1B= (TCCR1B & 0xF8) | (Config_Ptr->prescaler & 0x07);
}

void Timer1_deInit(void){
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	OCR1A=0;
	TIMSK= (TIMSK & 0x3C);
}

void Timer1_setCallBack(void(*a_ptr)(void)){
	g_function_ptr= a_ptr;
}

/*************************************************************
* 			    	ISRs Definitions   						 *
**************************************************************/
ISR(TIMER1_COMPA_vect){
	if(g_function_ptr != NULL_PTR){
		(*g_function_ptr)();
	}
}

ISR(TIMER1_OVF_vect){
	if(g_function_ptr != NULL_PTR){
		(*g_function_ptr)();
	}
}
