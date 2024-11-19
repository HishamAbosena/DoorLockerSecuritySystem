 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dcmotor.h
 *
 * Description: header file for the DC motor driver
 *
 * Author: Hisham Abosena
 *
 *******************************************************************************/
#ifndef DCMOTOR_H_
#define DCMOTOR_H_
/*******************************************************************************
 *                             Header Files Includes                           *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_OUTPUT_1_PORT				PORTB_ID
#define MOTOR_OUTPUT_1_PIN				PIN0_ID

#define MOTOR_OUTPUT_2_PORT				PORTB_ID
#define MOTOR_OUTPUT_2_PIN				PIN1_ID

#define MOTOR_ENABLE_PORT				PORTB_ID
#define MOTOR_ENABLE_PIN				PIN2_ID

/*******************************************************************************
 *                            User Defined Data Types                          *
 *******************************************************************************/
typedef enum{
	stop,cw,acw
}DcMotor_State;

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
void DcMotor_Init(void);



void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DCMOTOR_H_ */
