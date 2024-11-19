
/*************************************************************
 * file name: MC1.C
 *
 * Module: HMI_ECU
 *
 * Description: Source file for Human-Machine Interface
 * 				Micro-Controller
 *
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/
#include "HMI_ECU_Functions.h"


/*
 * Main function for HMI_ECU:
 * 					This function calls the initialization function of
 * 					the MC, then calls the function to create the password.
 * 					and in the super loop it just calls the main-program.
 */
int main(void){
	 MC1_init();

	 passwordCreate();

	 while(1){
		 mainMenu();
	 }
}

