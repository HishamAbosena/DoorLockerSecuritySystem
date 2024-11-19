/************************************************************
 * file name: buzzer.c
 *
 * Module: buzzer
 *
 * Description: source file for buzzer module
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 ************************************************************/
#include<avr/io.h>
#include"buzzer.h"
#include"gpio.h"

/*************************************************************
* 				Function Definitions 						 *
**************************************************************/


void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_OFF);
}

void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_ON);
}

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,BUZZER_OFF);
}
