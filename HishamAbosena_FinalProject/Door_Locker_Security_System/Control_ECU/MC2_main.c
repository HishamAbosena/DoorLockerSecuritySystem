
/*************************************************************
 * file name: MC2.C
 *
 * Module: Control_MCU
 *
 * Description: Source file for Control
 * 				Micro-Controller
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/

#include "Control_ECU_Functions.h"

/*
 * Main function for Control_ECU:
 * 					This function calls the initialization function of
 * 					the MC, then calls the function to create the password.
 * 					and in the super loop it just waits to get command from
 * 					HMI_ECU and do the processing accordingly.
 */
int main(void){

	MC2_init();

	createPassword();

	uint8 command;

	 while(1){

		command =UART_recieveByte();

		switch(command){

			case 'Z':
				createPassword();
				break;
			case 'Q':
				doorFunction();
				break;
			case'S':
				checkPassword();
				break;
			case'O':
				BUZZER();
		}

	 }

}

