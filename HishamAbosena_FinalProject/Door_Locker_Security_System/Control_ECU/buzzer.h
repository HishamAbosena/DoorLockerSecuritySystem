/*************************************************************
 * file name: buzzer.h
 *
 * Module: buzzer
 *
 * Description: Header file for buzzer module
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

/*************************************************************
* 				Including Common header files 				 *
**************************************************************/
#include "std_types.h"
#include "common_macros.h"

/*************************************************************
* 			    	Static Configurations  					 *
**************************************************************/
#define BUZZER_PORT_ID				PORTD_ID
#define BUZZER_PIN_ID				PIN7_ID

#define BUZZER_ON					LOGIC_HIGH
#define BUZZER_OFF					LOGIC_LOW

/*************************************************************
* 				    Function Prototypes 			     	 *
**************************************************************/
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
