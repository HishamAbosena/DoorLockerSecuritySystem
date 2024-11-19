/*************************************************************
 * file name: HMI_ECU_Functions.C
 *
 * Module: HMI_ECU
 *
 * Description: Source file for functions of Human-Machine
 * 				 Interface Micro-Controller
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/

/*******************************************************************************
 *                               Header-Files include                          *
 *******************************************************************************/
#include "HMI_ECU_Functions.h"

#include "lcd.h"
#include "keypad.h"
#include "myuart.h"
#include <util/delay.h>
#include "timer1.h"

/*******************************************************************************
 *                            Global Variable Definitions                     *
 *******************************************************************************/
uint8 g_timerTick=0;

/*******************************************************************************
 *                               Functions Definitions                         *
 *******************************************************************************/
/*
 * Description:
 * 				This Function initiates the HMI ECU, by configuring
 * 				the UART module and the LCD Module
 */
void MC1_init(void){
	UART_config config={9600,3,0,0};
	LCD_init();
	UART_init(&config);
}

/*
 * Description:
 * 				This Function Takes two Passwords from User,
 * 				and send them to Control ECU via UART and waits till
 * 				the Control ECU do the checking if they match and send
 * 				the result of checking to it via UART and
 * 				if they don't match it keeps looping to take two passwords
 * 				that match
 */
void passwordCreate(void){
	uint32 pass1=0,pass2=0;
	uint8 i=0,flag=0x00,key_pressed;

	do{
		pass1=0;
		pass2=0;
		LCD_clearScreen();
		LCD_moveCursor( 0, 0);
		LCD_displayString("PLZ Enter Pass:");

		LCD_moveCursor( 1, 0);
		for(i=0;i<5;i++){

			key_pressed=KEYPAD_getPressedKey();
			pass1=(pass1*10)+key_pressed;
			LCD_displayCharacter('*');

		}
		while(KEYPAD_getPressedKey() != '=');
		sendPassword(pass1);

		_delay_ms(200);
		LCD_clearScreen();

		LCD_moveCursor( 0, 0);
		LCD_displayString("PLZ re-enter the");
		LCD_moveCursor( 1, 0);
		LCD_displayString("same pass: ");

		for(i=0;i<5;i++){
			key_pressed=KEYPAD_getPressedKey();
			pass2=(pass2*10)+key_pressed;
			LCD_displayCharacter('*');
		}
		while(KEYPAD_getPressedKey() != '=');
		sendPassword(pass2);

		flag=UART_recieveByte();

		if (flag==0x10){

			LCD_clearScreen();
			LCD_moveCursor( 0, 0);
			LCD_displayString("Password created");
		}

		else{

			LCD_clearScreen();
			LCD_moveCursor( 0, 0);
			LCD_displayString("Passwords don't");
			LCD_moveCursor( 1, 0);
			LCD_displayString("Match");
			_delay_ms(1000);
		}
	}while (flag != 0x10);
	LCD_clearScreen();
	LCD_moveCursor( 0, 0);
	LCD_displayString("Password Created");
	_delay_ms(600);
}


/*
 * Description:
 * 				This Function is responsible for sending a password
 * 				to Control_ECU via UART. It takes integer value (i.e password)
 * 				and convert it to a string of ASCIIs and send the string via
 * 				UART
 */
void sendPassword(uint32 data){
	uint8 buff[10];

	for(int i=4;i>=0;i--){
		buff[i]=(data%10)+48;
		data=data/10;
	}
	buff[5]='\0';
	UART_sendString(buff);
	UART_sendByte('#');
}

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
void mainMenu(void){
	uint8 key_press=0,i=0,check;
	LCD_clearScreen();
	LCD_moveCursor( 0, 0);
	LCD_displayString("+: Open Door");
	LCD_moveCursor( 1, 0);
	LCD_displayString("-: Change Pass");
	do{
		key_press = KEYPAD_getPressedKey();
	}while((key_press !='+') && (key_press !='-'));

	do{
		check=checkIfPasswordIsCorrect();
		if(check){
			break;
		}
		i++;
	}while(i<3);

	if(!check){
		LCD_clearScreen();
		LCD_moveCursor( 0, 0);
		LCD_displayString("System Locked");
		UART_sendByte('O');
		for(uint8 i=0;i<60;i++){
			_delay_ms(1000);
		}
		UART_sendByte('o');
	}
	else{
		switch(key_press){
		case '+':
			openDoor();
			while(g_timerTick!=23);
			g_timerTick=0;
			break;
		case '-':
			UART_sendByte('Z');
			passwordCreate();
			break;
		}
	}

}

/*
 * Description:
 * 				This is the Function that takes the input password from
 * 				the user and sends it to control ECU. this function returns
 * 				true if password matches saved one
 */
uint8 checkIfPasswordIsCorrect(void){
	UART_sendByte('S');
	uint8 key_pressed;
	uint32 pass=0;
	LCD_clearScreen();
	LCD_moveCursor( 0, 0);
	LCD_displayString("PLZ Enter Pass:");

	LCD_moveCursor( 1, 0);
	for(uint8 i=0;i<5;i++){

		key_pressed=KEYPAD_getPressedKey();
		pass=(pass*10)+key_pressed;
		LCD_displayCharacter('*');
	}
	while(KEYPAD_getPressedKey() != '=');
	sendPassword(pass);
	if(UART_recieveByte()== 0xff){
		return 1;
	}
	return 0;
}

/*
 * Description:
 * 				This Function initiates timer 1 to count 15 seconds and
 * 				sets the callback function to TIMER_callBack() that manipulates
 * 				the timing of opening and closing the door
 * 				and sends to the Control ECU command to start rotating the motor
 */
void openDoor(void){
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayString("Door Opened!!");
	Timer1_ConfigType Config_Ptr={0,50000,F_CPU_256,compare};
	Timer1_init(& Config_Ptr);
	Timer1_setCallBack(&TIMER_callBack);
	UART_sendByte('Q');

}

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
void TIMER_callBack(void){
	g_timerTick++;

	if(g_timerTick==10){
		Timer1_ConfigType Config_Ptr={0,30000,F_CPU_256,compare};
		Timer1_init(& Config_Ptr);
		UART_sendByte('W');
	}
	else if(g_timerTick==13){
		Timer1_ConfigType Config_Ptr={0,50000,F_CPU_256,compare};
		Timer1_init(& Config_Ptr);
		UART_sendByte('X');
	}
	else if(g_timerTick==23){
		Timer1_deInit();
		UART_sendByte('Y');
	}


}
