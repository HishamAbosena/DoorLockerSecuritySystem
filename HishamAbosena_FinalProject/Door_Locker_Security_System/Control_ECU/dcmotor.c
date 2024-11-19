 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcmotor.c
 *
 * Description: source file for the DC motor driver
 *
 * Author: Hisham Abosena
 *
 *******************************************************************************/


/*******************************************************************************
 *                             Header Files Includes                           *
 *******************************************************************************/

#include "common_macros.h"
#include "gpio.h"
#include "dcmotor.h"
#include "pwm_timer0.h"
/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle);

void DcMotor_Init(void){
	GPIO_setupPinDirection(MOTOR_OUTPUT_1_PORT,MOTOR_OUTPUT_1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_OUTPUT_2_PORT,MOTOR_OUTPUT_2_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_ENABLE_PORT,MOTOR_ENABLE_PIN,PIN_OUTPUT);

	GPIO_writePin(MOTOR_OUTPUT_1_PORT,MOTOR_OUTPUT_1_PIN,LOGIC_LOW);
	GPIO_writePin(MOTOR_OUTPUT_2_PORT,MOTOR_OUTPUT_2_PIN,LOGIC_LOW);
}



void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	switch (state){
	case stop:
		GPIO_writePin(MOTOR_OUTPUT_1_PORT,MOTOR_OUTPUT_1_PIN,LOGIC_LOW);
		GPIO_writePin(MOTOR_OUTPUT_2_PORT,MOTOR_OUTPUT_2_PIN,LOGIC_LOW);
		break;
	case cw:
		GPIO_writePin(MOTOR_OUTPUT_1_PORT,MOTOR_OUTPUT_1_PIN,LOGIC_LOW);
		GPIO_writePin(MOTOR_OUTPUT_2_PORT,MOTOR_OUTPUT_2_PIN,LOGIC_HIGH);
		break;
	case acw:
		GPIO_writePin(MOTOR_OUTPUT_1_PORT,MOTOR_OUTPUT_1_PIN,LOGIC_HIGH);
		GPIO_writePin(MOTOR_OUTPUT_2_PORT,MOTOR_OUTPUT_2_PIN,LOGIC_LOW);
		break;
	default:
		break;
	}

	PWM_Timer0_Start(speed);
}
