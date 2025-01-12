/*************************************************************
 * file name: Control_ECU_Functions.h
 *
 * Module: Control_MCU
 *
 * Description: header file for Control
 * 				Micro-Controller Functions
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/
#ifndef CONTROL_ECU_FUNCTIONS_H_
#define CONTROL_ECU_FUNCTIONS_H_

#include "common_macros.h"
#include "std_types.h"
#include"myuart.h"
/*******************************************************************************
 *                           Functions Prototype                               *
 *******************************************************************************/

/*
 * Description:
 * 				This Function initiates the Control ECU, by configuring
 * 				the UART module and the door motor
 */
void MC2_init(void);

/*
 * Description:
 * 				This Function Receives the two passwords from the HMI_ECU
 * 				via UART and calls the function to check if they match,
 * 				and if this function returns true, the function calls
 * 				another function to save this password in EEPROM
 */
void createPassword(void);

/*
 * Description:
 * 				This Function takes 2 pointers to characters and check if
 * 				the two strings(match), if they match it returns true.
 */
uint8 checkIfPasswordsMatch(uint8*pass1,uint8*pass2);

/*
 * Description:
 * 				This Function is used to save a password in EEPROM,
 * 				it takes a pointer to string and saves it byte-by-byte
 * 				in EEPROM
 */
void savePassword(uint8*pass);

/*
 * Description:
 * 				This Function Opens the door by rotating the motor
 * 				CW for 15-seconds, then waits for command to stop the motor
 * 				from HMI_ECU and stops it till it gets command to rotate
 * 				the motor ACW for another 15 seconds
 */
void doorFunction(void);

/*
 * Description:
 * 				This Function gets a password from HMI_ECU via
 * 				UART and checks it with the one saved in EEPROM
 */
void checkPassword(void);

/*
 * Description:
 * 				This Function turn on the buzzer and wait for a command
 * 				from the HMI_ECU to release the buzzer
 */
void BUZZER(void);


#endif /* CONTROL_ECU_FUNCTIONS_H_ */
