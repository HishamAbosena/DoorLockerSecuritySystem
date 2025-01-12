/*************************************************************
 * file name: Control_ECU_Functions.C
 *
 * Module: Control_MCU
 *
 * Description: Source file for Control
 * 				Micro-Controller Functions
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/


/*******************************************************************************
 *                               Header-Files include                          *
 *******************************************************************************/
#include "Control_ECU_Functions.h"

#include"dcmotor.h"
#include"external_eeprom.h"
#include <util/delay.h>
#include <avr/io.h>
#include "buzzer.h"

/*******************************************************************************
 *                               Functions Definitions                         *
 *******************************************************************************/

/*
 * Description:
 * 				This Function initiates the Control ECU, by configuring
 * 				the UART module, the door motor and the buzzer
 */
void MC2_init(void){

	UART_config config={9600,3,0,0};
	UART_init(&config);

	Buzzer_init();
	DcMotor_Init();
}


/*
 * Description:
 * 				This Function Receives the two passwords from the HMI_ECU
 * 				via UART and calls the function to check if they match,
 * 				and if this function returns true, the function calls
 * 				another function to save this password in EEPROM
 */
void createPassword(void){
	uint8 pass1[10]={0},pass2[10]={0};
	uint8 check=0;

	do{
		UART_receiveString(pass1);

		UART_receiveString(pass2);

		check=checkIfPasswordsMatch(pass1,pass2);

		if(!check){
			UART_sendByte(0x00);
		}
		else{
			UART_sendByte(0x10);
		}
	}while(check == 0);

	savePassword(pass1);

}

/*
 * Description:
 * 				This Function takes 2 pointers to characters and check if
 * 				the two strings(match), if they match it returns true.
 */
uint8 checkIfPasswordsMatch(uint8*pass1,uint8*pass2){

	uint8 i;


	for(i=0;i<5;i++){

		if(pass1[i] != pass2[i]){
			return 0;

		}
	}

	return 1;
}


/*
 * Description:
 * 				This Function is used to save a password in EEPROM,
 * 				it takes a pointer to string and saves it byte-by-byte
 * 				in EEPROM
 */
void savePassword(uint8*pass){
	uint8 i=0;
	for(i=0;i<5;i++){
		EEPROM_writeByte(1000+i,*(pass+i));
		_delay_ms(10);
	}
}

/*
 * Description:
 * 				This Function Opens the door by rotating the motor
 * 				CW for 15-seconds, then waits for command to stop the motor
 * 				from HMI_ECU and stops it till it gets command to rotate
 * 				the motor ACW for another 15 seconds
 */
void doorFunction(void){
	DcMotor_Rotate(cw ,100);
	while(UART_recieveByte() != 'W');
	DcMotor_Rotate(0 ,0);
	while(UART_recieveByte() != 'X');
	DcMotor_Rotate(acw ,100);
	while(UART_recieveByte() != 'Y');
	DcMotor_Rotate(0 ,0);
}

/*
 * Description:
 * 				This Function gets a password from HMI_ECU via
 * 				UART and checks it with the one saved in EEPROM
 */
void checkPassword(void){
	uint8 pass1[10]={0},pass2[10]={0};
	uint8 check=1;
	UART_receiveString(pass1);

	for(uint8 i = 0; i<5 ; i++){
		EEPROM_readByte((1000+i), (pass2+i));
	}
	pass2[5]='\0';
	for(uint8 i = 0; i<5 ; i++){
		if(pass1[i] != pass2[i]){
			check=0;
		}
	}

	if(check){
		UART_sendByte(0xff);
	}
	else{
		UART_sendByte(0x00);
	}

}

/*
 * Description:
 * 				This Function turn on the buzzer and wait for a command
 * 				from the HMI_ECU to release the buzzer
 */
void BUZZER(void){
	Buzzer_on();
	while(UART_recieveByte() != 'o');
	Buzzer_off();
}
