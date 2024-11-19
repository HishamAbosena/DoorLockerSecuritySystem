/*************************************************************
 * file name: HMI_ECU_Functions.C
 *
 * Module: HMI_ECU
 *
 * Description: header file for functions of Human-Machine
 * 				 Interface Micro-Controller
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/

#ifndef HMI_ECU_FUNCTIONS_H_
#define HMI_ECU_FUNCTIONS_H_

#include "common_macros.h"
#include "std_types.h"

/*******************************************************************************
 *                           Functions Prototype                               *
 *******************************************************************************/

/*
 * Description:
 * 				This Function initiates timer 1 to count 15 seconds and
 * 				sets the callback function to TIMER_callBack() that manipulates
 * 				the timing of opening and closing the door
 * 				and sends to the Control ECU command to start rotating the motor
 */
void openDoor(void);

/*
 * Description:
 * 				This Function initiates the HMI ECU, by configuring
 * 				the UART module and the LCD Module
 */
void MC1_init(void);

/*
 * Description:
 * 				This Function Takes two Passwords from User,
 * 				and send them to Control ECU via UART and waits till
 * 				the Control ECU do the checking if they match and send
 * 				the result of checking to it via UART and
 * 				if they don't match it keeps looping to take two passwords
 * 				that match
 */
void passwordCreate(void);

/*
 * Description:
 * 				This is the callback Function of the Timer, it is responsible
 * 				for manipulating the timing of sending the commands of
 * 				rotating the motor CW first (15-seconds) then sending
 * 				command of turning off the motor (3-seconds) and then
 * 				rotating the motor ACW for (15-seconds) and finally
 * 				sending the command to end the process to the control
 * 				ECU
 */
void TIMER_callBack(void);

/*
 * Description:
 * 				This Function is responsible for sending a password
 * 				to Control_ECU via UART. It takes integer value (i.e password)
 * 				and convert it to a string of ASCIIs and send the string via
 * 				UART
 */
void sendPassword(uint32 x);

/*
 * Description:
 * 				This Function is the Main program in the SUPER_LOOP,
 * 				It Displays two options to he user whether to change
 * 				the password or open the door, when user chooses either,
 * 				it demands the password from user (He has 3 trials to
 * 				enter it correctly before the system locks for 1 minute and
 * 				it sends to the control ECU to turn on the buzzer and after
 * 				the 1 minute it sends to it to release the buzzer).
 *
 * 				It takes the password each time from user and sends it to
 * 				control ECU via UART and waits for the response of Control ECU
 * 				whether the password entered by user matches the saved one,
 *
 * 				if it matches it calls the function corresponding to the user choice
 */
void mainMenu(void);

/*
 * Description:
 * 				This is the Function that takes the input password from
 * 				the user and sends it to control ECU. this function returns
 * 				true if password matches saved one
 */
uint8 checkIfPasswordIsCorrect(void);

#endif /* HMI_ECU_FUNCTIONS_H_ */
