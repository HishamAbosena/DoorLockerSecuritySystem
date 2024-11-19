/*************************************************************
 * file name: timer1.h
 *
 * Module: Timer 1
 *
 * Description: Header file for timer 1 module
 *  Created on: Jul 20, 2024
 *
 *  Author: Hisham Abosena
 *************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

/*************************************************************
* 				Including Common header files 				 *
**************************************************************/
#include "std_types.h"
#include "common_macros.h"

/*************************************************************
* 				User Defined Data types  					 *
**************************************************************/
typedef enum{
	NO_CLK=0 ,F_CPU_1 , F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}Timer1_Prescaler;

typedef enum{
	overflow,compare=4
}Timer1_Mode;

typedef struct {

 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;

} Timer1_ConfigType;



/*************************************************************
* 				Function Prototypes 						 *
**************************************************************/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));



#endif /* TIMER1_H_ */
